#pragma once
#include <header/ECSRegistry.h>
#include <test/TransformComponent.h>
#include <header/Entity.h>
#include <header/Timer.h>
class TransformSystem : public ecs::System {
public:
	TransformSystem(ecs::ECSRegistry* p_Registry, uint32_t p_ID, uint32_t p_Priority) : System(p_Registry, p_ID, p_Priority) {}
	~TransformSystem() {
		for (auto registry : m_transformComponents) {
			delete registry;
		}
		m_transformComponents.clear();
	};

	virtual void Initialize() override
	{
		auto _RendererComponents = m_registry->GetAllComponent<TransformComponent>();
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
