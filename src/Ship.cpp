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

/*
void Ship::update()
{
    //Move the ship left or right
    xPos = fmod( (xPos + xVel + LEVEL_WIDTH), LEVEL_WIDTH);

    //Move the ship up or down
    yPos = fmod( (yPos + yVel + LEVEL_HEIGHT), LEVEL_HEIGHT);

    // apparently fmod (float modulo) doesn't do negative numbers (I think it takes the abs val)
    // so to get around this I just shift the number line to avoid passing negatives to fmod, 
    // hence the added LEVEL_WIDTH/LEVEL_HEIGHT in the first args

    //Rotate the ship clockwise or counter-clockwise
    Angle += rotVel;
}

void Ship::get_values(float* xPos_out, float* yPos_out, float* xVel_out, float* yVel_out, float* Angle_out, float* rotVel_out)
{
    *xPos_out = xPos;
    *yPos_out = yPos;
    *xVel_out = xVel;
    *yVel_out = yVel;
    *Angle_out = Angle;
    *rotVel_out = rotVel;
}

void Ship::get_values(float* xPos_out, float* yPos_out, float* Angle_out)
{
    *xPos_out = xPos;
    *yPos_out = yPos;
    *Angle_out = Angle;
}
*/
