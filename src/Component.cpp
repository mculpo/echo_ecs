#include <header/Component.h>
namespace ecs {
	Component::Component(uint32_t p_ID) : mID(p_ID), mEntity(nullptr) {
	}
	Component::~Component()
	{
	}
	bool Component::operator==(const Component& p_Other) const
	{
		return mID == p_Other.mID;
	}
}
