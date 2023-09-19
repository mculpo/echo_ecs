#include <Core.h>
#include <ECSRegistry.h>
#include <RenderSystem.h>
#include <RendererComponent.h>

int main() {
	ecs::ECSRegistry* registry = new ecs::ECSRegistry();

	ecs::Entity* entity1 = new ecs::Entity(registry->NextIndexEntity(), "Entity1", "Entity1");
	RendererComponent* component1 = new RendererComponent(registry->NextIndexComponent(), "component1");
	RendererComponent* component2 = new RendererComponent(registry->NextIndexComponent(), "component2");
	RendererSystem* system1 = new RendererSystem(registry, registry->NextIndexSystem(), 0);

	registry->RegisterEntity(entity1);
	registry->RegisterComponentToEntity(entity1, component1);
	registry->RegisterComponentToEntity(entity1, component2);
	registry->RegisterSystem(system1);

	registry->UpdateSystem(0);

	delete registry;
	return 0;
}