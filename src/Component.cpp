#include <header/Component.h>
namespace ecs {
	Component::Component(uint32_t p_ID) :m_ID(p_ID){
	}
	Component::~Component()
	{
	}
	void Component::SetEntityID(uint32_t p_EntityID)
	{
		m_EntityID = p_EntityID;
	}
	uint32_t Component::GetID() const
	{
		return m_ID;
	}
	uint32_t Component::GetEntityID() const
	{
		return m_EntityID;
	}
	bool Component::operator==(const Component& p_Other) const
	{
		return m_ID == p_Other.GetID();
	}
}
