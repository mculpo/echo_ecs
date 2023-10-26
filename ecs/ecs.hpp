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
	void IFuncBase::Initialize() {};
	void IFuncBase::Execute() {};
#endif //ECS_FUNC_BASE

#ifndef ECS_IBASE
#define ECS_IBASE
	class IBase {
	public:
		uint32_t mID;
		IBase(uint32_t p_ID);
		~IBase();
	};

	IBase::IBase(uint32_t p_ID) : mID(p_ID){}
	IBase::~IBase(){}
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

	Component::Component(uint32_t p_ID) : mEntity(nullptr), IBase(p_ID) {}
	Component::~Component(){}
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

	inline void System::Initialize(ECSRegistry& p_Registry) {}
	inline void System::Update(float deltaTime) {}

	System::System(uint32_t p_ID, uint32_t p_Priority) : IBase(p_ID), mPriority(p_Priority){}
	System::~System(){}

	bool System::operator==(const System& p_System)
	{
		return mID == p_System.mID;
	}
#endif // !ECS_SYSTEM


#ifndef ECS_ARRAYS
#define ECS_ARRAYS
	template <typename T>
	struct ecs_array {
		std::vector<T> array;
		std::vector<T*> ptr;
	};

#endif // !ECS_ARRAYS

#ifndef ECS_REGISTRY
#define ECS_REGISTRY
	class Entity;
	class Component;
	class System;
	struct ECSRegistry {
		ecs_array<Entity> mEntities;
		std::unordered_map<size_t, ecs_array<Component>> mComponents;
		ecs_array<System> mSystems;
	};
#endif // !ECS_REGISTRY

#ifndef ECS_REGISTRY_MANAGER
#define ECS_REGISTRY_MANAGER

	void RegisterEntity(ecs_array<Entity>& pVector, Entity* pEntity) {
		pVector.array.push_back(*pEntity);
		pVector.ptr.push_back(pEntity);
	}

	void RemoveEntity(ecs_array<Entity>& pVector, Entity* pEntity)
	{
		for (size_t i = 0; i < pVector.array.size(); i++) {
			if (pVector.array[i] == *pEntity) {
				pVector.array.erase(pVector.array.begin() + i);
				pVector.ptr.erase(pVector.ptr.begin() + i);
				break;
			}
		}
	}

	void RegisterSystem(ecs_array<System>& pSystems, System* pSystem)
	{
		pSystems.array.push_back(*pSystem);
		pSystems.ptr.push_back(pSystem);
	}

	void RemoveSystem(ecs_array<System>& pSystems, System* pSystem)
	{
		for (size_t i = 0; i < pSystems.array.size(); i++) {
			if (pSystems.array[i] == *pSystem) {
				pSystems.array.erase(pSystems.array.begin() + i);
				pSystems.ptr.erase(pSystems.ptr.begin() + i);
				break;
			}
		}
	}

	template <typename Type, typename T>
	inline void ReserveVectorCapacity(ecs_array<T>& pVector, size_t pCapacity) {
		size_t c_bytes = pCapacity * sizeof(Type);
		size_t new_capacity = c_bytes / sizeof(T);
		if (c_bytes % sizeof(T) != 0) {
			new_capacity++; // Incrementa se houver resto na divisão
		}
		pVector.array.reserve(new_capacity);
		pVector.ptr.reserve(pCapacity);
	}

	template <typename ComponentType, typename T>
	inline void ReserveMapCapacity(std::unordered_map<size_t, ecs_array<T>>& pMap, size_t pCapacity) {
		size_t componentType = typeid(ComponentType).hash_code();
		size_t c_bytes = pCapacity * sizeof(ComponentType);
		size_t new_capacity = c_bytes / sizeof(T);
		if (c_bytes % sizeof(T) != 0) {
			new_capacity++; // Incrementa se houver resto na divisão
		}
		pMap[componentType].array.reserve(new_capacity);
		pMap[componentType].ptr.reserve(pCapacity);
	}

	template <typename ComponentType>
	inline void RegisterComponentToEntity(std::unordered_map<size_t, ecs_array<Component>>& pComponents, Entity* pEntity, Component* pComponent) {
		static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be derived from Component");

		ComponentType* _component = dynamic_cast<ComponentType*>(pComponent);
		_component->mEntity = pEntity;

		size_t componentType = typeid(ComponentType).hash_code();
		pComponents[componentType].array.push_back(*_component);
		pComponents[componentType].ptr.push_back(_component);
	}

	/*template<typename ComponentType>
	 std::vector<ComponentType*> GetAllComponents(std::unordered_map<size_t, ecs_array<Component>>& pComponents) {
		static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be derived from Component");

		size_t componentType = typeid(ComponentType).hash_code();
		auto it = pComponents.find(componentType);

		if (it != pComponents.end()) {
			std::vector<ComponentType*> result;
			for (auto component : it->second.ptr) {
				ComponentType* castedComponent = dynamic_cast<ComponentType*>(component);
				if (castedComponent) {
					result.push_back(castedComponent);
				}
			}
			return result;
		}

		return std::vector<ComponentType*>();
	}*/

	//template<typename ComponentType>
	//inline _NODISCARD std::vector<ComponentType*> GetAllComponents(std::unordered_map<size_t, ecs_array<Component>>& pComponents) {
	//	static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be derived from Component");

	//	size_t componentType = typeid(ComponentType).hash_code();
	//	auto it = pComponents.find(componentType);

	//	if (it != pComponents.end()) {
	//		// Converta os ponteiros do vetor ptr para ComponentType*
	//		std::vector<ComponentType*> result;
	//		for (Component* component : it->second.ptr) {
	//			/*ComponentType* derivedComponent = static_cast<ComponentType*>(component);
	//			if (derivedComponent) {
	//				result.push_back(derivedComponent);
	//			}*/
	//			result.push_back(static_cast<ComponentType*>(component));
	//		}
	//		return result;
	//	}

	//	return std::vector<ComponentType*>();
	//}

	template<typename ComponentType>
	std::vector<ComponentType*> GetAllComponents(std::unordered_map<size_t, ecs_array<Component>>& pComponents) {
		static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be derived from Component");
		size_t componentType = typeid(ComponentType).hash_code();
		auto it = pComponents.find(componentType);

		if (it != pComponents.end()) {
			std::vector<ComponentType*> result;
			for (Component* component : it->second.ptr) {
				ComponentType* derivedComponent = static_cast<ComponentType*>(component);
				if (derivedComponent) {
					result.push_back(derivedComponent);
				}
			}
			return result;
		}

		return std::vector<ComponentType*>();
	}

	void InitializeSystem(ECSRegistry& p_Registry)
	{
		for (auto system : p_Registry.mSystems.ptr) {
			system->Initialize(p_Registry);
		}
	}

	void UpdateSystem(ECSRegistry* p_Registry, float deltaTime)
	{
		for (auto system : p_Registry->mSystems.ptr) {
			system->Update(deltaTime);
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
			return static_cast<double>(duration.count()) / 60.0; // Converter para segundos
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