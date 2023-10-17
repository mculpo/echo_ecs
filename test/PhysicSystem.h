#pragma once
#include <header/ECSRegistry.h>
#include <header/ECSRegistryManager.h>
#include <test/PhysicComponent.h>
#include <header/Entity.h>
#include <header/Timer.h>
class PhysicSystem : public ecs::System {
public:
	PhysicSystem(uint32_t p_ID, uint32_t p_Priority) : System(p_ID, p_Priority) {}
	~PhysicSystem() {
		m_transformComponents.clear();
	};

	virtual void Initialize(ecs::ECSRegistry& p_Registry) override
	{
		auto _RendererComponents = ecs::GetAllComponents<PhysicComponent>(p_Registry.mComponents);
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
	std::vector<PhysicComponent*> m_transformComponents;
};
