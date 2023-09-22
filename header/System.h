#pragma once
#include <header/Core.h>
#include <header/ECSRegistry.h>
namespace ecs{
	class ECSRegistry;
	class System
	{
	public:
		System(ECSRegistry* p_ECSRegistry, uint32_t p_ID, uint32_t p_Priority);
		System(std::shared_ptr<ECSRegistry> p_ECSRegistry, uint32_t p_ID, uint32_t p_Priority);
		~System();

		virtual void Initialize() {};
		virtual void Update(float deltaTime) {};
		virtual void Cleanup() {};

		uint32_t GetID() const;

		unsigned int GetPriority() const;
		void SetPriority(unsigned int p_Priority);

		bool operator==(const System& p_System);

	protected:
		uint32_t m_ID;
		uint32_t m_priority;
		std::shared_ptr<ECSRegistry> m_registry;
	};
}

