#pragma once
#include <Core.h>
#include <Entity.h>
#include <Component.h>
#include <System.h>

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

		void UpdateSystem(float deltaTime);

		uint32_t NextIndexEntity();
		uint32_t NextIndexComponent();
		uint32_t NextIndexSystem();

		uint32_t CurrentIndexEntity() const;
		uint32_t CurrentIndexComponent() const;
		uint32_t CurrentIndexSystem() const;


		template<typename ComponentType>
		inline std::vector<Entity*> GetEntitiesWithComponent()
		{
			static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be derived from Component");
			std::vector<Entity*> entities;

			for (auto entity : m_entities) {
				auto it = m_components.find(entity->GetID());
				for (auto component : it->second) {
					if (dynamic_cast<ComponentType*>(component) != nullptr) {
						entities.push_back(entity);
						break;
					}
				}
			}

			return entities;
		};

		template<typename ComponentType>
		inline ComponentType* GetComponentForEntity(Entity* entity)
		{
			auto it = m_components.find(entity->GetID());

			if (it != m_components.end()) {
				for (Component* component : it->second) {
					if (dynamic_cast<ComponentType*>(component) != nullptr) {
						return static_cast<ComponentType*>(component);
					}
				}
			}

			return nullptr; // Componente não encontrado para a entidade
		};

		template<typename ComponentType>
		inline std::vector<ComponentType*> GetAllComponent()
		{
			std::vector<ComponentType*> components;

			for (auto entity : m_entities) {
				auto it = m_components.find(entity->GetID());
				for (auto component : it->second) {
					if (dynamic_cast<ComponentType*>(component) != nullptr) {
						components.push_back(static_cast<ComponentType*>(component));
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

		uint32_t m_indexEntities;
		uint32_t m_indexComponents;
		uint32_t m_indexSystems;
	};
}

