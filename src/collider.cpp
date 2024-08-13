#include "collider.h"

bool Collider::IsColliding(CharacterBody* left, CharacterBody* right)
{

    int32_t centerXLeft = (left->pos[0] >> 12) + left->GetRadius();
    int32_t centerYLeft = (left->pos[1] >> 12) + left->GetRadius();

    int32_t centerXRight = (right->pos[0] >> 12) + right->GetRadius();
    int32_t centerYRight = (right->pos[1] >> 12) + right->GetRadius();

    int32_t distX = centerXLeft - centerXRight;
    int32_t distY = centerYLeft - centerYRight;

    int32_t radiusSum = left->GetRadius() + right->GetRadius();
    int32_t radiusSumSq = radiusSum * radiusSum;

    int32_t distSq = (distX*distX) + (distY*distY);

    //char str[100];
    //sprintf(str, "rt: %d ro: %d", owner->speed, other->GetRadius());
    //DEBUG_MSG::CreateMsg(0, str);

    if ( distSq < radiusSumSq)
    {
        return true;
    }
    return false;
}
