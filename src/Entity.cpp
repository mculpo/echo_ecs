#include <header/Entity.h>
namespace ecs {
	Entity::Entity(uint32_t p_ID, const String& p_Name, const String& p_Tag) :
		mID(p_ID), mName(p_Name), mTag(p_Tag)
	{
	}

	Entity::~Entity()
	{
	}

	bool Entity::operator==(const Entity& p_Other) const
	{
		return mID == p_Other.mID;
	}
}
