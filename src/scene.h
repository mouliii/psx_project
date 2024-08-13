#pragma once
#include "fixed_math.h"
#include "graphics.h"
#include "cd_drive.h"
#include "texture.h"
#include "sound.h"
#include "controller.h"
#include "debug_msg.h"


class Scene
{
public:
    Scene(){}
    virtual ~Scene(){}
    virtual void Setup(CdDrive &cd, Graphics &gfx) = 0;
    virtual void Update(Controller* controller) = 0;
    virtual void Draw(Graphics& gfx) = 0;
};