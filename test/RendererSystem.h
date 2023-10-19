#pragma once
#include <ecs.hpp>
#include <test/RendererComponent.h>
class RendererSystem : public ecs::System {
public:
	RendererSystem(uint32_t p_ID, uint32_t p_Priority) : System( p_ID, p_Priority) {}
	~RendererSystem() {
		m_transformComponents.clear();
	};

	virtual void Initialize(ecs::ECSRegistry& p_Registry) override
	{
		auto _RendererComponents = ecs::GetAllComponents<RendererComponent>(p_Registry.mComponents);
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
