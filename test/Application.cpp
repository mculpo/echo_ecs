#include <ecs/ecs.hpp>
#include <test/TransformSystem.h>
#include <test/TransformComponent.h>
#include <test/GameObject.h>

#define total_obj 100
#define tick_loop 1

void ReorganizeMemory() {
	ecs::ECSRegistry* registry = new ecs::ECSRegistry;

	ecs::ReserveVectorCapacity<GameObject>(registry->mEntities, total_obj);
	ecs::ReserveMapCapacity<TransformComponent>(registry->mComponents, total_obj);

	for (int i = 0; i < total_obj; i++) {
		GameObject* entity = new GameObject(i, "GameObject_" + std::to_string(i), "Entity_" + std::to_string(i));
		ecs::RegisterEntity(registry->mEntities, entity);
	}
	
	for (int i = 0; i < total_obj; i++) {
		TransformComponent* component = new TransformComponent(i, i, i + 2);
		ecs::RegisterComponentToEntity<TransformComponent>(registry->mComponents , registry->mEntities.ptr[i], component);
	}

	TransformSystem transformSystem (1, 0);

	ecs::RegisterSystem(registry->mSystems, &transformSystem);
	std::cout << "start" << std::endl;
	ecs::InitializeSystem(*registry);
	for (int i = 0; i < tick_loop; i++) {
		ecs::Timer::ClockBegin();
		ecs::UpdateSystem(registry, 0);
		ecs::Timer::ClockEnd();
		std::cout << ecs::Timer::GetMillisecondsDuration() << " ms" << std::endl;
	}

	//std::cin.get();

	delete registry;
}

int main() {
	ReorganizeMemory();

	return 0;
}