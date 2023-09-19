#pragma once
#include <Core.h>
namespace ecs {
    class Component {
    public:
        Component(uint32_t p_ID);
        ~Component();

        virtual void Initialize() = 0;
        virtual void Execute() = 0;
        virtual void Release() = 0;

        void Activate();
        void Deactivate();
        bool IsActive() const;
        uint32_t GetID() const;

        // Implemente o operador de igualdade para comparar duas entidades pelo ID
        bool operator==(const Component& p_Other) const;
    private:
        uint32_t m_ID;
        bool m_isActive;
    };
}

