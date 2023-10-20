#ifndef _ECS_
#define _ECS_

#include <iostream>
#include <bitset>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include <chrono>
#include <thread>
#include <iomanip>
#define String std::string

namespace ecs {
#ifndef ECS_FUNC_BASE
#define ECS_FUNC_BASE
	class IFuncBase {
	public:
		virtual void Initialize();
		virtual void Execute();
	};

	inline void ecs::IFuncBase::Initialize()
	{
	}

	inline void ecs::IFuncBase::Execute()
	{
	}
#endif //ECS_FUNC_BASE

#ifndef ECS_IBASE
#define ECS_IBASE
	class IBase {
	public:
		uint32_t mID;
		IBase(uint32_t p_ID);
		~IBase();
	};

	IBase::IBase(uint32_t p_ID) : mID(p_ID)
	{
	}
	IBase::~IBase()
	{
	}
#endif // !CLASS_IBASE

#ifndef ECS_ENTITY
#define ECS_ENTITY
	class Entity : public IBase, public IFuncBase
	{
	public:
		String mName;
		String mTag;

		Entity(uint32_t p_ID, const String& p_Name, const String& p_Tag);
		~Entity();
		// Operador de igualdade para comparar duas entidades pelo ID
		bool operator==(const Entity& p_Other) const;
	};

	Entity::Entity(uint32_t p_ID, const String& p_Name, const String& p_Tag) :
		IBase(p_ID), mName(p_Name), mTag(p_Tag) {}

	Entity::~Entity() {}

	bool Entity::operator==(const Entity& p_Other) const
	{
		return mID == p_Other.mID;
	}

#endif // !ECS_ENTITY

#ifndef ECS_COMPONENT
#define ECS_COMPONENT
	class Entity;
	class Component : public IBase, public IFuncBase {
	public:
		Entity* mEntity;
		Component(uint32_t p_ID);
		~Component();
		// Implemente o operador de igualdade para comparar duas entidades pelo ID
		bool operator==(const Component& p_Other) const;
	};

	Component::Component(uint32_t p_ID) : mEntity(nullptr), IBase(p_ID) {
	}
	Component::~Component()
	{
	}
	bool Component::operator==(const Component& p_Other) const
	{
		return mID == p_Other.mID;
	}
#endif // !ECS_COMPONENT

#ifndef ECS_SYSTEM
#define ECS_SYSTEM
	class ECSRegistry;
	class System : public IBase
	{
	public:
		uint32_t mPriority;

		System(uint32_t p_ID, uint32_t p_Priority);
		~System();

		virtual void Initialize(ECSRegistry& p_Registry);
		virtual void Update(float deltaTime);

		bool operator==(const System& p_System);
	};

	System::System(uint32_t p_ID, uint32_t p_Priority) : IBase(p_ID), mPriority(p_Priority)
	{
	}
	System::~System()
	{
	}
	inline void System::Initialize(ECSRegistry& p_Registry)
	{
	}
	inline void System::Update(float deltaTime)
	{
	}
	bool System::operator==(const System& p_System)
	{
		return mID == p_System.mID;
	}
#endif // !ECS_SYSTEM

#ifndef ECS_REGISTRY
#define ECS_REGISTRY
	class Entity;
	class Component;
	class System;
	class ECSRegistry {
	public:
		std::vector<Entity> mEntities;
		std::unordered_map<size_t, std::vector<Component>> mComponents;
		std::vector<System> mSystems;
	};
#endif // !ECS_REGISTRY

#ifndef ECS_REGISTRY_MANAGER
#define ECS_REGISTRY_MANAGER

	template <typename T>
	inline std::vector<T> CreateArray(size_t pCapacity) {
		std::vector<T> components(pCapacity, nullptr);
		return components;
	}

	void RegisterEntity(std::vector<Entity>& pVector, Entity& pEntity) {
		pVector.push_back(pEntity);
	}

	void RemoveEntity(std::vector<Entity>& pVector, Entity& pEntity)
	{
		auto it = std::find(pVector.begin(), pVector.end(), pEntity);
		if (it != pVector.end()) {
			pVector.erase(it);
		}
	}

