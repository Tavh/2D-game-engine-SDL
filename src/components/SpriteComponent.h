#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL2/SDL.h>
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "../Animation.h"

class SpriteComponent : public Component {
private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;
    bool isAnimated;
    int numFrames;
    int animationSpeed;
    bool isFixed;
    std::map<std::string, Animation> animations;
    std::string currentAnimationName;
    unsigned int animationIndex = 0;

public:
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent(const char* filePath) {
        isAnimated = false;
        isFixed = false;
        SetTexture(filePath);
    }
    
    SpriteComponent(std::string id, int numFrames, int animationSpeed, bool hasDirections, bool isFixed) {
        this->isAnimated = true;
        this->numFrames = numFrames;
        this->animationSpeed = animationSpeed;
        this->isFixed = isFixed;

        if (hasDirections) {
            Animation downAnimation(0, numFrames, animationSpeed);
            Animation rightAnimation(1, numFrames, animationSpeed);
            Animation leftAnimation(2, numFrames, animationSpeed);
            Animation upAnimation(3, numFrames, animationSpeed);

            animations.emplace("DownAnimation", downAnimation);
            animations.emplace("RightAnimation", rightAnimation);
            animations.emplace("LeftAnimation", leftAnimation);
            animations.emplace("UpAnimation", upAnimation);

            this->animationIndex = 0;
            this->currentAnimationName = "DownAnimation"; // Whenever the sprite is constructed, we start with a down facing animation
        } else {
            Animation singleAnimation = Animation(0, numFrames, animationSpeed);
            animations.emplace("SingleAnimation", singleAnimation);
            this->animationIndex = 0;
            this->currentAnimationName = "SingleAnimation";
        }
        Play(this->currentAnimationName);
        SetTexture(id);
    }

    void Play(std::string animationName) {
        this->numFrames = animations[animationName].numFrames;
        this->animationIndex = animations[animationName].index;
        this->animationSpeed = animations[animationName].animationSpeed;
        this->currentAnimationName = animationName;
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
        if (isAnimated) {
            srcRect.x = (srcRect.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numFrames));
        }
        srcRect.y = animationIndex * transform->height;

        destRect.x = static_cast<int>(transform->position.x);
        destRect.y = static_cast<int>(transform->position.y);
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }

    void Render() override {
        TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
    }

};
#endif