#pragma once
#include <ECSRegistry.h>
#include <RendererComponent.h>
#include <Entity.h>
class RendererSystem : public ecs::System {
public:
	RendererSystem(ecs::ECSRegistry* p_Registry, uint32_t p_ID, uint32_t p_Priority) : System(p_Registry, p_ID, p_Priority) {}
	RendererSystem(std::shared_ptr<ecs::ECSRegistry> p_Registry, uint32_t p_ID, uint32_t p_Priority) : System(p_Registry, p_ID, p_Priority) {}
	~RendererSystem() {};

	virtual void Initialize() override
	{
		auto _EntitiesComponents = m_registry->GetEntitiesWithComponent<RendererComponent>();
		for (auto& renderer : _EntitiesComponents) {
			m_entity.push_back(renderer);
		}
		auto _RendererComponents = m_registry->GetAllComponent<RendererComponent>();
		for (auto& renderer : _RendererComponents) {
			m_rendererComponents.push_back(renderer);
		}
	}
	virtual void Update(float deltaTime) override
	{
		auto _SoloEntity = m_entity[0];
		auto _SoloComponento = m_registry->GetComponentForEntity<RendererComponent>(_SoloEntity);

		std::cout << "Executing a 'm_registry->GetComponentForEntity<RendererComponent>'" << std::endl;
		_SoloEntity->Execute();
		_SoloComponento->Execute();

		std::cout << std::endl;
		std::cout << "Executing a vector with do 'm_registry->GetEntitiesWithComponent<RendererComponent>()'" << std::endl;
		for (auto& entity : m_entity) {
			std::cout << entity->GetName() << std::endl;
		}
		std::cout << std::endl;
		std::cout << "Executing a vector with do 'm_registry->GetAllComponent<RendererComponent>()'" << std::endl;
		for (auto& renderer : m_rendererComponents) {
			renderer->Execute();
		}
	}
	virtual void Cleanup() override
	{
	}
private:
	std::vector<std::shared_ptr<ecs::Entity>> m_entity;
	std::vector<std::shared_ptr<RendererComponent>> m_rendererComponents;
};
