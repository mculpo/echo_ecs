#pragma once
#include <header/ECSRegistry.h>
#include <test/TransformComponent.h>
#include <header/Entity.h>
#include <header/Timer.h>
class TransformSystem : public ecs::System {
public:
	TransformSystem(ecs::ECSRegistry* p_Registry, uint32_t p_ID, uint32_t p_Priority) : System(p_Registry, p_ID, p_Priority) {}
	TransformSystem(std::shared_ptr<ecs::ECSRegistry> p_Registry, uint32_t p_ID, uint32_t p_Priority) : System(p_Registry, p_ID, p_Priority) {}
	~TransformSystem() {};

	virtual void Initialize() override
	{
		auto _RendererComponents = m_registry->GetAllComponent<TransformComponent>();
		for (auto& renderer : _RendererComponents) {
			m_rendererComponents.push_back(renderer);
		}
	}
	virtual void Update(float deltaTime) override
	{
		Timer::ClockBegin();
		for (auto& renderer : m_rendererComponents) {
			renderer->Execute();
		}
		Timer::ClockEnd();	
		// Exibe o tempo decorrido
		std::cout << "Tempo decorrido no update do TransformSystem: " << Timer::GetMillisecondsDuration() << " milissegundos" << std::endl;
	}
	virtual void Cleanup() override
	{
	}
private:
	std::vector<std::shared_ptr<TransformComponent>> m_rendererComponents;
};
