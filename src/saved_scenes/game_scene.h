#pragma once
#include "scene.h"
#include "player.h"
#include "random.h"

class GameScene : public Scene
{
public:
    GameScene();
    ~GameScene();
    virtual void Setup(CdDrive &cd, Graphics &gfx) override;
    virtual void Update(Controller* controller) override;
    virtual void Draw(Graphics& gfx) override;
private:
    Texture* texChars;
    Texture* texProjs;
    Player* plr1;
    Player* enemies;

    uint32_t counter = 0;
};