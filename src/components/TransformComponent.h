#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <SDL2/SDL.h>
#include <bits/stdc++.h>
#include "../EntityManager.h"
#include "../../lib/glm/glm.hpp"
#include "../Game.h"

class TransformComponent : public Component{
public:
    int width;
    int height;
    glm::vec2 position;
    glm::vec2 velocity;
    int scale;

    TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s) {
        position = glm::vec2(posX, posY);
        velocity = glm::vec2(velX, velY);
        width = w;
        height = h;
        scale = s;
    }

    void Initialize() override {

    }

    void Update(float deltaTime) override {
        int velocityX = velocity.x * deltaTime;
        int velocityY = velocity.y * deltaTime;

        position.x += velocityX;
        position.y += velocityY;

        // position.x = clamp(position.x + velocityX, -10, WINDOW_WIDTH);
        // position.y = clamp(position.y + velocityY, -10, WINDOW_HEIGHT);
    }

    double clamp(double d, double min, double max) {
        const double t = d < min ? min : d;
        return t > max ? max : t;
    }

    void Render() override {}
};
#endif