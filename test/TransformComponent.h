#include <ecs/ecs.hpp>
#pragma once
class TransformComponent : public ecs::Component {
public:
	TransformComponent(uint32_t p_ID,  float px, float py) : Component(p_ID) {
		x = px;
		y = py;
	}
	~TransformComponent() {};

	// Inherited via Component
	virtual void Initialize() override {
		
	}
	virtual void Execute() override {
		x++;
	}

private:
	float x;
	float y;
};
