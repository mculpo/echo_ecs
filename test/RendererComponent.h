#include <ecs.hpp>
#pragma once
class RendererComponent : public ecs::Component {
public:
	RendererComponent(uint32_t p_ID) : Component(p_ID) {
		x = 5;
		y = 20;
	}
	~RendererComponent() {};

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