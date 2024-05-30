#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game_level.h"

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(120.0f, 60.0f);
const glm::vec2 HITBOX_SIZE(120.0f, 60.0f);
// Initial velocity of the player paddle
const glm::vec2 PLAYER_VELOCITY = glm::vec2(500.0f,300.0f);

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
    // game state
    GameState               State;
    bool                    Keys[1024];
    bool                    Mouse[1024];
    bool                    grounded;
    unsigned int            Width, Height;
    std::vector<GameLevel>  Levels;
    unsigned int            Level;
    // constructor/destructor
    Game(unsigned int width, unsigned int height);
    ~Game();
    // initialize game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void ProcessInput(float dt);
    // this function must be called in the while loop
    // it allows the use of mouse clicks in game
    void ProcessMouseInput(float dt);
    void DoCollisions();
    void Update(float dt);
    void Render(int fn);
};

#endif