#pragma once
#include <header/Core.h>
namespace ecs {
    class Component {
    public:
        Component(uint32_t p_ID);
        ~Component();

        virtual void Initialize() = 0;
        virtual void Execute() = 0;

        void SetEntityID(uint32_t p_EntityID);

        uint32_t GetID() const;
        uint32_t GetEntityID() const;

        // Implemente o operador de igualdade para comparar duas entidades pelo ID
        bool operator==(const Component& p_Other) const;
    private:
        uint32_t m_ID;
        uint32_t m_EntityID;
    };
}

