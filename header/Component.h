#pragma once
#include <header/Core.h>
#include <header/Entity.h>
#include "ECSRegistry.h"
namespace ecs {
    class Entity;
    class Component {
    public:
        uint32_t mID;
        Entity* mEntity;
        Component(uint32_t p_ID);
        ~Component();

        virtual void Initialize() = 0;
        virtual void Execute() = 0;

        // Implemente o operador de igualdade para comparar duas entidades pelo ID
        bool operator==(const Component& p_Other) const;
    };
}

