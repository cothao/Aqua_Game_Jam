#include "player.h"

Player::Player()
	:AttackDmg(5.), JumpHeight(300.), CurrentHealth(100.), MaxHealth(100.), Jumping(false), Attacking(false), State(IDLE) {};

Player::Player(GameObject* obj, float dmg, float jumpHeight, float currHealth, float maxHealth)
	:Object(*obj), AttackDmg(dmg), JumpHeight(jumpHeight), CurrentHealth(currHealth), MaxHealth(maxHealth), Position(obj->Position), Size(obj->Size), Velocity(obj->Velocity), Jumping(), Attacking() {};

void Player::SetDmg(float dmg)
{
	this->AttackDmg = dmg;
}

void Player::SetJumpHeight(float height)
{
	this->JumpHeight = height;
}

void Player::SetCurrentHealth(float health)
{
	this->CurrentHealth = health;
}

void Player::SetMaxHealth(float health)
{
	this->MaxHealth = health;
}