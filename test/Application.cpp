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

	ecs::ECSRegistry* registry = new ecs::ECSRegistry();

	Timer::ClockBegin();

	for (int i = 0; i < 1000; i++) {
		GameObject* entity = new GameObject(i, "Entity", "Entity");
		TransformComponent* component = new TransformComponent(i, "my_component_");

		registry->RegisterEntity(entity);
		registry->RegisterComponentToEntity(entity, component);
	}

	// Registra o tempo de término
	Timer::ClockEnd();

	// Exibe o tempo decorrido
	std::cout << "Tempo decorrido para criar: " << Timer::GetSecondsDuration() << " segundos" << std::endl;

	registry->RegisterSystem(new TransformSystem(registry, 1, 0));
	Timer::ClockBegin();
	registry->InitializeSystem();
	registry->UpdateSystem(0);
	// Registra o tempo de término
	Timer::ClockEnd();

	// Exibe o tempo decorrido
	std::cout << "Tempo decorrido do UPDATE: " << Timer::GetSecondsDuration() << " segundos" << std::endl;
	registry->CleanUpSystem();
	
	delete registry;
	std::cin.get();
	return 0;
}