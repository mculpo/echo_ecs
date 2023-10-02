#include <header/Entity.h>
namespace ecs {
	Entity::Entity(uint32_t p_ID, const String& p_Name, const String& p_Tag) :
		m_ID(p_ID), m_name(p_Name), m_tag(p_Tag)
	{
	}

	Entity::~Entity()
	{
	}

	uint32_t Entity::GetID() const
	{
		return m_ID;
	}

	const String& Entity::GetName() const
	{
		return m_name;
	}

	const String& Entity::GetTag() const
	{
		return m_tag;
	}
	bool Entity::operator==(const Entity& p_Other) const
	{
		return m_ID == p_Other.GetID();
	}
}
