#pragma once
#include <ECSRegistry.h>
#include <RendererComponent.h>
#include <Entity.h>
class RendererSystem : public ecs::System {
public:
	RendererSystem(ecs::ECSRegistry* p_Registry, uint32_t p_ID, uint32_t p_Priority) : System(p_Registry, p_ID, p_Priority) {
	}
	~RendererSystem() {};

	virtual void Initialize() override
	{
		auto _RendererComponents = m_registry->GetAllComponent<RendererComponent>();
		for (auto& renderer : _RendererComponents) {
			m_rendererComponents.push_back(renderer);
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
		for (auto& renderer : m_rendererComponents) {
			delete renderer;
		}
	}
private:
	std::vector<RendererComponent*> m_rendererComponents;
};
