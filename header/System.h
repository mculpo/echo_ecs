#pragma once
#include <header/Core.h>
#include <header/ECSRegistry.h>
namespace ecs{
	class ECSRegistry;
	class System
	{
	public:
		System(ECSRegistry* p_ECSRegistry, uint32_t p_ID, uint32_t p_Priority);
		~System();

		virtual void Initialize() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Cleanup() = 0;

		uint32_t GetID() const;

		unsigned int GetPriority() const;
		void SetPriority(unsigned int p_Priority);

		bool operator==(const System& p_System);

	protected:
		uint32_t m_ID;
		uint32_t m_priority;
		ECSRegistry* m_registry;
	};
}

