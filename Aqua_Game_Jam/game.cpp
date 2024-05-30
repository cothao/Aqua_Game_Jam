#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "game_level.h"
#include "game_object.h"
#include "player.h"
#include "enemy.h"
#include "iostream"
#include <ft2build.h>
#include FT_FREETYPE_H  
#include "text_renderer.h"

SpriteRenderer* Renderer;
SpriteRenderer* PlayerRenderer;
TextRenderer* Text;
Player* User;
std::vector<Player*> ; 
GameObject* swordBox;
GameObject* Mate;
GameObject* Mark;
GameObject* water_background;
GameObject* DialogueBox;
GameObject* Meat;
std::vector<GameObject*> trees1;
std::vector<GameObject*> trees2;
std::vector<GameObject*> trees3;
std::vector<GameObject*> trees4;
std::vector<GameObject*> rocks;
std::vector<GameObject*> boatPeople;
std::vector<GameObject*> boats;
std::vector<GameObject*> grassMiddle;
std::vector<GameObject*> dirtMiddle;
std::vector<Player*> babies;
std::vector<Enemy*> enemies;
glm::vec2 brickPos = glm::vec2(0.);
std::vector<TextRenderer*> MateOptions;
glm::vec2 matePos = glm::vec2(100., 500.);
glm::vec2 wbPos = glm::vec2(0., -1000.);
glm::vec2 markPos = glm::vec2(110., 500.); 
glm::vec2 treePos = glm::vec2(0., -30.);
glm::vec2 rockPos = glm::vec2(0., 0.);
glm::vec2 grassMidPos = glm::vec2(0., 0.);
glm::vec2 dirtMidPos = glm::vec2(0., 0.);
std::vector<GameObject*> allObjs;
std::string currAnim = "face";
std::string babyAnim = "face";
std::string currEnemAnim = "boar_idle";
float pAttackDmg = 5.0, prevPositionX = 0, prevPositionY = 0, pVelocityY = 0.0, pVelocityX = 0.0, enemyVelocity = 0.07, ePrevPosX = 0., ePrevPosY = 0., gravity = 600.f, jumpHeight = .0f, currHealth = 100.0, maxHealth = 100.0, enemyHealth = 100., enemyMaxHealth = 100. , i = 0., prevI = 0.;
static float lerp(float x, glm::vec2 sp, glm::vec2 ep);
bool DialogueInbound = false, isJumping = false, canMove = true, enemyGrounded = false, hit = false, isAttacking = false;
int babyAmt = 0, meatAmt = 0, mateFlipX = 0, hitButton = 0, selectedText = 0, selectedOption = 0, swordHit = 0, flip = 1, eFlip = 1, efn = 1, pfn = 1, enframeRate = 0, currFn = 0, rowerFn = 1, pCurrFn = 0, leftClick = 0;;
std::map<std::string, float> checkVelocity(GameObject&, float dt);
void moveToObject(GameObject one);


template<class T, class U>
bool CheckCollision(T one, U two);

//template<class T, class U>
//void moveToObject(T one, U two);




enum class enemyAnims
{
    IDLE,
    RUN,
    ATTACK
};

enum class playerAnims
{
    IDLE,
    RUN,
    ATTACK
};

enemyAnims enemyAnim = enemyAnims::IDLE;

playerAnims playerAnim = playerAnims::IDLE;


Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height), grounded(false)
{

}

Game::~Game()
{
    delete Renderer;
    delete User;
    delete Text;
    delete swordBox;
    delete Mate;
    delete water_background;
    delete Mark;
    delete Meat;
    delete DialogueBox;
    for (Player* baby : babies)
    {
        delete baby;
    }
}

