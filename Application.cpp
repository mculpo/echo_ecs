#include <Core.h>
#include <ECSRegistry.h>
#include <RenderSystem.h>
#include <RendererComponent.h>

int main() {
	ecs::ECSRegistry* registry = new ecs::ECSRegistry();

	ecs::Entity* entity1 = new ecs::Entity(registry->NextIndexEntity(), "Entity1", "Entity1");
	RendererComponent* component1 = new RendererComponent(registry->NextIndexComponent(), "my_component_1");

	ecs::Entity* entity2 = new ecs::Entity(registry->NextIndexEntity(), "Entity2", "Entity2");
	RendererComponent* component2 = new RendererComponent(registry->NextIndexComponent(), "my_component_2");

	RendererSystem* system1 = new RendererSystem(registry, registry->NextIndexSystem(), 0);

	registry->RegisterEntity(entity1);
	registry->RegisterComponentToEntity(entity1, component1);

	registry->RegisterEntity(entity2);
	registry->RegisterComponentToEntity(entity2, component2);

	registry->RegisterSystem(system1);

	registry->UpdateSystem(0);
	
	delete registry;

	return 0;
}