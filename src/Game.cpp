#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "../lib/glm/glm.hpp"
#include "./components/TransformComponent.h"
#include "./components/SpriteComponent.h"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;

Game::Game() {
    this->isRunning = false;
}

Game::~Game() {}

bool Game::IsRunning() const {
    return this->isRunning;
}

void Game::Initialize(int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }
    this->window = SDL_CreateWindow(
        NULL, 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS
    );
    
    if (!window) {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }

    const int DEFAULT_DRIVER_INDEX = -1; // Driver basically means monitor in this contex
    const int NO_FLAGS_INDICATION = 0;
    this->renderer = SDL_CreateRenderer(window, DEFAULT_DRIVER_INDEX, NO_FLAGS_INDICATION);

    if (!renderer) {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }

    LoadLevel(0);

    this->isRunning = true;
    return;
}

void Game::LoadLevel(int levelNumber) {
    // Start including new assets to the assetMAnager list
    std::string textureFilePath = "./assets/images/tank-big-right.png";
    assetManager->AddTexture("tank-image", textureFilePath.c_str());

    // Start including entities and also components to them
	auto& newEntity(manager.AddEntity("tank"));
	newEntity.AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
    newEntity.AddComponent<SpriteComponent>("tank-image");

    manager.ListAllEntities();
}

void Game::ProcessInput() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_QUIT: 
            this->isRunning = false;
            break;

        case SDL_KEYDOWN: 
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    this->isRunning = false;
                    break;
                }

        default:
            break;
    }
}

void Game::Update() {
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);

    if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
        SDL_Delay(timeToWait);
    }

    // Delta time is the difference in ticks from the last frame converted to seconds
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

    // clamp deltaTime to a max value
    const float MAX_DELTA_TIME_VALUE = 0.05f;
    deltaTime = (deltaTime > MAX_DELTA_TIME_VALUE) ? MAX_DELTA_TIME_VALUE : deltaTime;

    // Sets the new ticks for the current frame to be used in the next pass
    ticksLastFrame = SDL_GetTicks();

    manager.Update(deltaTime);
}

void Game::Render() {
    SDL_SetRenderDrawColor(this->renderer, 21, 21, 21, 255);
    SDL_RenderClear(this->renderer);

    if (manager.HasNoEntities()) {
    	return;
    }
    manager.Render();

    SDL_RenderPresent(this->renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}
