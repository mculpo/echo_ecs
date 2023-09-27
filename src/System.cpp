#include <header/System.h>
namespace ecs {
	System::System(ECSRegistry* p_ECSRegistry, uint32_t p_ID, uint32_t p_Priority) : m_registry(p_ECSRegistry), m_ID(p_ID), m_priority(p_Priority)
	{
	}
	System::~System()
	{
	}
	uint32_t System::GetID() const
	{
		return m_ID;
	}
	unsigned int System::GetPriority() const
	{
		return m_priority;
	}
	void System::SetPriority(unsigned int p_Priority)
	{
		m_priority = p_Priority;
	}
	bool System::operator==(const System& p_System)
	{
		return m_ID == p_System.GetID();
	}
}
