#include "Explosion.h"

Explosion::Explosion(float xp, float yp, float xv, float yv)
{
    xPos = xp;
    yPos = yp;
    xVel = xv;
    yVel = yv;
    Angle = rand()%360;

    Collider.x = xPos;
    Collider.y = yPos;
    Collider.r = 35;

    solid = false;
    can_take_damage = false;
    animated = true;
    anim_loops = false;
    frames_x = 17;
    frames_y = 2;

    prev_frame_num = -1;

    TEX_INDEX = EXPLOSION;
}

void Explosion::update()
{
    MovingObject::update();
    if( prev_frame_num == frame_num ) //this will be true after the animation stops at the last frame
        dead = true;
    else
        prev_frame_num = frame_num;
}

int Explosion::get_type()
{
    return T_EXPLOSION;
}