void Game::Init()
{
    
    // load shaders
    ResourceManager::LoadShader("./shader.vs", "./shader.fs", nullptr, "sprite");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

    // set render-specific controls
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

    // IDLE
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/pirahna/pirahnna_idle_0.png", true, "face1");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/pirahna/pirahnna_idle_1.png", true, "face2");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/pirahna/pirahnna_idle_2.png", true, "face3");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/pirahna/pirahnna_idle_3.png", true, "face4");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/pirahna/pirahnna_idle_4.png", true, "face5");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/pirahna/pirahnna_idle_5.png", true, "face6");
    
    // ASSETS
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Pictures/textures/menu_pic.png", false, "menu_pic");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/assets/GUI/dialogue_box.png", true, "dialogue_box");

    // RUN
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/idle_knight/run_00.png", true, "run1");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/idle_knight/run_01.png", true, "run2");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/idle_knight/run_02.png", true, "run3");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/idle_knight/run_03.png", true, "run4");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/idle_knight/run_04.png", true, "run5");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/idle_knight/run_05.png", true, "run6");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/idle_knight/run_06.png", true, "run7");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/idle_knight/run_07.png", true, "run8");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/idle_knight/run_08.png", true, "run9");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/idle_knight/run_09.png", true, "run10");

    // JUMP
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/idle_knight/jump_00.png", true, "jump1");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/idle_knight/jump_01.png", true, "jump2");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/idle_knight/jump_02.png", true, "jump3");

    // ATTACK
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/pirahna/attack_0.png", true, "attack1");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/pirahna/attack_1.png", true, "attack2");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/pirahna/attack_2.png", true, "attack3");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/pirahna/attack_3.png", true, "attack4");


    // ENEMY IDLE
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/boar/boar_idle_0.png", true, "boar_idle1");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/boar/boar_idle_1.png", true, "boar_idle2");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/boar/boar_idle_2.png", true, "boar_idle3");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/boar/boar_idle_3.png", true, "boar_idle4");

    // ENEMY RUN

    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/boar/boar_run_0.png", true, "boar_run1");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/boar/boar_run_1.png", true, "boar_run2");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/boar/boar_run_2.png", true, "boar_run3");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/boar/boar_run_3.png", true, "boar_run4");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/boar/boar_run_4.png", true, "boar_run5");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/animations/boar/boar_run_5.png", true, "boar_run6");
    // load textures
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/assets/food/meat.png", true, "meat");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/assets/tiles/grass_tile.png", true, "grassMid");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/assets/tiles/dirt_tile.png", true, "dirtMid");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/assets/Dock/water.png", true, "water");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/assets/Dock/6.png", true, "water_background");

    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/assets/Dock/2.png", true, "trees1");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/assets/Dock/3.png", true, "trees2");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/assets/Dock/4.png", true, "trees3");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/assets/Dock/5.png", true, "trees4");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/assets/Dock/7.png", true, "rocks");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Pictures/textures/block_solid.png", false, "block_solid");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Pictures/textures/paddle.png", true, "paddle");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/assets/speech_indicators/exclamation_0.png", true, "exclamation1");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/assets/speech_indicators/exclamation_1.png", true, "exclamation2");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/assets/speech_indicators/exclamation_2.png", true, "exclamation3");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/assets/speech_indicators/exclamation_3.png", true, "exclamation4");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/assets/speech_indicators/exclamation_4.png", true, "exclamation5");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/assets/speech_indicators/exclamation_5.png", true, "exclamation6");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/assets/Dock/0.png", true, "background");

    // Load boats
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/assets/rower/sprite_0.png", true, "rower1");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/assets/rower/sprite_1.png", true, "rower2");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/assets/rower/sprite_2.png", true, "rower3");
    ResourceManager::LoadTexture("C:/Users/colli/OneDrive/Documents/assets/rower/sprite_3.png", true, "rower4");



    // load levels
    GameLevel one; one.Load("one.lvl", this->Width, this->Height);
    GameLevel two; two.Load("two.lvl", this->Width, this->Height);
    GameLevel three; three.Load("levels/three.lvl", this->Width, this->Height / 2);
    GameLevel four; four.Load("levels/four.lvl", this->Width, this->Height / 2);
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);
    this->Level = 0;

    // configure game objects
    glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height/2.);
    glm::vec2 enemyPos = glm::vec2(this->Width / 2.0f / 2.0f, 0);
    //glm::vec2 hitBoxPos = glm::vec2(playerPos.x, playerPos.y);
    User = new Player(new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("face1"), HITBOX_SIZE, glm::vec3(1.), PLAYER_VELOCITY, "PLAYER"), 5.,5.,5.,5.);
    
    swordBox = new GameObject(glm::vec2(User->Position.x + (flip * 135), User->Position.y + 70.), glm::vec2(50., 30.), ResourceManager::GetTexture(""), glm::vec2(1.), glm::vec3(0.), glm::vec2(0.), "hitbox");
    Mate = new GameObject(matePos, PLAYER_SIZE, ResourceManager::GetTexture("face1"), HITBOX_SIZE, glm::vec3(1.), PLAYER_VELOCITY, "MATE");
    water_background = new GameObject(wbPos, glm::vec2(10000,3000), ResourceManager::GetTexture("water_background"), HITBOX_SIZE, glm::vec3(1.), PLAYER_VELOCITY, "wb");
    Mark = new GameObject(glm::vec2(Mate->Position.x + 50, Mate->Position.y - 20.), glm::vec2(30, 30), ResourceManager::GetTexture("exclamation1"), HITBOX_SIZE, glm::vec3(1.), PLAYER_VELOCITY, "wb");
    DialogueBox = new GameObject(glm::vec2(this->Width / 2. - 200000., this->Height - 12000.), glm::vec2(400, 100), ResourceManager::GetTexture("dialogue_box"), HITBOX_SIZE, glm::vec3(1.), PLAYER_VELOCITY, "wb");
    Meat = new GameObject(glm::vec2(0.), glm::vec2(50, 50), ResourceManager::GetTexture("meat"), HITBOX_SIZE, glm::vec3(1.), PLAYER_VELOCITY, "wb");

    for (int i = 0; i < 30; i++)
    {
        trees1.push_back(new GameObject(glm::vec2((treePos.x + 300.) * (float)i, treePos.y ), glm::vec2(300, 300), ResourceManager::GetTexture("trees1"), HITBOX_SIZE, glm::vec3(1.), PLAYER_VELOCITY, "wb"));
    }

    for (int i = 0; i < 30; i++)
    {
        trees2.push_back(new GameObject(glm::vec2((treePos.x + 300.) * (float)i, treePos.y), glm::vec2(300, 700), ResourceManager::GetTexture("trees2"), HITBOX_SIZE, glm::vec3(1.), PLAYER_VELOCITY, "wb"));
    }

    for (int i = 0; i < 30; i++)
    {
        trees3.push_back(new GameObject(glm::vec2((treePos.x + 300.) * (float)i, treePos.y ), glm::vec2(300, 700), ResourceManager::GetTexture("trees3"), HITBOX_SIZE, glm::vec3(1.), PLAYER_VELOCITY, "wb"));
    }

    for (int i = 0; i < 30; i++)
    {
        trees4.push_back(new GameObject(glm::vec2((treePos.x + 300.) * (float)i, treePos.y ), glm::vec2(300, 700), ResourceManager::GetTexture("trees4"), HITBOX_SIZE, glm::vec3(1.), PLAYER_VELOCITY, "wb"));
    }

    for (int i = 0; i < 30; i++)
    {
        rocks.push_back(new GameObject(glm::vec2((rockPos.x + 300.) * (float)i, 0.), glm::vec2(300, 700), ResourceManager::GetTexture("rocks"), HITBOX_SIZE, glm::vec3(1.), PLAYER_VELOCITY, "wb"));
    }

    for (int i = 0; i < 30; i++)
    {
        grassMiddle.push_back(new GameObject(glm::vec2((-100.) * (float)i, 250.), glm::vec2(100, 100), ResourceManager::GetTexture("grassMid"), HITBOX_SIZE, glm::vec3(1.), PLAYER_VELOCITY, "wb"));
    }

    for (int i = 0; i < 2; i++)
    {
        boats.push_back(new GameObject(glm::vec2((-100) * (float)i, 260.), glm::vec2(100, 50), ResourceManager::GetTexture("rower1"), HITBOX_SIZE, glm::vec3(1.), PLAYER_VELOCITY, "wb"));

    }

    for (int i = 0; i < 30; i++)
    {
        dirtMiddle.push_back(new GameObject(glm::vec2((-100.) * (float)i, 330.), glm::vec2(100, 100), ResourceManager::GetTexture("dirtMid"), HITBOX_SIZE, glm::vec3(1.), PLAYER_VELOCITY, "wb"));
    }

    for (int i = 0; i < 30; i++)
    {
        dirtMiddle.push_back(new GameObject(glm::vec2((-100.) * (float)i, 400.), glm::vec2(100, 100), ResourceManager::GetTexture("dirtMid"), HITBOX_SIZE, glm::vec3(1.), PLAYER_VELOCITY, "wb"));
    }

    for (int i = 0; i < 30; i++)
    {
        dirtMiddle.push_back(new GameObject(glm::vec2((-100.) * (float)i, 470.), glm::vec2(100, 100), ResourceManager::GetTexture("dirtMid"), HITBOX_SIZE, glm::vec3(1.), PLAYER_VELOCITY, "wb"));
    }

    for (int i = 0; i < 30; i++)
    {
        dirtMiddle.push_back(new GameObject(glm::vec2((-100.) * (float)i, 540.), glm::vec2(100, 100), ResourceManager::GetTexture("dirtMid"), HITBOX_SIZE, glm::vec3(1.), PLAYER_VELOCITY, "wb"));
    }

    for (int i = 0; i < 30; i++)
    {
        dirtMiddle.push_back(new GameObject(glm::vec2((-100.) * (float)i, 610.), glm::vec2(100, 100), ResourceManager::GetTexture("dirtMid"), HITBOX_SIZE, glm::vec3(1.), PLAYER_VELOCITY, "wb"));
    }

    for (int i = 0; i < 30; i++)
    {
        dirtMiddle.push_back(new GameObject(glm::vec2((-100.) * (float)i, 680.), glm::vec2(100, 100), ResourceManager::GetTexture("dirtMid"), HITBOX_SIZE, glm::vec3(1.), PLAYER_VELOCITY, "wb"));
    }

    enemies.push_back(new Enemy(new GameObject(enemyPos, PLAYER_SIZE, ResourceManager::GetTexture("boar_idle1"), HITBOX_SIZE, glm::vec3(1.), PLAYER_VELOCITY, "ENEMY"), 5., 5., 5. ,5.));
    //Renderer->DrawSprite(ResourceManager::GetTexture(""), glm::vec2(Player->Position.x + ((flip * 135)), Player->Position.y + 70.), glm::vec2(100., 50.), 0.0f, glm::vec3(1.));

    Text = new TextRenderer(this->Width, this->Height);
    Text->Load("fonts/OpenSans-Bold.TTF", 30);

    //for (int i = 0; i < 3; i++)
    //{
    //    MateOptions.push_back(new Text);
    //}

}

