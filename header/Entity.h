#pragma once
#include <header/Core.h>
#include <header/Component.h>
namespace ecs {
	class Component;

	class Entity
	{
	public:
		Entity(uint32_t p_ID, const String& p_Name, const String& p_Tag);
		~Entity();

		virtual void Initialize() = 0;
		virtual void Execute() = 0;

		uint32_t GetID() const;
		const String& GetName() const;
		const String& GetTag() const;

		// Operador de igualdade para comparar duas entidades pelo ID
		bool operator==(const Entity& p_Other) const;

	private:
		uint32_t m_ID;
	protected:
		String m_name;
		String m_tag;
	};


}

