#include <header/Core.h>
#include <header/ECSRegistry.h>
#include <test/TransformSystem.h>
#include <test/TransformComponent.h>
#include <test/GameObject.h>
#include <header/Timer.h>

int main() {

	// Obtém o número máximo de threads suportadas pelo hardware
	int numCores = std::thread::hardware_concurrency();

	if (numCores != 0) {
		std::cout << "Numero de nucleos do processador: " << numCores << std::endl;
	}
	else {
		std::cout << "Não foi possível determinar o numero de ncleos do processador." << std::endl;
	}


	std::shared_ptr<ecs::ECSRegistry> registry = std::make_shared<ecs::ECSRegistry>();

	Timer::ClockBegin();

	for (int i = 0; i < 10000; i++) {
		std::shared_ptr<GameObject> entity =
			std::make_shared<GameObject>(registry->NextIndexEntity(), "Entity", "Entity");
		std::shared_ptr<TransformComponent> component =
			std::make_shared<TransformComponent>(registry->NextIndexComponent(), "my_component_");

		registry->RegisterEntity(entity);
		registry->RegisterComponentToEntity(entity, component);
	}

	// Registra o tempo de término
	Timer::ClockEnd();

	// Exibe o tempo decorrido
	std::cout << "Tempo decorrido para criar: " << Timer::GetMillisecondsDuration() << " milissegundos" << std::endl;

	std::shared_ptr<TransformSystem> transformSystem = std::make_shared<TransformSystem>(registry, registry->NextIndexSystem(), 0);

	registry->RegisterSystem(transformSystem);

	registry->InitializeSystem();
	for (int i = 0; i < 100; i++) {
		registry->UpdateSystem(0);
	}
	registry->CleanUpSystem();
	
	return 0;
}