void Game::Update(float dt)
{

    if (this->State == GAME_ACTIVE)
    {

        //std::cout << currAnim << "\n";

        //Dialogue
        if (DialogueInbound)
        {
            DialogueBox->Position = glm::vec2(this->Width / 2. - 200., this->Height - 120.);
        }
        else
        {
            DialogueBox->Position = glm::vec2(this->Width / 2. - 200000., this->Height - 12000.);
        }

        // MATE

        if (Mate->Position.x > User->Object.Position.x)
        {
            mateFlipX = 0;
        }
        else
        {
            mateFlipX = 1;

        }

        if (CheckCollision<GameObject, GameObject>(*Mate, User->Object))
        {
            Mark->Position = glm::vec2(Mate->Position.x + 50, Mate->Position.y - 20.);

        }
        else
        {
            Mark->Position = glm::vec2(Mate->Position.x + 5000, Mate->Position.y - 2000.);
        }

        // boatPerson
        for (GameObject* boatPerson: boats)
        {
            boatPerson->Position.y = rocks[0]->Position.y + 260.;
            boatPerson->Position.x += 200. * dt;
        }

        // grass
        for (GameObject* grass : grassMiddle)
        {
            grass->Position.y = rocks[0]->Position.y + 260.;
            //grass->Position.x = rocks[0]->Position.x - 260.;
        }

        int grassI = 0;

        for (GameObject* grass : dirtMiddle)
        {
            if (grassI < 30)
            {
            grass->Position.y = rocks[0]->Position.y + 330.;
            }
            else if(grassI < 60)
            {
                grass->Position.y = rocks[0]->Position.y + 430.;

            }
            else if (grassI < 90)
            {
                grass->Position.y = rocks[0]->Position.y + 530.;

            }
            else if (grassI < 120)
            {
                grass->Position.y = rocks[0]->Position.y + 630.;

            }
            else if (grassI < 150)
            {
                grass->Position.y = rocks[0]->Position.y + 730.;

            }
            else if (grassI < 180)
            {
                grass->Position.y = rocks[0]->Position.y + 830.;

            }
            grassI++;
        }

        //EVERYTHING

        for (GameObject* tree : trees1)
        {
                tree->Position.y = brickPos.y - 300.;
        }

        for (GameObject* tree : trees2)
        {
                tree->Position.y = brickPos.y - 300.;
        }

        for (GameObject* tree : trees3)
        {
                tree->Position.y = brickPos.y - 300.;
        }

        for (GameObject* tree : trees4)
        {
                tree->Position.y = brickPos.y - 300.;
        }

        for (GameObject* rock : rocks)
        {
                rock->Position.y = brickPos.y - 300.;
        }


        water_background->Position.y = brickPos.y - 1350.;

        Mate->Position.y = brickPos.y + 300.;
    

        // BABY

        for (Player* baby : babies)
        {
                if (baby->Object.Position.x < User->Object.Position.x + (flip ? -50. : 100) + (baby->ID * 20.))
                {
                    baby->Object.Position.x += 300. * dt;

                }
                
                if (baby->Object.Position.x > User->Object.Position.x + (flip ? -50. : 100) - (baby->ID * 20.))
                {
                    baby->Object.Position.x -= 300. * dt;

                }
        }

        // ENEMY



        switch (enemyAnim)
        {
        case enemyAnims::IDLE:
            currFn = 4;
            break;
        case enemyAnims::RUN:
            currFn = 6;
            break;
        case enemyAnims::ATTACK:
            currFn = 7;
            break;
        default:
            currFn = 10;
        }

        i += dt;
        //std::cout << (int)i << "\n";

        if ((int)i != prevI)
        {
            hit = false;
        }

        prevI = (int)i;

        for (GameObject* enemy : enemies)
        {

            if (!enemyGrounded)
            {
                enemy->Position.y += 300.f * dt;

            }

            for (GameObject& brick : this->Levels[this->Level].Bricks)
            {
                if (CheckCollision(*enemy, brick))
                {
                    enemyGrounded = true;
                    break; // I have to add this break as it checks for EVERY brick and turns grounded back to false;
                }
                else
                {
                    enemyGrounded = false;

                }

            }

            if (checkVelocity(*enemy, dt)["x"] != 0.0)
            {
                currEnemAnim = "boar_run";
                enemyAnim = enemyAnims::RUN;
                if (checkVelocity(*enemy, dt)["x"] > 0.0)
                {
                    eFlip = 0;
                }
                else
                {
                    eFlip = 1;
                }

            }

            //std::cout << eFlip <<  "|" << checkVelocity(*enemy, dt)["x"] << "\n";

        }



        // ENEMY END

        switch (playerAnim)
        {
        case playerAnims::IDLE:
            pCurrFn = 5;
            break;
        case playerAnims::RUN:
            pCurrFn = 9;
            break;
        case playerAnims::ATTACK:
            pCurrFn = 4;
            break;
        default:
            pCurrFn = 10;
        }

        User->Velocity.y = (User->Object.Position.y - prevPositionY) / dt;
        User->Velocity.x = (User->Object.Position.x - prevPositionX) / dt;
        prevPositionY = User->Object.Position.y;
        prevPositionX = User->Object.Position.x;

        //std::cout << User->Object.Position.x << "\n";

        if (isAttacking) currAnim = "attack";

        this->DoCollisions();

        // MOVE TO PLAYER
        //for (GameObject* enemy : enemies)
        //{
        //    moveToObject(*enemy, *User);
        //}

        // END MOVE TO PLAYER

        if (User->Jumping)
        {
            gravity = -300.0f;
        }
        else
        {
            gravity = 300.0f;
        }

        if (!grounded)
        {
            //for (GameObject& brick: this->Levels[this->Level].Bricks)
            //{
            //    brick.Position.y -= gravity * dt;
            //}
        }

        if (User->Jumping)
        {
            if (jumpHeight < -70.f)
            {
                jumpHeight = 0.0f;
                User->Jumping = false;
            }
            User->Object.Position.y += gravity * dt;
            jumpHeight += gravity * dt;
            //std::cout << jumpHeight << "\n";
        }

        if (User->Velocity.x != 0 && !User->Attacking)
        {
            currAnim = "run";
            playerAnim = playerAnims::RUN;
        }
        else
        {
            if (!User->Attacking)
            {
                currAnim = "face";
                playerAnim = playerAnims::IDLE;
            }
            else
            {
                playerAnim = playerAnims::ATTACK;

            }
        }

    }
    else if (this->State == GAME_MENU)
    {

    }
}

