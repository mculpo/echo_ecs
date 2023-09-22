#include <header/Core.h>
#include <header/ECSRegistry.h>
#include <test/RenderSystem.h>
#include <test/RendererComponent.h>
#include <test/GameObject.h>

int main() {
	std::shared_ptr<ecs::ECSRegistry> registry = std::make_shared<ecs::ECSRegistry>();

	std::shared_ptr<GameObject> entity1 = 
		std::make_shared<GameObject>(registry->NextIndexEntity(), "Entity1", "Entity1");
	std::shared_ptr<RendererComponent> component1 = 
		std::make_shared<RendererComponent>(registry->NextIndexComponent(), "my_component_1");

	std::shared_ptr<GameObject> entity2 =
		std::make_shared<GameObject>(registry->NextIndexEntity(), "Entity2", "Entity2");
	std::shared_ptr<RendererComponent> component2 = 
		std::make_shared<RendererComponent>(registry->NextIndexComponent(), "my_component_2");

	std::shared_ptr<RendererSystem> system1 = 
		std::make_shared<RendererSystem>(registry, registry->NextIndexSystem(), 0);

	registry->RegisterEntity(entity1);
	registry->RegisterComponentToEntity(entity1, component1);

	registry->RegisterEntity(entity2);
	registry->RegisterComponentToEntity(entity2, component2);

	registry->RegisterSystem(system1);

	registry->InitializeSystem();
	registry->UpdateSystem(0);
	registry->CleanUpSystem();
	
	return 0;
}