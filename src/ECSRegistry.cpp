#include <header/ECSRegistry.h>
namespace ecs {
	ECSRegistry::ECSRegistry()
	{
		m_indexEntities   = 0;
		m_indexComponents = 0;
		m_indexSystems    = 0;
	}

	ECSRegistry::~ECSRegistry()
	{}

	void ECSRegistry::RegisterEntity(std::shared_ptr<Entity> p_Entity)
	{
		m_entities.push_back(p_Entity);
	}

	void ECSRegistry::RemoveEntity(std::shared_ptr<Entity> p_Entity)
	{
		auto it = std::find(m_entities.begin(), m_entities.end(), p_Entity);
		if (it != m_entities.end()) {
			m_entities.erase(it);
		}
	}

	void ECSRegistry::RegisterComponentToEntity(std::shared_ptr<Entity> p_Entity, std::shared_ptr<Component> p_Component)
	{
		auto it_entity = std::find(m_entities.begin(), m_entities.end(), p_Entity);
		if (it_entity != m_entities.end()) {
			m_components[(*it_entity)->GetID()].push_back(p_Component);
		}
		else {
			std::cout << "Entity not found : " << p_Entity->GetID() << std::endl;
		}
	}

	void ECSRegistry::RemoveComponentFromEntity(std::shared_ptr<Entity> p_Entity, std::shared_ptr<Component> p_Component)
	{
		auto it_entity = m_components.find(p_Entity->GetID());
		if (it_entity != m_components.end()) {
			auto it_component = std::find(it_entity->second.begin(), it_entity->second.end(), p_Component);
			if (it_component != it_entity->second.end()) {
				it_entity->second.erase(it_component);
			}
		}
	}

	void ECSRegistry::RegisterSystem(std::shared_ptr <System> p_System)
	{
		m_systems.push_back(p_System);
	}

	void ECSRegistry::RemoveSystem(std::shared_ptr <System> p_System)
	{
		auto it_system = std::find(m_systems.cbegin(), m_systems.cend(), p_System);
		if (it_system != m_systems.end()) {
			m_systems.erase(it_system);
		}
	}

	void ECSRegistry::InitializeSystem()
	{
		std::cout << "Start Initialize" << std::endl;
		for (auto& system : m_systems) {
			system->Initialize();
		}
		std::cout << std::endl;
	}

	void ECSRegistry::UpdateSystem(float deltaTime)
	{
		std::cout << "Start Update" << std::endl;
		for (auto& system : m_systems) {
			system->Update(deltaTime);
		}
		std::cout << std::endl;
	}

	void ECSRegistry::CleanUpSystem()
	{
		std::cout << "Start Cleanup" << std::endl;
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
}
