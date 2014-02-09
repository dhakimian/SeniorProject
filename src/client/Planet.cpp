#include "Planet.h"

Planet::Planet(float xp, float yp, float ang)
    : Object()
{
    xPos = xp;
    yPos = yp;
    Angle = ang;

    xVel = 0;
    yVel = 0;
    rotVel = 0;

    uint tmp = -1;
    mass = (float)tmp;
    //Since tmp is unsigned, -1 turns into the largest possible value for an int
    //This is to represent planets as immovable objects in the collision equations
    //since an immovable object would have to have infinite mass

    Collider.x = xPos;
    Collider.y = yPos;
    Collider.r = 170;

    TEX_INDEX = PLANET;
}

int Planet::get_type()
{ return T_PLANET; }

void Planet::update()
{
    Object::update();
    xVel = 0;
    yVel = 0;
    rotVel = 0;
}
