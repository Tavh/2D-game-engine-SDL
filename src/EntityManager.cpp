#include "EntityManager.h"

void EntityManager::ClearData() {
    for (auto& entity : this->entities) {
        entity->Destroy();
    }
}

bool EntityManager::HasNoEntities() const {
    return this->entities.size() == 0;
}

void EntityManager::Update(float deltaTime) {
    for (auto& entity : this->entities) {
        entity->Update(deltaTime);
    }
}

void EntityManager::Render() {
    for (int layerNumber = 0; layerNumber < NUM_LAYERS; layerNumber++) {
        for (auto& entity : GetEntitiesByLayer(static_cast<LayerType>(layerNumber))) {
            entity->Render();
        }
    }
}

Entity& EntityManager::AddEntity(std::string entityName, LayerType layer) {
    Entity* entity = new Entity(*this, entityName, layer);
    entities.emplace_back(entity);
    return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const {
    return this->entities;
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const {
    std::vector<Entity*> selectedEntities;
    for (auto& entity : this->entities) {
        if (entity->layer == layer) {
            selectedEntities.emplace_back(entity);
        }
    }
    return selectedEntities;
}

unsigned int EntityManager::GetEntityCount() const {
    return this->entities.size();
}

void EntityManager::ListAllEntities() const {
    unsigned int entityIndex = 0;
    for (auto& entity : this->entities) {
        std::cout << "Entity" << "[" << entityIndex << "]" << "name: " << entity->name 
        << "\ncomponents:" << std::endl;

        entity->ListAllComponents();

        std::cout << "********************************************" << std::endl;
        entityIndex++;
    }
}