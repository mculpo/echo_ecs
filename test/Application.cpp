#include <header/Core.h>
#include <header/ECSRegistry.h>
#include <test/TransformSystem.h>
#include <test/RendererSystem.h>
#include <test/PhysicSystem.h>
#include <test/TransformComponent.h>
#include <test/GameObject.h>
#include <header/Timer.h>
#include "RendererComponent.h"
#include "PhysicComponent.h"

#define total_obj 10000
#define tick_loop 100

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
		RendererComponent* component_1 = new RendererComponent(i);
		PhysicComponent* component_2 = new PhysicComponent(i);

		registry->RegisterEntity(entity);
		registry->RegisterComponentToEntity(entity, component);
		registry->RegisterComponentToEntity(entity, component_1);
		registry->RegisterComponentToEntity(entity, component_2);
	}

	Timer::ClockEnd();
	registry->ReorganizeMemoryLayout();

	registry->RegisterSystem(new TransformSystem(registry, 1, 0));
	registry->RegisterSystem(new RendererSystem(registry, 2, 1));
	registry->RegisterSystem(new PhysicSystem(registry, 3, 2));
	
	std::cout << "Tamanho da classe em bytes: " << sizeof(registry) << std::endl;

	registry->InitializeSystem();
	for (int i = 0; i < tick_loop; i++) {
		Timer::ClockBegin();
		registry->UpdateSystem(0);
		Timer::ClockEnd();
		// Exibe o tempo decorrido
		std::cout << "time to run a systems methods " << Timer::GetMillisecondsDuration() << " milliseconds" << std::endl;
	}


	delete registry;
}

int main() {
	
	ReorganizeMemory();
	std::cin.get();
	return 0;
}