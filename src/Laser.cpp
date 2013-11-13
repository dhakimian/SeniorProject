#include "Laser.h"

Laser::Laser()
{
    Collider.r = 2;

    TEX_INDEX = LASER;
}

int Laser::get_type()
{
    return T_LASER;
}

//void Laser::set_values(float x, float y, float ang, float xv, float yv, int time)
void Laser::set_values(float x, float y, float ang, float xv, float yv)
{
    xPos = x;
    yPos = y;
    Angle = ang;
    xVel = xv;
    yVel = yv;
    //time_left = time;
    time_left = LIFESPAN;
    dead = false;
}

int Laser::get_time_left()
{
    return time_left;
}

void Laser::update()
{
    time_left--;
    if( time_left <= 0 )
        dead = true;
    else
        MovingObject::update();
}

void Laser::onCollide( Object* collided_with )
{
    if( time_left < 95 )
        dead = true;
}
