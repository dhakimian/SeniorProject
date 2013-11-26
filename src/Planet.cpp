#include "Planet.h"

Planet::Planet(float xp, float yp, float ang)
    : Object()
{
    xPos = xp;
    yPos = yp;
    Angle = ang;

    Collider.x = xPos;
    Collider.y = yPos;
    Collider.r = 170;

    TEX_INDEX = PLANET;
}

int Planet::get_type()
{ return T_PLANET; }
