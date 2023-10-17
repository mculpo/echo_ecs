#pragma once
#include <header/Core.h>
#include <header/Entity.h>
#include <header/Component.h>
#include <header/System.h>

namespace ecs {

	/*void RegisterEntity(std::vector<Entity*> p_vector, Entity* p_Entity);
	void RemoveEntity(std::vector<Entity*> p_vector, Entity* p_Entity);

	void RemoveComponentFromEntity(Entity* p_Entity, Component* p_Component);

	void RegisterSystem(std::vector<System*> p_Systems, System* p_System);
	void RemoveSystem(std::vector<System*> p_Systems, System* p_System);

	template <typename T>
	void ReserveVectorCapacity(std::vector<T>& p_Vector, size_t p_Capacity);

	template <typename ComponentType, typename Key, typename T>
	void ReserveMapCapacity(std::unordered_map<Key, std::vector<T>>& p_Map, size_t p_Capacity);

	template <typename T>
	void ReorganizeMemoryLayout(std::vector<T>& p_Vector);

	template <typename Key, typename T>
	void ReorganizeMemoryLayout(std::unordered_map<Key, std::vector<T>>& p_Map);

	template <typename ComponentType>
	void RegisterComponentToEntity(std::unordered_map<size_t, std::vector<Component*>> p_Components, Entity* p_Entity, ComponentType* p_Component);

	template<typename ComponentType>
	_NODISCARD ComponentType* GetComponentForEntity(std::unordered_map<size_t, std::vector<Component*>> p_Components, Entity* entity);

	template<typename ComponentType>
	_NODISCARD std::vector<ComponentType*> GetAllComponents(std::unordered_map<size_t, std::vector<Component*>> p_Components);

	template <typename ComponentType>
	_NODISCARD std::vector<ComponentType*> GetComponent(std::unordered_map<size_t, std::vector<Component*>> p_Components, Entity* p_Entity);*/

	void RegisterEntity(std::vector<Entity*>& p_vector, Entity* p_Entity)
	{
		p_vector.push_back(p_Entity);
	}

	void RemoveEntity(std::vector<Entity*>& p_vector, Entity* p_Entity)
	{
		auto it = std::find(p_vector.begin(), p_vector.end(), p_Entity);
		if (it != p_vector.end()) {
			p_vector.erase(it);
		}
	}

	void RemoveComponentFromEntity(std::unordered_map<size_t, std::vector<Component*>>& p_Components, Entity* p_Entity, Component* p_Component)
	{
		auto it_entity = p_Components.find(p_Entity->mID);
		if (it_entity != p_Components.end()) {
			auto it_component = std::find(it_entity->second.begin(), it_entity->second.end(), p_Component);
			if (it_component != it_entity->second.end()) {
				it_entity->second.erase(it_component);
			}
		}
	}

	void RegisterSystem(std::vector<System*>& p_Systems, System* p_System)
	{
		p_Systems.push_back(p_System);
	}

	void RemoveSystem(std::vector<System*>& p_Systems, System* p_System)
	{
		auto it_system = std::find(p_Systems.cbegin(), p_Systems.cend(), p_System);
		if (it_system != p_Systems.end()) {
			p_Systems.erase(it_system);
		}
	}

	template <typename T>
	void ReserveVectorCapacity(std::vector<T>& p_Vector, size_t p_Capacity) {
		p_Vector.reserve(p_Capacity);
	}

	template <typename ComponentType, typename Key, typename T>
	void ReserveMapCapacity(std::unordered_map<Key, std::vector<T>>& p_Map, size_t p_Capacity) {
		Key componentType = typeid(ComponentType).hash_code();
		p_Map[componentType].reserve(p_Capacity);
	}

	template <typename T>
	void ReorganizeMemoryLayout(T& p_Vector) {
		std::vector<T> compactedVector;
		compactedVector.reserve(p_Vector.size());

		for (const T& item : p_Vector) {
			compactedVector.push_back(item);
		}
		p_Vector = compactedVector;
	}

	template <typename Key, typename T>
	void ReorganizeMemoryLayout(std::unordered_map<Key, std::vector<T>>& p_Map) {
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
	void RegisterComponentToEntity(std::unordered_map<size_t, std::vector<Component*>>& p_Components, Entity* p_Entity, ComponentType* p_Component) {
		static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be derived from Component");

		Component* _component = dynamic_cast<Component*>(p_Component);
		_component->mEntity = p_Entity;

		size_t componentType = typeid(ComponentType).hash_code();
		p_Components[componentType].push_back(p_Component);
	}

	template<typename ComponentType>
	_NODISCARD ComponentType* GetComponentForEntity(std::unordered_map<size_t, std::vector<Component*>>& p_Components, Entity* entity) {
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
	_NODISCARD std::vector<ComponentType*> GetAllComponents(std::unordered_map<size_t, std::vector<Component*>>& p_Components) {
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
	_NODISCARD std::vector<ComponentType*> GetComponent(std::unordered_map<size_t, std::vector<Component*>>& p_Components, Entity* p_Entity) {
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
}

