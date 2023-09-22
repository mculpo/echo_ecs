# Entity Component System (ECS) Library (Simple and Accessible)

This is a straightforward and accessible C++ Entity Component System (ECS) library that provides an uncomplicated way to manage game entities, components, and systems. ECS is a widely-used design pattern in game development that simplifies the organization of game objects' data and logic, making it ideal for both beginners and experienced developers.

## Contents

- [Introduction](#introduction)
- [Entities, Components, and Systems](#entities-components-and-systems)
- [ECSRegistry](#ecsregistry)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Creating Entities](#creating-entities)
  - [Attaching Components](#attaching-components)
  - [Registering Systems](#registering-systems)
  - [Using ECSRegistry Methods](#using-ecsregistry-methods)
- [License](#license)

## Introduction

The Entity Component System (ECS) architecture is commonly used in game development to structure game entities, their attributes (components), and the logic that operates on them (systems). This repository provides a user-friendly C++ implementation of an ECS framework, making it ideal for simple and accessible game development projects.

## Entities, Components, and Systems

In ECS, entities, components, and systems play distinct roles in managing game data and behavior.

### Entity

An entity is a fundamental object in the ECS architecture. It is essentially a container for components, representing a game object. Entities are lightweight and typically consist of an identifier and a collection of attached components.

### Component

A component represents a specific aspect or attribute of an entity. Components are designed to be small, reusable, and self-contained, focusing on a single piece of functionality or data. For example, you might have components for graphics, physics, or behavior.

### System

A system is responsible for processing entities and their associated components. Systems encapsulate the logic that operates on entities and their components. Each system typically focuses on a specific aspect of the game, such as rendering, collision detection, or AI behavior.

## ECSRegistry

The `ECSRegistry` class is the heart of this ECS library, providing methods for managing entities, components, and systems.

## Features

- **Effortless Entity Management**: Create, register, and remove game entities with simplicity in mind.
- **Component Attachment Made Easy**: Attach components to entities and remove them without hassle.
- **Straightforward System Integration**: Register systems to process entities and their components with ease.
- **Dynamic and Efficient**: Offers flexibility and performance through a dynamic component-based architecture.
- **User-Friendly Type-Safe Operations**: Utilizes C++ templates to ensure type safety when working with components, making it accessible for developers of all levels.

## Getting Started

To use this ECS library in your project, follow these steps:

### Creating Entities

To create an entity, follow these steps:

```cpp
#include "ECSRegistry.h"

ecs::ECSRegistry registry;
std::shared_ptr<ecs::Entity> entity = std::make_shared<ecs::Entity>();
registry.RegisterEntity(entity);
```
### Attaching Components

To attach a component to an entity, follow these steps:

```cpp
#include "ECSRegistry.h"
#include "YourComponent.h" // Replace with your component class header

ecs::ECSRegistry registry;
std::shared_ptr<ecs::Entity> entity = std::make_shared<ecs::Entity>();
std::shared_ptr<YourComponent> component = std::make_shared<YourComponent>();
registry.RegisterEntity(entity);
registry.RegisterComponentToEntity(entity, component)
```

### Registering Systems

To register a system, follow these steps:

```cpp
#include "ECSRegistry.h"
#include "YourSystem.h" // Replace with your system class header

ecs::ECSRegistry registry;
std::shared_ptr<YourSystem> system = std::make_shared<YourSystem>();
registry.RegisterSystem(system);
```

### Using ECSRegistry Methods

Here are some examples of how to use methods provided by ECSRegistry:

```cpp
ecs::ECSRegistry registry;

// Get all entities with a HealthComponent
std::vector<std::shared_ptr<HealthComponent>> entitiesWithHealth = registry.GetEntitiesWithComponent<HealthComponent>();

// Get the WeaponComponent for a specific player entity
std::shared_ptr<WeaponComponent> weaponComponent = registry.GetComponentForEntity<WeaponComponent>(playerEntity);

// Get all components of a specific type
std::vector<std::shared_ptr<RendererComponent>> allComponents = registry.GetAllComponent<RendererComponent>();
```

### License
This project is licensed under the Apache-2.0 license.
