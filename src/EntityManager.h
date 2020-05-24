#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "./Component.h"
#include "./Entity.h"
#include <vector>
#include <iostream>

class EntityManager {
private:
    std::vector<Entity*> entities;
public:
    void ClearData();
    void Update(float deltaTime);
    void Render();
    bool HasNoEntities() const;
    Entity& AddEntity(std::string entityName, LayerType layer);
    std::vector<Entity*> GetEntities() const;
    std::vector<Entity*> GetEntitiesByLayer(LayerType layer) const;
    unsigned int GetEntityCount() const;
    void ListAllEntities() const;
    std::string CheckEntityCollisions(Entity& entity) const;
};

#endif
