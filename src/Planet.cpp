#include "Planet.h"

Planet::Planet(float xp, float yp, float ang)
{
    xPos = xp;
    yPos = yp;
    Angle = ang;

    Collider.x = xPos;
    Collider.y = yPos;
    Collider.r = 170;

    TEX_INDEX = PLANET;
}
