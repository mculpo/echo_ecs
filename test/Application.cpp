#include <header/Core.h>
#include <header/ECSRegistry.h>
#include <test/TransformSystem.h>
#include <test/TransformComponent.h>
#include <test/GameObject.h>
#include <header/Timer.h>

#define total_obj 1000
#define tick_loop 10

void NonReorganizeMemory() {
	ecs::ECSRegistry* registry = new ecs::ECSRegistry();

	for (int i = 0; i < total_obj; i++) {
		GameObject* entity = new GameObject(i, "Entity_" + std::to_string(i), "Entity_" + std::to_string(i));
		TransformComponent* component = new TransformComponent(i, "my_component_" + std::to_string(i));

		registry->RegisterEntity(entity);
		registry->RegisterComponentToEntity(entity, component);
	}

	registry->RegisterSystem(new TransformSystem(registry, 1, 0));
	Timer::ClockBegin();

	registry->InitializeSystem();
	for (int i = 0; i < tick_loop; i++)
		registry->UpdateSystem(0);

	Timer::ClockEnd();
	// Exibe o tempo decorrido
	std::cout << "time to run a systems methods " << Timer::GetMillisecondsDuration() << " milliseconds" << std::endl;
	delete registry;
}
void ReorganizeMemory() {
	ecs::ECSRegistry* registry = new ecs::ECSRegistry();
	Timer::ClockBegin();

	for (int i = 0; i < total_obj; i++) {
		GameObject* entity = new GameObject(i, "Entity_" + std::to_string(i), "Entity_" + std::to_string(i));
		TransformComponent* component = new TransformComponent(i, "my_component_" + std::to_string(i));

		registry->RegisterEntity(entity);
		registry->RegisterComponentToEntity(entity, component);
	}
	Timer::ClockEnd();
	registry->ReorganizeMemoryLayout();

	registry->RegisterSystem(new TransformSystem(registry, 1, 0));
	Timer::ClockBegin();

	registry->InitializeSystem();
	for (int i = 0; i < tick_loop; i++)
		registry->UpdateSystem(0);

	Timer::ClockEnd();
	// Exibe o tempo decorrido
	std::cout << "time to run a systems methods " << Timer::GetMillisecondsDuration() << " milliseconds" << std::endl;

	delete registry;
}

int main() {
	NonReorganizeMemory();
	ReorganizeMemory();
	std::cin.get();
	return 0;
}