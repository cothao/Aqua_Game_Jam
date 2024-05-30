#include "enemy.h"

Enemy::Enemy()
	:AttackDmg(5.), JumpHeight(300.), CurrentHealth(100.), MaxHealth(100.), Jumping(false), Attacking(false), State() {};

Enemy::Enemy(GameObject* obj, float dmg, float jumpHeight, float currHealth, float maxHealth)
	:Object(*obj), AttackDmg(dmg), JumpHeight(jumpHeight), CurrentHealth(currHealth), MaxHealth(maxHealth), Position(obj->Position), Size(obj->Size), Velocity(obj->Velocity), Jumping(), Attacking() {}


