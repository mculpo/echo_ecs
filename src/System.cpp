#include <header/System.h>
namespace ecs {
	System::System(uint32_t p_ID, uint32_t p_Priority) : mID(p_ID), mPriority(p_Priority)
	{
	}
	System::~System()
	{
	}
	bool System::operator==(const System& p_System)
	{
		return mID == p_System.mID;
	}
}
