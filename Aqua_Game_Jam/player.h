#ifndef PLAYER_H
#define PLAYER_H

#include "game_object.h"
#include <map>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "texture.h"
#include "shader.h"
enum PlayerState
{
	IDLE,
	RUN,
	ATTACK
};

class Player: public GameObject
{
public:
	glm::vec2   Position, Size, Velocity, HitBox;
	int			FrameRate;
	int			FrameNumber;
	int			ID;
	float		AttackDmg;
	float		JumpHeight;
	float		CurrentHealth;
	float		MaxHealth;
	bool		Jumping;
	bool		Attacking;
	GameObject  Object;
	PlayerState State;

	void SetDmg(float dmg);
	void SetJumpHeight(float height);
	void SetCurrentHealth(float health);
	void SetMaxHealth(float health);

	Player();
	Player(GameObject* obj, float dmg, float jumpHeight, float currHealth, float maxHealth);

};

#endif // !