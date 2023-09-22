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

		virtual void Initialize() {};
		virtual void Execute() { std::cout << m_name << std::endl; };
		virtual void Release() {};

		uint32_t GetID() const;
		const String& GetName() const;
		const String& GetTag() const;
		
		void Activate();
		void Deactivate();
		bool IsActive() const;

		void SetStatic(bool p_Static);
		bool IsStatic() const;


		// Operador de igualdade para comparar duas entidades pelo ID
		bool operator==(const Entity& p_Other) const;

	private:
		uint32_t m_ID;
		String m_name;
		String m_tag;
		bool m_isActive;
		bool m_isStatic;
	};


}

