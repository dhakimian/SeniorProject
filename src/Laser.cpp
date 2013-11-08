#include "Laser.h"

Laser::Laser()
{
    Collider.r = 2;

    TEX_INDEX = LASER;
}

void Laser::set_values(float x, float y, float ang, float xv, float yv, int time)
{
    xPos = x;
    yPos = y;
    Angle = ang;
    xVel = xv;
    yVel = yv;
    time_left = time;
    dead = false;
}

void Laser::update()
{
    time_left--;
    if( time_left <= 0 )
        dead = true;
    else
        MovingObject::update();
}
