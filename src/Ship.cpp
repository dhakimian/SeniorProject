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

void Ship::thrust_b() // fire rear thrusters, moving the ship forward
{
    double ang = M_PI * Angle;
    ang = ang / 180;
    xVel += SHIP_ACCEL * sin(ang);
    yVel -= SHIP_ACCEL * cos(ang);
}

void Ship::thrust_f() // fire forward thrusters, moving the ship backwards
{
    double ang = M_PI * Angle;
    ang = ang / 180;
    xVel -= SHIP_REV_ACCEL * sin(ang);
    yVel += SHIP_REV_ACCEL * cos(ang);
}

void Ship::rot_l()
{
    rotVel -= SHIP_ROT_ACCEL;
}

void Ship::rot_r()
{
    rotVel += SHIP_ROT_ACCEL;
}

void Ship::thrust_l() // fire port-side thrusters, moving the ship right
{
    double ang = M_PI * Angle;
    ang = ang / 180;
    xVel += SHIP_REV_ACCEL * cos(ang);
    yVel += SHIP_REV_ACCEL * sin(ang);
}

void Ship::thrust_r() // fire starboard thrusters, moving the ship left
{
    double ang = M_PI * Angle;
    ang = ang / 180;
    xVel -= SHIP_REV_ACCEL * cos(ang);
    yVel -= SHIP_REV_ACCEL * sin(ang);
}
