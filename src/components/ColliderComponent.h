#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "../EntityManager.h"
#include "./TransformComponent.h"
#include "../TextureManager.h"
#include "../AssetManager.h"

class ColliderComponent : public Component {
public:
    std::string colliderTag;
    SDL_Rect collider;
    SDL_Rect srcRect;
    SDL_Rect destRect;
    TransformComponent* transform;
    SDL_Texture* colliderBoundingBoxTexture;

    ColliderComponent(std::string colliderTag, int x, int y, int w, int h) {
        this->colliderTag = colliderTag;
        this->collider = { x, y, w, h };
        colliderBoundingBoxTexture = Game::assetManager->GetTexture("collision-box");
    }

    void Initialize() override {
        if (owner->HasComponent<TransformComponent>()) {
            transform = owner->GetComponent<TransformComponent>();
            srcRect = { 0, 0, transform->width, transform->height };
            destRect = { collider.x, collider.y, collider.w, collider.h };
        }
    }

    void Update(float deltaTime) override {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;
        destRect.x = collider.x - Game::camera.x;
        destRect.y = collider.y - Game::camera.y;
    }

    void Render() override {
        TextureManager::Draw(colliderBoundingBoxTexture, srcRect, destRect, SDL_FLIP_NONE);
    }
};
#endif