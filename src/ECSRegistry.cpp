#include <header/ECSRegistry.h>
namespace ecs {
	ECSRegistry::ECSRegistry()
	{}
	ECSRegistry::~ECSRegistry()
	{	
		for (System* system : m_systems) {
			delete system;
		}

		for (const auto& map : m_components) {
			for (Component* component : map.second) {
				delete component;
			}
		}

		for (Entity* Entity : m_entities) {
			delete Entity;
		}

		m_systems.clear();
		m_components.clear();
		m_entities.clear();
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
		auto it_system = std::find(m_systems.cbegin(), m_systems.cend(), p_System);
		if (it_system != m_systems.end()) {
			m_systems.erase(it_system);
		}
	}

	void ECSRegistry::InitializeSystem()
	{
		for (auto& system : m_systems) {
			system->Initialize();
		}
	}

	void ECSRegistry::UpdateSystem(float deltaTime)
	{
		
		for (auto& system : m_systems) {
			system->Update(deltaTime);
		}
	}

	void ECSRegistry::CleanUpSystem()
	{
		for (auto& system : m_systems) {
			system->Cleanup();
		}
	}
}
