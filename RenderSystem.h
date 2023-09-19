#pragma once
#include <ECSRegistry.h>
#include <RendererComponent.h>
#include <Entity.h>
class RendererSystem : public ecs::System {
public:
	RendererSystem(ecs::ECSRegistry* registry, uint32_t p_ID, uint32_t p_Priority) : System(registry, p_ID, p_Priority) {
	}
	~RendererSystem() {};

	virtual void Initialize() override
	{
		std::vector<ecs::Entity> entitiesRenderer = m_registry->GetEntitiesWithComponents<RendererComponent>();
		for (auto& entt : entitiesRenderer) {
			m_rendererComponents.push_back(m_registry->GetComponentForEntity<RendererComponent>(&entt));
		}
	}
	virtual void Update(float deltaTime) override
	{
		for (auto& renderer : m_rendererComponents) {
			renderer->Execute();
		}
	}
	virtual void Cleanup() override
	{
	}

	std::vector<RendererComponent*> m_rendererComponents;
};
