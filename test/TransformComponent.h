#include <header/Component.h>
#pragma once
class TransformComponent : public ecs::Component {
public:
	TransformComponent(uint32_t p_ID, String p_Name) : Component(p_ID) , m_Name(p_Name) {
		x = 10;
		y = 5;
	}
	~TransformComponent() {};

	// Inherited via Component
	virtual void Initialize() override {
		
	}
	virtual void Execute() override {
		x++;
		y = x * y * y;
		equation = (x + y) * 2 / 3;
	}

	float GetEquation() {
		return equation;
	}

private:
	String m_Name;
	float x;
	float y;
	float equation;
};
