#include <ecs/ecs.hpp>
#include <test/TransformSystem.h>
#include <test/TransformComponent.h>
#include <test/GameObject.h>


#define total_obj 5100
#define tick_loop 1

void ReorganizeMemory() {
	ecs::ECSRegistry* registry = new ecs::ECSRegistry;

	ecs::ReserveVectorCapacity<GameObject>(registry->mEntities, total_obj);
	ecs::ReserveMapCapacity<TransformComponent>(registry->mComponents, total_obj);

	
	for (int i = 0; i < total_obj; i++) {
		GameObject* entity = new GameObject(i, "GameObject_" + std::to_string(i), "Entity_" + std::to_string(i));
		TransformComponent* component = new TransformComponent(i, "TransformComponent_" + std::to_string(i),  i, 2 * i);

		ecs::RegisterEntity(registry->mEntities, entity);
		ecs::RegisterComponentToEntity<TransformComponent>(registry->mComponents ,entity, component);
	}

	TransformSystem transformSystem (1, 0);

	ecs::RegisterSystem(registry->mSystems, &transformSystem);

	ecs::InitializeSystem(*registry);
	for (int i = 0; i < tick_loop; i++) {
		ecs::UpdateSystem(registry, 0);
	}

	for (int i = 0; i < registry->mEntities.array.size(); i++) {
		std::cout << &registry->mEntities.array[i] <<  std::endl;
	}

	delete registry;
}


int main() {
	ReorganizeMemory();

	return 0;
}