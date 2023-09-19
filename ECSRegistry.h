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

		template<typename ComponentType>
		bool HasComponent(Entity& entity);

		template <typename... ComponentTypes>
		std::vector<Entity> GetEntitiesWithComponents();

		template<typename ComponentType, typename... Rest>
		bool CheckEntityForComponents(Entity& entity, ComponentType, Rest... rest);

		template<typename ComponentType>
		ComponentType* GetComponentForEntity(Entity* entity);

		uint32_t NextIndexEntity();
		uint32_t NextIndexComponent();
		uint32_t NextIndexSystem();

		uint32_t CurrentIndexEntity() const;
		uint32_t CurrentIndexComponent() const;
		uint32_t CurrentIndexSystem() const;

	private:
		std::vector<Entity*> m_entities;
		std::unordered_map <uint32_t, std::vector<Component*>> m_components;
		std::vector<System*> m_systems;

		uint32_t m_indexEntities;
		uint32_t m_indexComponents;
		uint32_t m_indexSystems;
	};
}

