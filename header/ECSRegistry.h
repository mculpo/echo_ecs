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

		void RegisterEntity(std::shared_ptr<Entity> p_Entity);
		void RemoveEntity(std::shared_ptr<Entity> p_Entity);

		void RegisterComponentToEntity(std::shared_ptr<Entity> p_Entity, std::shared_ptr<Component> p_Component);
		void RemoveComponentFromEntity(std::shared_ptr<Entity> p_Entity, std::shared_ptr<Component> p_Component);

		void RegisterSystem(std::shared_ptr<System> p_System);
		void RemoveSystem(std::shared_ptr<System> p_System);

		virtual void InitializeSystem();
		virtual void UpdateSystem(float deltaTime);
		virtual void CleanUpSystem();

		uint32_t NextIndexEntity();
		uint32_t NextIndexComponent();
		uint32_t NextIndexSystem();

		uint32_t CurrentIndexEntity() const;
		uint32_t CurrentIndexComponent() const;
		uint32_t CurrentIndexSystem() const;


		template<typename ComponentType>
		inline std::vector<std::shared_ptr<Entity>> GetEntitiesWithComponent()
		{
			static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be derived from Component");
			std::vector<std::shared_ptr<Entity>> entities;

			for (auto entity : m_entities) {
				auto it = m_components.find(entity->GetID());
				for (auto componentPair : it->second) {
					if (auto component = std::dynamic_pointer_cast<ComponentType>(componentPair)) {
						entities.push_back(entity);
						break;
					}
				}
			}

			return entities;
		};

		template<typename ComponentType>
		inline std::shared_ptr<ComponentType> GetComponentForEntity(std::shared_ptr<Entity> entity)
		{
			static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be derived from Component");
			auto it = m_components.find(entity->GetID());

			if (it != m_components.end()) {
				for (auto component : it->second) {
					if (auto derivedComponent = std::dynamic_pointer_cast<ComponentType>(component)) {
						return derivedComponent;
					}
				}
			}

			return nullptr; // Componente não encontrado para a entidade
		};

		template<typename ComponentType>
		inline std::vector<std::shared_ptr<ComponentType>> GetAllComponent()
		{
			static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be derived from Component");
			std::vector<std::shared_ptr<ComponentType>> components;

			for (auto entity : m_entities) {
				auto it = m_components.find(entity->GetID());
				for (auto component : it->second) {
					if (auto derivedComponent = std::dynamic_pointer_cast<ComponentType>(component)) {
						components.push_back(derivedComponent);
						break;
					}
				}
			}

			return components;
		};

	private:
		std::vector<std::shared_ptr<Entity>> m_entities;
		std::unordered_map <uint32_t, std::vector<std::shared_ptr<Component>>> m_components;
		std::vector<std::shared_ptr<System>> m_systems;

		uint32_t m_indexEntities;
		uint32_t m_indexComponents;
		uint32_t m_indexSystems;
	};
}

