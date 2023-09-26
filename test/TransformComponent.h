#include <header/Component.h>
#pragma once
class TransformComponent : public ecs::Component {
public:
	TransformComponent(uint32_t p_ID, String p_Name) : Component(p_ID) , m_Name(p_Name) {
		x = 0;
		y = 0;
	}
	~TransformComponent() {};

	// Inherited via Component
	virtual void Initialize() override {

	}
	virtual void Execute() override {
		x++;
		y++;
	}
	virtual void Release() override {

	}

private:
	String m_Name;
	float x;
	float y;
};
