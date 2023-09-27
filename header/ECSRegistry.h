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

		void RegisterComponentToEntity(Entity* p_Entity, Component* p_Component);
		void RemoveComponentFromEntity(Entity* p_Entity, Component* p_Component);

		void RegisterSystem(System* p_System);
		void RemoveSystem(System* p_System);

		virtual void InitializeSystem();
		virtual void UpdateSystem(float deltaTime);
		virtual void CleanUpSystem();

		template<typename ComponentType>
		inline std::vector<Entity*> GetEntitiesWithComponent()
		{
			static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be derived from Component");
			std::vector<Entity*> entities;

			for (auto entity : m_entities) {
				auto it = m_components.find(entity->GetID());
				for (auto componentPair : it->second) {
					if (auto component = dynamic_cast<ComponentType*>(componentPair)) {
						entities.push_back(entity);
						break;
					}
				}
			}

			return entities;
		};

		template<typename ComponentType>
		inline std::shared_ptr<ComponentType> GetComponentForEntity(Entity* entity)
		{
			static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be derived from Component");
			auto it = m_components.find(entity->GetID());

			if (it != m_components.end()) {
				for (auto component : it->second) {
					if (auto derivedComponent = dynamic_cast<ComponentType*>(component)) {
						return derivedComponent;
					}
				}
			}

			return nullptr; // Componente não encontrado para a entidade
		};

		template<typename ComponentType>
		inline std::vector<ComponentType*> GetAllComponent()
		{
			static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be derived from Component");
			std::vector<ComponentType*> components;

			for (auto entity : m_entities) {
				auto it = m_components.find(entity->GetID());
				for (auto component : it->second) {
					if (auto derivedComponent = dynamic_cast<ComponentType*>(component)) {
						components.push_back(derivedComponent);
						break;
					}
				}
			}

			return components;
		};

	private:
		std::vector<Entity*> m_entities;
		std::unordered_map <uint32_t, std::vector<Component*>> m_components;
		std::vector<System*> m_systems;
	};
}

