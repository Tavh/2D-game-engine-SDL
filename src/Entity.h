#ifndef ENTITY_H
#define ENTITY_H
#include <vector>
#include <string>
#include "./EntityManager.h"
#include "./Component.h"
#include <iostream>
#include <map>

class EntityManager;
class Component;

class Entity {
private:
    EntityManager& manager;
    bool isActive;
    std::vector<Component*> components;
    std::map<const std::type_info*, Component*> componentTypeMap;
public:
    std::string name;
    Entity(EntityManager& manager);
    Entity(EntityManager&, std::string name);
    void Update(float deltaTime);
    void Render();
    void Destroy();
    bool IsActive() const;
    void ListAllComponents() const;
    template <typename T, typename... TArgs>
    T& AddComponent(TArgs&&... args) {
	    T* newComponent(new T(std::forward<TArgs>(args)...));
	    newComponent->owner = this;
	    this->components.emplace_back(newComponent);
        componentTypeMap[&typeid(*newComponent)] = newComponent;
	    newComponent->Initialize();
	    return *newComponent;
    }
};

#endif
