#include "MovingObject.h"

MovingObject::MovingObject()
{
    xVel = 0.0;
    yVel = 0.0;

    rotVel = 0.0;

}

void MovingObject::update()
{
    //Move the object left or right
    xPos = fmod( (xPos + xVel + LEVEL_WIDTH), LEVEL_WIDTH);

    //Move the object up or down
    yPos = fmod( (yPos + yVel + LEVEL_HEIGHT), LEVEL_HEIGHT);

    // apparently fmod (float modulo) doesn't do negative numbers (I think it takes the abs val)
    // so to get around this I just shift the number line to avoid passing negatives to fmod, 
    // hence the added LEVEL_WIDTH/LEVEL_HEIGHT in the first args

    //Rotate the object clockwise or counter-clockwise
    Angle += rotVel;

    Collider.x = xPos;
    Collider.y = yPos;
}

void MovingObject::get_values(float* xPos_out, float* yPos_out, float* xVel_out, float* yVel_out, float* Angle_out, float* rotVel_out)
{
    *xPos_out = xPos;
    *yPos_out = yPos;
    *xVel_out = xVel;
    *yVel_out = yVel;
    *Angle_out = Angle;
    *rotVel_out = rotVel;
}

void MovingObject::get_values(float* xPos_out, float* yPos_out, float* Angle_out)
{
    *xPos_out = xPos;
    *yPos_out = yPos;
    *Angle_out = Angle;
}
