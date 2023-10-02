#pragma once
#include <header/Core.h>
#include <header/Entity.h>
#include <header/Component.h>
#include <header/System.h>

namespace ecs {
	class System;
	class ECSRegistry
	{
	public:
		ECSRegistry();
		~ECSRegistry();

		void RegisterEntity(Entity* p_Entity);
		void RemoveEntity(Entity* p_Entity);

		void RemoveComponentFromEntity(Entity* p_Entity, Component* p_Component);

		void RegisterSystem(System* p_System);
		void RemoveSystem(System* p_System);

		void ReorganizeMemoryLayout();

		virtual void InitializeSystem();
		virtual void UpdateSystem(float deltaTime);

		template <typename ComponentType>
		void RegisterComponentToEntity(Entity* p_Entity, ComponentType* p_Component) {
			static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be derived from Component");

			Component* _component = dynamic_cast<Component*>(p_Component);
			_component->SetEntityID(p_Entity->GetID());

			size_t componentType = typeid(ComponentType).hash_code();

			// Verifica se o vetor de componentes desse tipo já existe
			if (m_components.find(componentType) == m_components.end()) {
				m_components[componentType] = std::vector<Component*>();
			}

			// Adiciona o componente ao vetor
			m_components[componentType].push_back(p_Component);
		}

		template<typename ComponentType>
		ComponentType* GetComponentForEntity(Entity* entity)
		{
			static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be derived from Component");

			size_t componentType = typeid(ComponentType).hash_code();
			auto it = m_components.find(componentType);

			if (it != m_components.end()) {
				for (auto component : it->second) {
					if (component->GetEntityID() == entity->GetID()) {
						return dynamic_cast<ComponentType*>(component);
					}
				}
			}

			// Componente não encontrado para a entidade
			return nullptr;
		}


		template<typename ComponentType>
		std::vector<ComponentType*> GetAllComponents()
		{
			static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be derived from Component");

			size_t componentType = typeid(ComponentType).hash_code();
			auto it = m_components.find(componentType);

			if (it != m_components.end()) {
				std::vector<ComponentType*> result;
				for (Component* component : it->second) {
					ComponentType* castedComponent = dynamic_cast<ComponentType*>(component);
					if (castedComponent) {
						result.push_back(castedComponent);
					}
				}
				return result;
			}

			// Se nenhum componente do tipo for encontrado, retorne um vetor vazio.
			return std::vector<ComponentType*>();
		}


		template <typename ComponentType>
		std::vector<ComponentType*> GetComponent(Entity* p_Entity) {
			static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be derived from Component");

			size_t componentType = typeid(ComponentType).hash_code();

			if (m_components.find(componentType) != m_components.end()) {

				std::vector<ComponentType*> componentVector;

				for (Component* component : m_components[componentType]) {
					ComponentType* derivedComponent = dynamic_cast<ComponentType*>(component);
					if (derivedComponent) {
						componentVector.push_back(derivedComponent);
					}
				}
				return componentVector;
			}
			return std::vector<ComponentType*>();
		}

	private:
		std::vector<Entity*> m_entities;
		std::unordered_map<size_t, std::vector<Component*>> m_components;
		std::vector<System*> m_systems;
	};
}