void Game::ProcessInput(float dt)
{
    if (this->State == GAME_ACTIVE)
    {
        //std::cout << grounded;
        float velocity = PLAYER_VELOCITY.x * dt;
        float velocityY = PLAYER_VELOCITY.y * dt;
        // move playerboard
        if (this->Keys[GLFW_KEY_A])
        {
            if (!DialogueInbound && grassMiddle[0]->Position.x < this->Width/2. - 140.)
            {


                /*if (User->Object.Position.x >= 0.0f)
                    User->Object.Position.x -= velocity;*/
                for (GameObject& brick : this->Levels[this->Level].Bricks)
                {
                        brick.Position.x += 500. * dt;
                }

                for (GameObject* tree : trees1)
                {
                    tree->Position.x += 100. * dt;
                }

                for (GameObject* tree : trees2)
                {
                    tree->Position.x += 150. * dt;
                }

                for (GameObject* tree : trees3)
                {
                    tree->Position.x += 50. * dt;
                }

                for (GameObject* tree : trees4)
                {
                    tree->Position.x += 75. * dt;
                }

                for (GameObject* rock : rocks)
                {
                    rock->Position.x += 500. * dt;
                }

                for (Player* baby : babies)
                {
                    baby->Object.Position.x += 500. * dt;
                }

                for (GameObject* boat : boats)
                {
                    boat->Position.x += 500. * dt;
                }

                for (GameObject* grass : grassMiddle)
                {
                    grass->Position.x += 500. * dt;
                }

                for (GameObject* grass : dirtMiddle)
                {
                    grass->Position.x += 500. * dt;
                }

                Mate->Position.x += 500. * dt;
                water_background->Position.x += 400. * dt;

                flip = 0;
            }
        }
        if (this->Keys[GLFW_KEY_D])
        {
            if (!DialogueInbound)
            {


                //User->Object.Position.x += velocity;
                for (GameObject& brick : this->Levels[this->Level].Bricks)
                {
                    brick.Position.x -= 500. * dt;
                }

                for (GameObject* tree : trees1)
                {
                    tree->Position.x -= 100. * dt;
                }

                for (GameObject* tree : trees2)
                {
                    tree->Position.x -= 150. * dt;
                }

                for (GameObject* tree : trees3)
                {
                    tree->Position.x -= 50. * dt;
                }

                for (GameObject* tree : trees4)
                {
                    tree->Position.x -= 75. * dt;
                }

                for (GameObject* rock : rocks)
                {
                    rock->Position.x -= 500. * dt;
                }

                for (Player* baby : babies)
                {
                    baby->Object.Position.x -= 500. * dt;
                }

                for (GameObject* boat : boats)
                {
                    boat->Position.x -= 500. * dt;
                }

                for (GameObject* grass : grassMiddle)
                {
                    grass->Position.x -= 500. * dt;
                }

                for (GameObject* grass : dirtMiddle)
                {
                    grass->Position.x -= 500. * dt;
                }

                Mate->Position.x -= 500. * dt;
                water_background->Position.x -= 400. * dt;

                flip = 1;
            }
        }

        if (this->Keys[GLFW_KEY_W])
        {
            if (!DialogueInbound)
            {


                for (GameObject& brick : this->Levels[this->Level].Bricks)
                {

                    brickPos = brick.Position;

                    if (brick.Position.y < this->Height / 2. + 30.)
                    {
                        brick.Position.y += 500. * dt;
                    }
                }

            }
            if (DialogueInbound)
            {
                if (hitButton == 0)
                {
                    selectedOption > 1 ? selectedOption-- : selectedOption = 2;
                    hitButton++;
                }
            }

        }
        else
        {
            if (this->Keys[GLFW_KEY_S])
            {
                if (DialogueInbound)
                {
                    if (hitButton == 0)
                    {
                        selectedOption < 2 ? selectedOption++ : selectedOption = 1;
                        hitButton++;
                    }
                }
            }
            else
            {
                hitButton = 0;
            }
        }
        if (this->Keys[GLFW_KEY_S])
        {
            if (!DialogueInbound)
            {


                for (GameObject& brick : this->Levels[this->Level].Bricks)
                {

                    brickPos = brick.Position;


                    if (brick.Position.y > 0.)
                    {
                        brick.Position.y -= 500. * dt;
                    }
                }
            }
        }
        if (this->Keys[GLFW_KEY_E])
        {
            if (CheckCollision(*Mate, User->Object))
            {
                DialogueInbound = true;
            }

            if (selectedOption == 1)
            {
                meatAmt -= 50;
                babies.push_back(new Player(new GameObject(glm::vec2(User->Object.Position.x, User->Object.Position.y), glm::vec2(50., 50.), ResourceManager::GetTexture("face1"), HITBOX_SIZE, glm::vec3(1.), PLAYER_VELOCITY, "PLAYER"), 5., 5., 5., 5.));
                babies[babyAmt]->ID = babyAmt;
                std::cout << babies[babyAmt]->ID << "\n";
                babyAmt++;
            }

            if (selectedOption == 2)
            {
                DialogueBox->Position = glm::vec2(this->Width / 2. - 200000., this->Height - 12000.);
                DialogueInbound = false;
            }
        }
    }
    else if (this->State == GAME_MENU)
    {

        if (this->Keys[GLFW_KEY_W])
        {
            if (hitButton == 0)
            {
                selectedText > 1 ? selectedText-- : selectedText = 2;
                hitButton++;
            }
        }
        else
        {
            if (this->Keys[GLFW_KEY_S])
            {
                if (hitButton == 0)
                {
                    selectedText < 2 ? selectedText++ : selectedText = 1;
                    hitButton++;
                }
            }
            else
            {
                hitButton = 0;
            }
        }


        if (this->Keys[GLFW_KEY_ENTER])
        {
            if (selectedText == 1)
            {
                this->State = GAME_ACTIVE;
            }
        }

    }
}

