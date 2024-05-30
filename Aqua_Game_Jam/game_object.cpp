#include "game_object.h"


GameObject::GameObject()
    : Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), HitBox(0.0f,0.0f), Color(1.0f), Rotation(0.0f), Sprite(), IsSolid(false), Destroyed(false), ID(ID) { }

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec2 hitBox,glm::vec3 color, glm::vec2 velocity, std::string ID)
    : Position(pos), Size(size), Velocity(velocity), HitBox(hitBox),Color(color), Rotation(0.0f), Sprite(sprite), IsSolid(false), Destroyed(false), ID(ID) { }

void GameObject::Draw(SpriteRenderer& renderer, int flip)
{
    renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color, flip);
}

void GameObject::SetFrame(std::string tex)
{
    this->Sprite = ResourceManager::GetTexture(tex);
}

void GameObject::SetPos(glm::vec2 pos)
{
    this->Position = pos;
}