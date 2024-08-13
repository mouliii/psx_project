#pragma once
#include "scene.h"
#include "player.h"
#include "enemy.h"
#include "random.h"
#include "smart_arr.h"
#include "debug_msg.h"
#include "collider.h"

class GameScene : public Scene
{
public:
    GameScene();
    ~GameScene();
    virtual void Setup(CdDrive &cd, Graphics &gfx) override;
    virtual void Update(Controller* controller) override;
    virtual void Draw(Graphics& gfx) override;
    void UpdateScene();
private:
// SCENE SETUP
    Texture* texChars;
    Texture* texProjs;
    Player* plr1;
// ENEMY MANAGEMENT
    static constexpr int32_t MAX_ENEMIES = 1024;
    Mou::SmartArr<Enemy> enemies;
    uint32_t counter = 0;
// COLLISION TEST
    Collider collision;
};