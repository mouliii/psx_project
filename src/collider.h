#pragma once
#include <cstdint>
#include "character_body.h"
#include "debug_msg.h"

enum class CollisionLayers
{
    world = 1,
    player = 2,
    enemy = 3,
    projectile = 4,
    collectable = 5
};

class CharacterBody;

class Collider
{
public:
    Collider() = default;
    bool IsColliding(CharacterBody* left, CharacterBody* right);
public:
// COLLISION SHAPE
};