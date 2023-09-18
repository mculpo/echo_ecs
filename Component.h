#pragma once
#include <Core.h>
namespace ecs {
    class Component {
    public:
        Component(uint32_t p_ID);
        ~Component();

        virtual void Initialize() {};
        virtual void Execute() {};
        virtual void Release() {};

        void Activate();
        void Deactivate();
        bool IsActive() const;
        uint32_t GetID() const;

    private:
        uint32_t m_ID;
        bool m_isActive;
    };
}

