/*This source code was based off part of a tutorial source file from lazyfoo.net which had the following 
 * copyright notice at the top:*/
/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
 * and may not be redistributed without written permission.*/
#include "Alien.h"

/*
Alien::Alien()
{
    //Alien((float) SCREEN_WIDTH / 2, (float) SCREEN_HEIGHT / 2);
    Alien(0.0, 0.0, 0.0);
}
*/

Alien::Alien(float xp, float yp, float ang )
{
    // acceleration rate
    SHIP_ACCEL = 0.07;
    SHIP_REV_ACCEL = 0.04;
    SHIP_ROT_ACCEL = 0.03;

    xPos = xp;
    yPos = yp;

    Collider.x = xPos;
    Collider.y = yPos;
    Collider.r = 30;

    //xVel = 0.0;
    //yVel = 0.0;

    Angle = ang;

    //rotVel = 0.0;

    MAX_HP = 200;
    hitpoints = 200;

    TEX_INDEX = ALIEN;
}

