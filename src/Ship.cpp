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

/*
   Ship::~Ship()
   {

   }
   */

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

void Ship::update_pos()
{
    //Move the ship left or right
    xPos += xVel;

    //If the ship went too far to the left
    if( xPos - Collider.r < 0 )
    {
        xPos = (float) Collider.r;
        xVel = 0.0;
    }
    //If the ship went too far to the right
    if ( xPos + Collider.r > LEVEL_WIDTH )
    {
        xPos = (float) LEVEL_WIDTH - Collider.r;
        xVel = 0.0;
    }

    //Move the ship up or down
    yPos += yVel;

    //If the ship went too far up
    if( yPos - Collider.r < 0 )
    {
        yPos = (float) Collider.r;
        yVel = 0.0;
    }
    //If the ship went too far down
    if( yPos + Collider.r > LEVEL_HEIGHT )
    {
        yPos = (float) LEVEL_HEIGHT - Collider.r;
        yVel = 0.0;
    }

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

/*SDL_Point getCenter();
{
    SDL_Point center;
    center.x = (SHIP_WIDTH / 2);
    center.y = (SHIP_HEIGHT / 2);
    return center;
}
*/
