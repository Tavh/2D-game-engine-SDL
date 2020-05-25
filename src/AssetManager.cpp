#include "./AssetManager.h"

AssetManager::AssetManager(EntityManager* manager): manager(manager) {

}

void AssetManager::ClearData() {
    this->textures.clear();
    this->fonts.clear();
}

void AssetManager::AddTexture(std::string textureId, const char* filePath) {
    this->textures.emplace(textureId, TextureManager::LoadTexture(filePath));
}

void AssetManager::AddFont(std::string fontId, const char* filePath, int fontSize) {
    fonts.emplace(fontId, FontManager::LoadFont(filePath, fontSize));
}

SDL_Texture* AssetManager::GetTexture(std::string textureId) {
    return this->textures[textureId];
}

TTF_Font* AssetManager::GetFont(std::string fontId) {
    return fonts[fontId];
}