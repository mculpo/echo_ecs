#pragma once
#include <header/Core.h>
#include <header/Component.h>
namespace ecs {
	class Component;

	class Entity
	{
	public:
		uint32_t mID;
		String mName;
		String mTag;

		Entity(uint32_t p_ID, const String& p_Name, const String& p_Tag);
		~Entity();

		virtual void Initialize() = 0;
		virtual void Execute() = 0;

		// Operador de igualdade para comparar duas entidades pelo ID
		bool operator==(const Entity& p_Other) const;		
	};


}

