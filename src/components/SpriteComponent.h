#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL2/SDL.h>
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "./TransformComponent.h"

class SpriteComponent : public Component {
private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;

public:
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent(const char* filePath) {
        SetTexture(filePath);
    }
    
    void SetTexture(std::string assetTextureId) {
        texture = Game::assetManager->GetTexture(assetTextureId);
    }


    void Initialize() override {
        this->transform = owner->GetComponent<TransformComponent>();
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;
    }

    void Update(float deltaTime) override {
        destRect.x = (int) transform->position.x;
        destRect.y = (int) transform->position.y;
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }

    void Render() override {
        TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
    }

};
#endif