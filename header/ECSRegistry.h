#pragma once
#include <header/Core.h>
#include <header/Entity.h>
#include <header/Component.h>
#include <header/System.h>

namespace ecs {
    class Entity;
    class Component;
    class System;
    struct ECSRegistry {
        std::vector<Entity*> mEntities;
        std::unordered_map<size_t, std::vector<Component*>> mComponents;
        std::vector<System*> mSystems;
    };
}

