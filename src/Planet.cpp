#include "Planet.h"

Planet::Planet(float xp, float yp, float ang)
{
    xPos = xp;
    yPos = yp;
    Angle = ang;
    C_RAD = 170;
    TEX_INDEX = PLANET;
}
