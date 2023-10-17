#pragma once
#include <header/Core.h>
#include <header/ECSRegistry.h>
namespace ecs{
	class ECSRegistry;
	class System
	{
	public:
		uint32_t mID;
		uint32_t mPriority;

		System(uint32_t p_ID, uint32_t p_Priority);
		~System();

		virtual void Initialize(ECSRegistry& p_Registry) = 0;
		virtual void Update(float deltaTime) = 0;

		bool operator==(const System& p_System);
	};
}