void Game::ProcessMouseInput(float dt)
{
 
    if (this->State == GAME_ACTIVE)
    {
        if (this->Mouse[GLFW_MOUSE_BUTTON_LEFT])
        {
            if (leftClick < 1)
            {
                leftClick++;
                User->Attacking = true;
                pfn = 1;
            }

            for (GameObject* enemy : enemies)
            {
                if (CheckCollision(*swordBox, *enemy))
                {
                    if (swordHit < 1)
                    {
                        std::cout << "hit!" << "\n";
                        swordHit = 1;
                        enemyHealth -= User->AttackDmg;
                    }
                }
            }

        }
        else
        {
            leftClick = 0;
            swordHit = 0;
        }
    }
    else if (this->State == GAME_MENU)
    {
        
    }
}

void Game::Render(int fn)
{
    if (this->State == GAME_ACTIVE)
    {

        // draw background
        Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f, glm::vec3(1.));
        for (GameObject* tree : trees1)
        {
            tree->Draw(*Renderer, 0);
        }
        water_background->Draw(*Renderer, 0);
        Mate->Draw(*Renderer, mateFlipX);
        Mate->SetFrame("face" + std::to_string(pfn));

        Mark->Draw(*Renderer, 0);
        Mark->SetFrame("exclamation" + std::to_string(pfn));

        for (GameObject* tree : trees2)
        {
            tree->Draw(*Renderer, 0);
        }

        for (GameObject* tree : trees3)
        {
            tree->Draw(*Renderer, 0);
        }

        for (GameObject* tree : trees4)
        {
            tree->Draw(*Renderer, 0);
        }

        for (GameObject* rock : rocks)
        {
            rock->Draw(*Renderer, 0);
        }

        for (GameObject* grass : grassMiddle)
        {
            grass->Draw(*Renderer, 0);
        }

        for (GameObject* dirt : dirtMiddle)
        {
            dirt->Draw(*Renderer, 0);
        }

        User->Object.Draw(*Renderer, flip);
        User->Object.SetFrame(currAnim + std::to_string(pfn));

        for (Player * baby : babies)
        {
            baby->Object.Draw(*Renderer, flip);
            baby->Object.SetFrame(babyAnim + std::to_string(pfn));
            //baby->Object.SetPos(glm::vec2(User->Position.x + ((flip * -50) + ((1- flip) * 100)), User->Position.y + 10.));
        }

        enframeRate++;
        if (enframeRate % 200 == 0)
        {
            if (efn < currFn)
            {
                efn++;
            }
            else
            {
                efn = 1;
            }
        }

        if (enframeRate % 100 == 0)
        {
            if (pfn < pCurrFn)
            {
                pfn++;
                std::cout << pCurrFn << "\n";
            }
            else
            {
                if (playerAnim == playerAnims::ATTACK) User->Attacking = false;
                pfn = 1;

            }

            if (rowerFn < 4)
            {
                rowerFn++;
            }
            else
            {
                rowerFn = 1;
            }
        }

        for (GameObject* enemy : enemies)
        {
            enemy->SetFrame(currEnemAnim + std::to_string(efn));
        }

        for (GameObject* boat: boats)
        {
            boat->Draw(*Renderer);
            boat->SetFrame("rower" + std::to_string(rowerFn));
        }

        this->Levels[this->Level].Draw(*Renderer);


        Text->RenderText(std::to_string(User->CurrentHealth) + '/' + std::to_string(User->MaxHealth), User->Object.Position.x + 20, User->Object.Position.y, .5f, glm::vec3(.0));

        if (User->Attacking)
        {
            swordBox->SetPos(glm::vec2(User->Object.Position.x + (flip * 45), User->Object.Position.y + 20.));
            swordBox->Draw(*Renderer, 1);
            currAnim = "attack";
        }

        // DIALOGUE BOX
        DialogueBox->Draw(*Renderer, 0);

        if (DialogueInbound)
        {
            Text->RenderText("Hatch egg (30 meat)", DialogueBox->Position.x + 20, DialogueBox->Position.y + 35., .5f, glm::vec3(selectedOption == 1 ? 0. : 1.));
            Text->RenderText("End.", DialogueBox->Position.x + 20, DialogueBox->Position.y + 50., .5f, glm::vec3(selectedOption == 2 ? 0. : 1.));

        }
        

        Meat->Draw(*Renderer, 0);
        Text->RenderText('x' + std::to_string(meatAmt), Meat->Position.x + 60, 30., .5f, glm::vec3(1.));

        // END DIALOGUE BOX

        //Mate->Draw(*Renderer, 0);
        //User->Object.Draw(*Renderer, flip);
        //User->Object.SetFrame(currAnim + std::to_string(pfn));

    }
    else if (this->State == GAME_MENU)
    {
        Renderer->DrawSprite(ResourceManager::GetTexture("menu_pic"), glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f, glm::vec3(1.));
        Text->RenderText("START", 50., 450., 1.0f, selectedText != 1 ? glm::vec3(1.) : glm::vec3(1.,0.,0.));
        Text->RenderText("SETTINGS", 50., 500., 1.0f, selectedText != 2 ? glm::vec3(1.) : glm::vec3(1.,0.,0.));

    }



}

