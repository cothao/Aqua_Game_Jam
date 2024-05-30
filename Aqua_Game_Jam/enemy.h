#ifndef ENEMY_H
#define ENEMY_H

#include "game_object.h"
#include <map>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "texture.h"
#include "shader.h"

enum class EnemyState
{
	IDLE,
	RUN,
	ATTACK,
};

class Enemy : public GameObject
{
public:
	glm::vec2   Position, Size, Velocity, HitBox;
	int			FrameRate;
	int			FrameNumber;
	float		AttackDmg;
	float		JumpHeight;
	float		CurrentHealth;
	float		MaxHealth;
	bool		Jumping;
	bool		Attacking;
	GameObject  Object;
	EnemyState State;

	void SetDmg(float dmg);
	void SetJumpHeight(float height);
	void SetCurrentHealth(float health);
	void SetMaxHealth(float health);

	Enemy();
	Enemy(GameObject* obj, float dmg, float jumpHeight, float currHealth, float maxHealth);

};

#endif // !ENEMEY_H
