#pragma once
#include <header/ECSRegistry.h>
#include <test/RendererComponent.h>
#include <header/Entity.h>
#include <header/Timer.h>
class RendererSystem : public ecs::System {
public:
	RendererSystem(ecs::ECSRegistry* p_Registry, uint32_t p_ID, uint32_t p_Priority) : System(p_Registry, p_ID, p_Priority) {}
	~RendererSystem() {
		for (auto registry : m_transformComponents) {
			delete registry;
		}
		m_transformComponents.clear();
	};

	virtual void Initialize() override
	{
		auto _RendererComponents = m_registry->GetAllComponents<RendererComponent>();
		for (auto& renderer : _RendererComponents) {
			m_transformComponents.push_back(renderer);
		}
	}
	virtual void Update(float deltaTime) override
	{
		for (auto& renderer : m_transformComponents) {
			renderer->Execute();
		}
	}
private:
	std::vector<RendererComponent*> m_transformComponents;
};
