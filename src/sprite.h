#ifndef PONG_SPRITE_H
#define PONG_SPRITE_H

#include <stdint.h>

#include "vector2D.h"

typedef struct {
    uint8_t id;
    Vector2D_16 position;
    Vector2D size;
} Sprite;

typedef struct {
    Sprite sprite;
    Vector2D velocity;
} Ball;

enum SpriteCollisionType {
    SPRITE_COLLISION_NONE = 0,
    SPRITE_COLLISION_TOP,
    SPRITE_COLLISION_MIDDLE,
    SPRITE_COLLISION_BOTTOM
};

enum SpriteCollisionType isColliding(Sprite *a, Sprite *b);

#endif //PONG_SPRITE_H
