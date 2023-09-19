#include "Entity.h"
namespace ecs {
	Entity::Entity(uint32_t p_ID, const String& p_Name, const String& p_Tag) :
		m_ID(p_ID), m_name(p_Name), m_tag(p_Tag), m_isActive(true), m_isStatic(false)
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
	void Entity::Activate()
	{
		m_isActive = true;
	}
	void Entity::Deactivate()
	{
		m_isActive = false;
	}
	bool Entity::IsActive() const
	{
		return m_isActive;
	}
	void Entity::SetStatic(bool p_Static)
	{
		m_isStatic = p_Static;
	}
	bool Entity::IsStatic() const
	{
		return m_isStatic;
	}
	bool Entity::operator==(const Entity& p_Other) const
	{
		return m_ID == p_Other.GetID();
	}
}
