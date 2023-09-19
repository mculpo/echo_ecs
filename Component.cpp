#include "Component.h"
namespace ecs {
	Component::Component(uint32_t p_ID) :m_ID(p_ID), m_isActive(true)
	{
	}
	Component::~Component()
	{
	}
	void Component::Activate()
	{
		m_isActive = true;
	}
	void Component::Deactivate()
	{
		m_isActive = false;
	}
	bool Component::IsActive() const
	{
		return m_isActive;
	}
	uint32_t Component::GetID() const
	{
		return m_ID;
	}
	bool Component::operator==(const Component& p_Other) const
	{
		return m_ID == p_Other.GetID();
	}
}
