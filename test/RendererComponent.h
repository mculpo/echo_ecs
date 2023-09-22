#include <header/Component.h>
#pragma once
class RendererComponent : public ecs::Component {
public:
	RendererComponent(uint32_t p_ID, String p_Name) : Component(p_ID) , m_Name(p_Name) {
	}
	~RendererComponent() {};

	// Inherited via Component
	virtual void Initialize() override {

	}
	virtual void Execute() override {
		std::cout << m_Name << std::endl;
	}
	virtual void Release() override {

	}

private:
	String m_Name;
};
