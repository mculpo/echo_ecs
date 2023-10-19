#pragma once
#include <ecs.hpp>
#include <test/TransformComponent.h>
class TransformSystem : public ecs::System {
public:
	TransformSystem(uint32_t p_ID, uint32_t p_Priority) : System(p_ID, p_Priority) {}
	~TransformSystem() {
		m_transformComponents.clear();
	};

	virtual void Initialize(ecs::ECSRegistry& p_Registry) override
	{
		auto _RendererComponents = ecs::GetAllComponents<TransformComponent>(p_Registry.mComponents);
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
	std::vector<TransformComponent*> m_transformComponents;
};
