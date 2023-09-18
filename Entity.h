#pragma once
#include "core.h"
namespace ecs {
	class Entity
	{
	public:
		Entity(uint32_t p_ID, const String& p_Name, const String& p_Tag);
		~Entity();

		virtual void Initialize() {};
		virtual void Execute() {};
		virtual void Release() {};

		uint32_t GetID() const;
		const String& GetName() const;
		const String& GetTag() const;
		
		void Activate();
		void Deactivate();
		bool IsActive() const;

		void SetStatic(bool p_Static);
		bool IsStatic() const;
	private:
		uint32_t m_ID;
		std::bitset<MAX_COMPONENTS> m_components;
		String m_name;
		String m_tag;
		bool m_isActive;
		bool m_isStatic;
	};
}

