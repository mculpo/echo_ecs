#include <header/Core.h>
#include <header/ECSRegistry.h>
#include <test/TransformSystem.h>
#include <test/RendererSystem.h>
#include <test/PhysicSystem.h>
#include <test/TransformComponent.h>
#include <test/GameObject.h>
#include <header/Timer.h>
#include <header/ECSRegistryManager.h>
#include "RendererComponent.h"
#include "PhysicComponent.h"

#define total_obj 10
#define tick_loop 1

void ReorganizeMemory() {
	ecs::ECSRegistry* registry = new ecs::ECSRegistry;
	Timer::ClockBegin();

	ecs::ReserveVectorCapacity(registry->mEntities, total_obj);
	ecs::ReserveVectorCapacity(registry->mSystems, total_obj);
	ecs::ReserveMapCapacity<TransformComponent>(registry->mComponents, total_obj);
	//ecs::ReserveMapCapacity<RendererComponent>(registry->mComponents, total_obj);
	//ecs::ReserveMapCapacity<PhysicComponent>(registry->mComponents, total_obj);

	for (int i = 0; i < total_obj; i++) {
		GameObject* entity = new GameObject(i, "Entity_" + std::to_string(i), "Entity_" + std::to_string(i));
		TransformComponent* component = new TransformComponent(i, "my_component_" + std::to_string(i));
		//RendererComponent* component_1 = new RendererComponent(i);
		//PhysicComponent* component_2 = new PhysicComponent(i);

		ecs::RegisterEntity(registry->mEntities, entity);
		ecs::RegisterComponentToEntity(registry->mComponents ,entity, component);
		//ecs::RegisterComponentToEntity(registry->mComponents ,entity, component_1);
		//ecs::RegisterComponentToEntity(registry->mComponents ,entity, component_2);
	}

	Timer::ClockEnd();
	//ReorganizeMemoryLayout();

	ecs::RegisterSystem(registry->mSystems, new TransformSystem(1, 0));
	//ecs::RegisterSystem(registry->mSystems, new RendererSystem(2, 1));
	//ecs::RegisterSystem(registry->mSystems, new PhysicSystem(3, 2));

	ecs::InitializeSystem(*registry);
	for (int i = 0; i < tick_loop; i++) {
		Timer::ClockBegin();
		ecs::UpdateSystem(*registry, 0);
		Timer::ClockEnd();
		// Exibe o tempo decorrido
		std::cout << "time to run a systems methods " << Timer::GetMillisecondsDuration() << " milliseconds" << std::endl;
	}
	ecs::ReleaseECSRegistry(*registry);
}

int main() {
	
	ReorganizeMemory();
	std::cin.get();
	return 0;
}