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
		virtual void Initialize() = 0;
		virtual void Execute() = 0;
	};
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

		virtual void Initialize(ECSRegistry& p_Registry) = 0;
		virtual void Update(float deltaTime) = 0;

		bool operator==(const System& p_System);
	};

	System::System(uint32_t p_ID, uint32_t p_Priority) : IBase(p_ID), mPriority(p_Priority)
	{
	}
	System::~System()
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
		std::vector<Entity*> mEntities;
		std::unordered_map<size_t, std::vector<Component*>> mComponents;
		std::vector<System*> mSystems;
	};
#endif // !ECS_REGISTRY

#ifndef ECS_REGISTRY_MANAGER
#define ECS_REGISTRY_MANAGER

	inline void RegisterEntity(std::vector<Entity*>& p_vector, Entity* p_Entity)
	{
		p_vector.push_back(p_Entity);
	}

	inline void RemoveEntity(std::vector<Entity*>& p_vector, Entity* p_Entity)
	{
		auto it = std::find(p_vector.begin(), p_vector.end(), p_Entity);
		if (it != p_vector.end()) {
			p_vector.erase(it);
		}
	}

	inline void RemoveComponentFromEntity(std::unordered_map<size_t, std::vector<Component*>>& p_Components, Entity* p_Entity, Component* p_Component)
	{
		auto it_entity = p_Components.find(p_Entity->mID);
		if (it_entity != p_Components.end()) {
			auto it_component = std::find(it_entity->second.begin(), it_entity->second.end(), p_Component);
			if (it_component != it_entity->second.end()) {
				it_entity->second.erase(it_component);
			}
		}
	}

	inline void RegisterSystem(std::vector<System*>& p_Systems, System* p_System)
	{
		p_Systems.push_back(p_System);
	}

	inline void RemoveSystem(std::vector<System*>& p_Systems, System* p_System)
	{
		auto it_system = std::find(p_Systems.cbegin(), p_Systems.cend(), p_System);
		if (it_system != p_Systems.end()) {
			p_Systems.erase(it_system);
		}
	}

	template <typename T>
	inline void ReserveVectorCapacity(std::vector<T>& p_Vector, size_t p_Capacity) {
		p_Vector.reserve(p_Capacity);
	}

	template <typename ComponentType, typename Key, typename T>
	inline void ReserveMapCapacity(std::unordered_map<Key, std::vector<T>>& p_Map, size_t p_Capacity) {
		Key componentType = typeid(ComponentType).hash_code();
		p_Map[componentType].reserve(p_Capacity);
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
	inline void RegisterComponentToEntity(std::unordered_map<size_t, std::vector<Component*>>& p_Components, Entity* p_Entity, ComponentType* p_Component) {
		static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be derived from Component");

		Component* _component = dynamic_cast<Component*>(p_Component);
		_component->mEntity = p_Entity;

		size_t componentType = typeid(ComponentType).hash_code();
		p_Components[componentType].push_back(p_Component);
	}

	template<typename ComponentType>
	inline _NODISCARD ComponentType* GetComponentForEntity(std::unordered_map<size_t, std::vector<Component*>>& p_Components, Entity* entity) {
		static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be derived from Component");

		size_t componentType = typeid(ComponentType).hash_code();
		auto it = p_Components.find(componentType);

		if (it != p_Components.end()) {
			for (auto component : it->second) {
				if (component->mEntity.mID == entity->mID) {
					return dynamic_cast<ComponentType*>(component);
				}
			}
		}

		return nullptr;
	}

	template<typename ComponentType>
	inline _NODISCARD std::vector<ComponentType*> GetAllComponents(std::unordered_map<size_t, std::vector<Component*>>& p_Components) {
		static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be derived from Component");

		size_t componentType = typeid(ComponentType).hash_code();
		auto it = p_Components.find(componentType);

		if (it != p_Components.end()) {
			std::vector<ComponentType*> result;
			for (Component* component : it->second) {
				ComponentType* castedComponent = dynamic_cast<ComponentType*>(component);
				if (castedComponent) {
					result.push_back(castedComponent);
				}
			}
			return result;
		}

		return std::vector<ComponentType*>();
	}

	template <typename ComponentType>
	inline _NODISCARD std::vector<ComponentType*> GetComponent(std::unordered_map<size_t, std::vector<Component*>>& p_Components, Entity* p_Entity) {
		static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be derived from Component");

		size_t componentType = typeid(ComponentType).hash_code();

		if (p_Components.find(componentType) != p_Components.end()) {

			std::vector<ComponentType*> componentVector;

			for (Component* component : p_Components[componentType]) {
				ComponentType* derivedComponent = dynamic_cast<ComponentType*>(component);
				if (derivedComponent) {
					componentVector.push_back(derivedComponent);
				}
			}
			return componentVector;
		}
		return std::vector<ComponentType*>();
	}

	void InitializeSystem(ECSRegistry& p_Registry)
	{
		for (auto& system : p_Registry.mSystems) {
			system->Initialize(p_Registry);
		}
	}

	void UpdateSystem(ECSRegistry& p_Registry, float deltaTime)
	{
		for (auto& system : p_Registry.mSystems) {
			system->Update(deltaTime);
		}
	}

	// Função para liberar recursos em uma instância de ECSRegistry
	void ReleaseECSRegistry(ECSRegistry& registry) {
		for (System* system : registry.mSystems) {
			delete system;
		}

		for (const auto& map : registry.mComponents) {
			for (Component* component : map.second) {
				delete component;
			}
		}

		for (Entity* entity : registry.mEntities) {
			delete entity;
		}

		registry.mSystems.clear();
		registry.mComponents.clear();
		registry.mEntities.clear();
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