// collision detection


void Game::DoCollisions()
{

    for (GameObject& brick : this->Levels[this->Level].Bricks)
    {
        if (CheckCollision<GameObject, GameObject>(User->Object, brick))
        {
                grounded = true;
                //Player->Position.y += .5;
                break; // I have to add this break as it checks for EVERY brick and turns grounded back to false;
        }
        else
        {
            grounded = false; // note to self: we set grounded to true and never set it to false,  that is why he stays on one part of the y axis when moving
        }

    }

    for (GameObject* enemy : enemies)
    {
        if (CheckCollision<GameObject, GameObject>(User->Object, *enemy))
        {

            enemyAnim = enemyAnims::IDLE;

            currEnemAnim = "boar_idle";

            efn = 1;

            if (!hit)
            {
                currHealth -= 10.f;
                hit = true;
            }
        }
        else
        {
        }
    }

}

template<class T, class U>
bool CheckCollision(T one, U two) // AABB - AABB collision
{

    if (one.ID == "PLAYER" && two.ID == "ENEMY")
    {
        // collision x-axis?
        bool collisionX = (one.Position.x + one.Size.x / 2) - 20 >= two.Position.x &&
            two.Position.x + two.Size.x >= one.Position.x + 150;
        // collision y-axis?
        bool collisionY = one.Position.y + one.Size.y >= two.Position.y + 20. &&
            two.Position.y + two.Size.y >= one.Position.y;
        // collision only if on both axes
        return collisionX && collisionY;
    }

    if (one.ID == "PLAYER")
    {
        // collision x-axis?
        bool collisionX = one.Position.x + one.Size.x / 2 >= two.Position.x &&
            two.Position.x + two.Size.x >= one.Position.x + 90;
        // collision y-axis?
        bool collisionY = one.Position.y + one.Size.y >= two.Position.y + 20. &&
            two.Position.y + two.Size.y >= one.Position.y;
        // collision only if on both axes
        return collisionX && collisionY;
    }

    if (one.ID == "ENEMY")
    {
        // collision x-axis?
        bool collisionX = one.Position.x + one.Size.x / 2 >= two.Position.x &&
            two.Position.x + two.Size.x >= one.Position.x + 90;
        // collision y-axis?
        bool collisionY = one.Position.y + one.Size.y >= two.Position.y + 20. &&
            two.Position.y + two.Size.y >= one.Position.y;
        // collision only if on both axes
        return collisionX && collisionY;
    }

    // collision x-axis?
    bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
        two.Position.x + two.Size.x >= one.Position.x;
    // collision y-axis?
    bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
        two.Position.y + two.Size.y >= one.Position.y;
    // collision only if on both axes
    return collisionX && collisionY;
}

