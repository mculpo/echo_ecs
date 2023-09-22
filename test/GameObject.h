#include <header/Entity.h>
#pragma once

class GameObject : public ecs::Entity {
public:
	GameObject(uint32_t p_ID, const String& p_Name, const String& p_Tag)
		: Entity(p_ID, p_Name, p_Tag) {}
	~GameObject() {};
	// Herdado por meio de System
	virtual void Initialize() override {
		std::cout << m_name << std::endl;
	}
	virtual void Execute() override {

	}
	virtual void Release() override {

	}
};