/*This source code was based off part of a tutorial source file from lazyfoo.net which had the following 
 * copyright notice at the top:*/
/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
 * and may not be redistributed without written permission.*/
#include "Alien.h"

Alien::Alien(float xp, float yp, float ang )
{
    /*
    // acceleration rates
    SHIP_ACCEL = 0.07;
    SHIP_REV_ACCEL = 0.04;
    //SHIP_STRAFE_ACCEL = 
    SHIP_ROT_ACCEL = 0.03;
        */

    //Collider.r = 30;

    xPos = xp;
    yPos = yp;

    Collider.x = xPos;
    Collider.y = yPos;

    Angle = ang;

    rotVel = 1.0;

    MAX_HP = 2000;
    hitpoints = MAX_HP;

    team = 0;

    TEX_INDEX = ALIEN;
}

int Alien::get_type()
{ return T_ALIEN; }
