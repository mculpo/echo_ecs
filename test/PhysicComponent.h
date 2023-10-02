#include <header/Component.h>
#pragma once
class PhysicComponent : public ecs::Component {
public:
	PhysicComponent(uint32_t p_ID) : Component(p_ID) {
		x = 1;
		y = 1;
	}
	~PhysicComponent() {};
	virtual void Initialize() override
	{
	}

	virtual void Execute() override
	{
		x = x * 2 + y;
	}

	float x;
	float y;
};