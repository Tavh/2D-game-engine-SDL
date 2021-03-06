#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component {
private:

public:
    Entity* owner;
    ~Component() {}
    virtual void Initialize() {}
    virtual void Update(float deltaTime) {}
    virtual void Render() {}
};

#endif COMPONENT_H
