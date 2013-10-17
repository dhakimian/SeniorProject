/*This source code was based off part of a tutorial source file from lazyfoo.net which had the following 
 * copyright notice at the top:*/
/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
 * and may not be redistributed without written permission.*/

#include "Ship.h"

Ship::Ship()
{
    xPos = (float) SCREEN_WIDTH / 2;
    yPos = (float) SCREEN_HEIGHT / 2;

    xVel = 0.0;
    yVel = 0.0;

    Angle = 0.0;

    rotVel = 0.0;

    Collider.x = xPos;
    Collider.y = yPos;
    Collider.r = Collider.r;
}

void Ship::thrust_b()
{
    double ang = M_PI * Angle;
    ang = ang / 180;
    xVel += SHIP_ACCEL * sin(ang);
    yVel -= SHIP_ACCEL * cos(ang);
}

void Ship::thrust_f()
{
    double ang = M_PI * Angle;
    ang = ang / 180;
    xVel -= SHIP_REV_ACCEL * sin(ang);
    yVel += SHIP_REV_ACCEL * cos(ang);
}

void Ship::thrust_l()
{
    rotVel -= SHIP_ROT_ACCEL;
}

void Ship::thrust_r()
{
    rotVel += SHIP_ROT_ACCEL;
}
