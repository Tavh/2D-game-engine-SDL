#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "./Game.h"

class TextureManager {
public:
    static SDL_Texture* LoadTexture(const char* filePath);
    static void Draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip);

};

#endif