static float lerp(float x, glm::vec2 sp, glm::vec2 ep)
{
    // y = y1 + (x - x1) * y2 - y1/x2-x1  

    float x1 = sp.x, y1 = sp.y, x2 = ep.x, y2 = ep.y;
    
    float y = y1 + (x - x1) * ((y2 - y1)/(x2-x1));

    return y;
};

void moveToObject(GameObject one) 
{

    if (one.Position.x < 40000.)
    {
        one.Position.x += 10.;
    }
    
}

//void moveToObject(GameObject one, GameObject two)
//{
//    if (one.Position.x < two.Position.x)
//    {
//        one.Position.x += 1000.4;
//        std::cout << one.Position.x << "\n";
//        eFlip = 0;
//    }
//    else if (one.Position.x > two.Position.x)
//    {
//        one.Position.x -= enemyVelocity;
//        eFlip = 1;
//
//    }
//}

std::map<std::string, float> checkVelocity(GameObject& obj, float dt)
{
    std::map<std::string, float> velocity;
    velocity["x"] = (obj.Position.x - ePrevPosX) / dt;
    velocity["y"] = (obj.Position.y - ePrevPosY) / dt;
    //std::cout << obj.Position.x << '|' << ePrevPosX << "\n";
    ePrevPosX = obj.Position.x;
    ePrevPosY = obj.Position.y;
    //std::cout << (obj.Position.x - ePrevPosX) / dt << "\n";
    return velocity;

}
