#include <ecs/ecs.hpp>
#include <test/TransformSystem.h>
#include <test/RendererSystem.h>
#include <test/PhysicSystem.h>
#include <test/TransformComponent.h>
#include <test/GameObject.h>
#include <test/RendererComponent.h>
#include <test/PhysicComponent.h>

#define total_obj 1000
#define tick_loop 30

void ReorganizeMemory() {
	ecs::ECSRegistry* registry = new ecs::ECSRegistry;
	ecs::Timer::ClockBegin();

	ecs::ReserveVectorCapacity<GameObject>(registry->mEntities, total_obj);
	ecs::ReserveVectorCapacity<ecs::System>(registry->mSystems, total_obj);
	ecs::ReserveMapCapacity<TransformComponent>(registry->mComponents, total_obj);
	ecs::ReserveMapCapacity<RendererComponent>(registry->mComponents, total_obj);
	ecs::ReserveMapCapacity<PhysicComponent>(registry->mComponents, total_obj);

	for (int i = 0; i < total_obj; i++) {
		GameObject* entity = new GameObject(i, "Entity_" + std::to_string(i), "Entity_" + std::to_string(i));
		TransformComponent* component = new TransformComponent(i, "my_component_" + std::to_string(i));
		RendererComponent* component_1 = new RendererComponent(i);
		PhysicComponent* component_2 = new PhysicComponent(i);

		ecs::RegisterEntity(registry->mEntities, *entity);
		ecs::RegisterComponentToEntity<TransformComponent>(registry->mComponents ,*entity, *component);
		ecs::RegisterComponentToEntity<RendererComponent>(registry->mComponents ,*entity, *component_1);
		ecs::RegisterComponentToEntity<PhysicComponent>(registry->mComponents ,*entity, *component_2);
	}

	ecs::Timer::ClockEnd();

	TransformSystem transformSystem(1, 0);
	RendererSystem rendererSystem(2, 1);
	PhysicSystem physicsSystem(3, 2);

	ecs::RegisterSystem(registry->mSystems, transformSystem);
	ecs::RegisterSystem(registry->mSystems, rendererSystem);
	ecs::RegisterSystem(registry->mSystems, physicsSystem);

	ecs::InitializeSystem(*registry);
	for (int i = 0; i < tick_loop; i++) {
		ecs::Timer::ClockBegin();
		ecs::UpdateSystem(*registry, 0);
		ecs::Timer::ClockEnd();
		// Exibe o tempo decorrido
		std::cout << "time to run a systems methods " << ecs::Timer::GetMillisecondsDuration() << " milliseconds" << std::endl;
	}
	delete registry;
}

int main() {
	
	ReorganizeMemory();

	return 0;
}