	void RegisterSystem(std::vector<System>& pSystems, System& pSystem)
	{
		pSystems.push_back(pSystem);
	}

	void RemoveSystem(std::vector<System>& pSystems, System& pSystem)
	{
		auto it_system = std::find(pSystems.begin(), pSystems.end(), pSystem);
		if (it_system != pSystems.end()) {
			pSystems.erase(it_system);
		}
	}

	template <typename ComponentType, typename T>
	inline void ReserveVectorCapacity(std::vector<T>& p_Vector, size_t pCapacity) {
		p_Vector = CreateArray<ComponentType>(pCapacity);
	}

	template <typename ComponentType, typename Key, typename T>
	inline void ReserveMapCapacity(std::unordered_map<Key, std::vector<T>>& p_Map, size_t pCapacity) {
		Key componentType = typeid(ComponentType).hash_code();
		p_Map[componentType] = CreateArray<ComponentType>(pCapacity);
	}

	template <typename T>
	inline void ReorganizeMemoryLayout(T& p_Vector) {
		std::vector<T> compactedVector;
		compactedVector.reserve(p_Vector.size());

		for (const T& item : p_Vector) {
			compactedVector.push_back(item);
		}
		p_Vector = compactedVector;
	}

	template <typename Key, typename T>
	inline void ReorganizeMemoryLayout(std::unordered_map<Key, std::vector<T>>& p_Map) {
		for (auto& componentPair : p_Map) {
			std::vector<T>& components = componentPair.second;
			std::vector<T> newLayoutComponents;
			newLayoutComponents.reserve(components.size());
			for (T& component : components) {
				newLayoutComponents.push_back(component);
			}
			components = newLayoutComponents;
		}
	}

	template <typename ComponentType>
	inline void RegisterComponentToEntity(std::unordered_map<size_t, std::vector<Component>>& pComponents, Entity& pEntity, Component& pComponent) {
		static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be derived from Component");

		ComponentType* _component = dynamic_cast<ComponentType*>(&pComponent);
		_component->mEntity = &pEntity;

		size_t componentType = typeid(ComponentType).hash_code();
		pComponents[componentType].push_back(pComponent);
	}

	template<typename ComponentType>
	inline _NODISCARD std::vector<ComponentType*> GetAllComponents(std::unordered_map<size_t, std::vector<Component>>& pComponents) {
		static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be derived from Component");

		size_t componentType = typeid(ComponentType).hash_code();
		auto it = pComponents.find(componentType);

		if (it != pComponents.end()) {
			std::vector<ComponentType*> result;
			for (auto component : it->second) {
				ComponentType* castedComponent = dynamic_cast<ComponentType*>(&component);
				if (castedComponent) {
					result.push_back(castedComponent);
				}
			}
			return result;
		}

		return std::vector<ComponentType*>();
	}

	void InitializeSystem(ECSRegistry& p_Registry)
	{
		for (auto& system : p_Registry.mSystems) {
			system.Initialize(p_Registry);
		}
	}

	void UpdateSystem(ECSRegistry& p_Registry, float deltaTime)
	{
		for (auto& system : p_Registry.mSystems) {
			system.Update(deltaTime);
		}
	}
#endif // !ECS_REGISTRY

#ifndef ECS_TIMER
#define ECS_TIMER
	class Timer {
	public:
		static void ClockBegin() {
			start_time = std::chrono::high_resolution_clock::now();
		}

		static void ClockEnd() {
			end_time = std::chrono::high_resolution_clock::now();
		}

		static double GetMillisecondsDuration() {
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
			return static_cast<double>(duration.count()) / 1000.0; // Converte para milissegundos com precisão de até 8 casas decimais
		}

		static double GetSecondsDuration() {
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
			return static_cast<double>(duration.count()) / 1000.0; // Converter para segundos
		}

	private:
		static std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
		static std::chrono::time_point<std::chrono::high_resolution_clock> end_time;
	};

	std::chrono::time_point<std::chrono::high_resolution_clock> Timer::start_time;
	std::chrono::time_point<std::chrono::high_resolution_clock> Timer::end_time;
#endif // !ECS_TIMER
}

#endif _ECS_