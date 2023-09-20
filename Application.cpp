#include <Core.h>
#include <ECSRegistry.h>
#include <RenderSystem.h>
#include <RendererComponent.h>

int main() {
	std::shared_ptr<ecs::ECSRegistry> registry = std::make_shared<ecs::ECSRegistry>();

	std::shared_ptr<ecs::Entity> entity1 = 
		std::make_shared<ecs::Entity>(registry->NextIndexEntity(), "Entity1", "Entity1");
	std::shared_ptr<RendererComponent> component1 = 
		std::make_shared<RendererComponent>(registry->NextIndexComponent(), "my_component_1");

	std::shared_ptr<ecs::Entity> entity2 = 
		std::make_shared<ecs::Entity>(registry->NextIndexEntity(), "Entity2", "Entity2");
	std::shared_ptr<RendererComponent> component2 = 
		std::make_shared<RendererComponent>(registry->NextIndexComponent(), "my_component_2");

	std::shared_ptr<RendererSystem> system1 = 
		std::make_shared<RendererSystem>(registry, registry->NextIndexSystem(), 0);

	registry->RegisterEntity(entity1);
	registry->RegisterComponentToEntity(entity1, component1);

	registry->RegisterEntity(entity2);
	registry->RegisterComponentToEntity(entity2, component2);

	registry->RegisterSystem(system1);

	registry->UpdateSystem(0);
	
	return 0;
}