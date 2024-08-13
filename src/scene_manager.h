#pragma once
#include "game_scene.h"
#include "main_menu.h"

enum SCENE_ID
{
    MAIN_MENU = 1,
    GAME = 2
};

class SceneManager
{
public:
    static SceneManager& Get()
    {
        static SceneManager instance;
        return instance;
    }
    static void Setup(Scene* scene, Graphics* gfx, CdDrive* cd){Get().ISetup(scene, gfx, cd);}
    static void ChangeScene(SCENE_ID id){ Get().IChangeScene(id);}
private:
    SceneManager() = default;
    void IChangeScene(SCENE_ID id)
    {
        delete scene;
        switch (id)
        {
        case MAIN_MENU:
            scene = new MainMenu();
            break;
        case GAME:
            scene = new GameScene();
        default:
            break;
        }
        scene->Setup(*cd, *gfx);
    }
    void ISetup(Scene* scene, Graphics* gfx, CdDrive* cd)
    {
        this->scene = scene;
        this->gfx = gfx;
        this->cd = cd;
    }
private:
    Scene* scene;
    CdDrive* cd;
    Graphics* gfx;
};