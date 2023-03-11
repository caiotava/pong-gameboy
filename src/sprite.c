#include "sprite.h"

enum SpriteCollisionType isColliding(Sprite *a, Sprite *b)
{
    int widthA = a->position.x + a->size.x;
    int heightA = a->position.y + a->size.y;
    int widthB = b->position.x + b->size.x;
    int heightB = b->position.y + b->size.y;

    int centerA = a->position.y + a->size.y / 2;
    int centerB = b->position.y + b->size.y / 2;

    short int hasCollisionY = ((a->position.y >= b->position.y && a->position.y <= heightB)
                               || (heightA >= b->position.y) && heightA <= heightB);

    short int hasCollisionX = ((a->position.x >= b->position.x && a->position.x <= widthB)
                               || widthA >= b->position.x && widthA <= widthB);

    if ( ! ( hasCollisionY && hasCollisionX ) ) {
        return SPRITE_COLLISION_NONE;
    }

    if (a->position.y < centerB) {
        return SPRITE_COLLISION_TOP;
    }
    else if (a->position.y >= centerB) {
        return SPRITE_COLLISION_BOTTOM;
    }
    else if (centerA == centerB) {
        return SPRITE_COLLISION_MIDDLE;
    }

    return 0;
}