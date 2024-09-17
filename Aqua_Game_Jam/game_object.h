#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"
#include "resource_manager.h"


// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class GameObject
{
public:
    // object state
    glm::vec2   Position, Size, Velocity, HitBox;
    glm::vec3   Color;
    float       Rotation;
    bool        IsSolid;
    bool        Destroyed;
    int         Flip;
    std::string ID;
    // render state
    Texture2D   Sprite;
    // constructor(s)
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec2 hitBox, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f), std::string ID = "");
    // draw sprite
    virtual void Draw(SpriteRenderer& renderer);
    virtual void SetFrame(std::string);
    virtual void SetPos(glm::vec2 pos);
    virtual void Destroy();
    virtual void SetFlip(int flip);
};

#endif