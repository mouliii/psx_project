#pragma once
#include "graphics.h"
#include "controller.h"
#include "cd_drive.h"
#include "texture.h"
#include "sound.h"

typedef struct {
	Graphics* gfx;
	SoundPlayer* soundPlayer;
	CdDrive* cd;
	Controller* controller;
}PSX;