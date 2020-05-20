#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "./Component.h"
#include "EntityManager.h"

class Game {
private:
    bool isRunning;
    SDL_Window *window;
    int ticksLastFrame;
public:
    static SDL_Renderer* renderer;

    Game();
    ~Game();
    bool IsRunning() const;
    void Initialize(int width, int height);
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();
    void LoadLevel(int levelNumber);
};
#endif
