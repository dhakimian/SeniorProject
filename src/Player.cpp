/*This source code was based off part of a tutorial source file from lazyfoo.net which had the following 
 * copyright notice at the top:*/
/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
 * and may not be redistributed without written permission.*/
#include "Player.h"
#include <iostream>

Player::Player()
{
    // acceleration rate
    SHIP_ACCEL = 0.07;
    SHIP_REV_ACCEL = 0.04;
    SHIP_ROT_ACCEL = 0.03;

    xPos = (float) SCREEN_WIDTH / 2;
    yPos = (float) SCREEN_HEIGHT / 2;

    Collider.x = xPos;
    Collider.y = yPos;
    Collider.r = 30;

    xVel = 0.0;
    yVel = 0.0;

    Angle = 0.0;

    rotVel = 0.0;

    MAX_HP = 100;
    hitpoints = 100;
    //    std::cout << "Max hp: " << this->MAX_HP << std::endl;
    
}
