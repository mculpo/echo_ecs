#include <ecs/ecs.hpp>
#pragma once
class TransformComponent : public ecs::Component {
public:
	TransformComponent(uint32_t p_ID, String pName, float px, float py) : Component(p_ID) {
		x = px;
		y = py;
		mName = pName;
	}
	~TransformComponent() {};

	// Inherited via Component
	virtual void Initialize() override {
		
	}
	virtual void Execute() override {
		/*std::cout << mName << std::endl;
		std::cout << x << "-" << y << std::endl << std::endl;*/
	}

	float GetEquation() {
		return equation;
	}

private:
	String mName;
	float x;
	float y;
	float equation;
};
