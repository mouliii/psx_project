#pragma once
#include <cstdint>
#include "scene.h"


class MainMenu : public Scene
{
public:
    MainMenu();
    ~MainMenu();
    virtual void Setup(CdDrive &cd, Graphics &gfx) override;
    virtual void Update(Controller* controller) override;
    virtual void Draw(Graphics& gfx) override;
// this scene
    void DrawSelector(Graphics& gfx);
private:
    Texture* texMenu;
// SELECTOR
    int8_t selection = 0;
    uint8_t uvRetOffs[2] = {11*16,0}; // SPRT_16 pos: x: 1.5*16, y: 3.15*16
};