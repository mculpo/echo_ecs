#include "ECSRegistry.h"
namespace ecs {
	ECSRegistry::ECSRegistry()
	{
		m_indexEntities   = 0;
		m_indexComponents = 0;
		m_indexSystems    = 0;
	}
	ECSRegistry::~ECSRegistry()
	{
	}
	void ECSRegistry::RegisterEntity(Entity* p_Entity)
	{
		m_entities.push_back(p_Entity);
	}
	void ECSRegistry::RemoveEntity(Entity* p_Entity)
	{
		auto it = std::find(m_entities.begin(), m_entities.end(), p_Entity);
		if (it != m_entities.end()) {
			m_entities.erase(it);
		}
	}
	void ECSRegistry::RegisterComponentToEntity(Entity* p_Entity, Component* p_Component)
	{
		auto it_entity = std::find(m_entities.begin(), m_entities.end(), p_Entity);
		if (it_entity != m_entities.end()) {
			m_components[(*it_entity)->GetID()].push_back(p_Component);
		}
		else {
			std::cout << "Entity not found : " << p_Entity->GetID() << std::endl;
		}
	}
	void ECSRegistry::RemoveComponentFromEntity(Entity* p_Entity, Component* p_Component)
	{
		auto it_entity = m_components.find(p_Entity->GetID());
		if (it_entity != m_components.end()) {
			auto it_component = std::find(it_entity->second.begin(), it_entity->second.end(), p_Component);
			if (it_component != it_entity->second.end()) {
				it_entity->second.erase(it_component);
			}
		}
	}
	void ECSRegistry::RegisterSystem(System* p_System)
	{
		m_systems.push_back(p_System);
	}
	void ECSRegistry::RemoveSystem(System* p_System)
	{
		auto it_system = std::find(m_systems.begin(), m_systems.end(), p_System);
		if (it_system != m_systems.end()) {
			m_systems.erase(it_system);
		}
	}

	void ECSRegistry::UpdateSystem(float deltaTime)
	{
		for (auto& system : m_systems) {
			system->Initialize();
		}

		for (auto& system : m_systems) {
			system->Update(deltaTime);
		}
		for (auto& system : m_systems) {
			system->Cleanup();
		}

	}

	uint32_t ECSRegistry::NextIndexEntity()
	{
		return ++m_indexEntities;
	}

	uint32_t ECSRegistry::NextIndexComponent()
	{
		return ++m_indexComponents;
	}

	uint32_t ECSRegistry::NextIndexSystem()
	{
		return ++m_indexSystems;
	}

	uint32_t ECSRegistry::CurrentIndexEntity() const
	{
		return m_indexEntities;
	}

	uint32_t ECSRegistry::CurrentIndexComponent() const
	{
		return m_indexComponents;
	}

	uint32_t ECSRegistry::CurrentIndexSystem() const
	{
		return m_indexSystems;
	}

	template<typename ComponentType>
	inline bool ECSRegistry::HasComponent(Entity& entity)
	{
		std::type_index type = typeid(ComponentType);
		auto it = m_components.find(entity);
		if (it != m_components.end()) {
			for (Component* component : it->second) {
				if(dynamic_cast<ComponentType*>(component) != nullptr)
					return true;
			}
		}
		return false;
	}

	template<typename ...ComponentTypes>
	inline std::vector<Entity> ECSRegistry::GetEntitiesWithComponents()
	{
		std::vector<Entity> entities;

		for (const auto& entityComponents : m_components) {
			if (CheckEntityForComponents(entityComponents.first, ComponentTypes...)) {
				entities.push_back(entityComponents.first);
			}
		}
		return entities;
	}

	template<typename ComponentType, typename ...Rest>
	inline bool ECSRegistry::CheckEntityForComponents(Entity& entity, ComponentType, Rest ...rest)
	{
		if (!HasComponent<ComponentType>(entity)) {
			return false;
		}
		return !CheckEntityForComponents(entity, rest...);
	}
	template<typename ComponentType>
	ComponentType* ECSRegistry::GetComponentForEntity(Entity* entity)
	{
		std::type_index type = typeid(ComponentType);
		auto it = m_components.find(entity->GetID());

		if (it != m_components.end()) {
			for (Component* component : it->second) {
				if (std::type_index(typeid(*component)) == type) {
					return dynamic_cast<ComponentType*>(component);
				}
			}
		}

		return nullptr; // Componente não encontrado para a entidade
	}
}
