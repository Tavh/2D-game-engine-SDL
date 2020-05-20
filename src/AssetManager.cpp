#include "./AssetManager.h"

AssetManager::AssetManager(EntityManager* manager): manager(manager) {

}

void AssetManager::ClearData() {
    this->textures.clear();
}

void AssetManager::AddTexture(std::string textureId, const char* filePath) {
    this->textures.emplace(textureId, TextureManager::LoadTexture(filePath));
}

SDL_Texture* AssetManager::GetTexture(std::string textureId) {
    return this->textures[textureId];
}