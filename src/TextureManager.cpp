#include "./TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* filePath) {
    SDL_Surface* surface = IMG_Load(filePath);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void TextureManager::Draw(SDL_Texture* texture, 
                          SDL_Rect srcRect, 
                          SDL_Rect destRect, 
                          SDL_RendererFlip flip) {
    SDL_RenderCopyEx(Game::renderer, 
                     texture,
                     &srcRect,
                     &destRect,
                     0.0,
                     NULL,
                     flip);
}