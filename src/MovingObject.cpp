#include "MovingObject.h"

MovingObject::MovingObject()
{
    xVel = 0.0;
    yVel = 0.0;

    rotVel = 0.0;

}

int MovingObject::get_type()
{
    return T_MOVOBJ;
}

void MovingObject::update()
{
    xPos_old = xPos;
    yPos_old = yPos;

    xVel_old = xVel;
    yVel_old = yVel;
    rotVel_old = rotVel;

    //Move the object left or right
    xPos = fmod( (xPos + xVel + LEVEL_WIDTH), LEVEL_WIDTH );

    //Move the object up or down
    yPos = fmod( (yPos + yVel + LEVEL_HEIGHT), LEVEL_HEIGHT );

    // apparently fmod (float modulo) doesn't do negative numbers (I think it takes the abs val)
    // so to get around this I just shift the number line to avoid passing negatives to fmod, 
    // hence the added LEVEL_WIDTH/LEVEL_HEIGHT in the first args

    //Rotate the object clockwise or counter-clockwise
    Angle = fmod( (Angle + rotVel + 360), 360 );

    Collider.x = xPos;
    Collider.y = yPos;

    //Collision checks
    for( int i=0; i<objects.size(); i++ )
    {
        Circle other_collider = objects[i]->get_collider();
        if( checkCollision( Collider, other_collider ) && (this != objects[i]) )
            onCollide( objects[i] );
    }
}

void MovingObject::onCollide( Object* collided_with )
{
    xVel = 0.0;
    yVel = 0.0;
    rotVel = 0.0;
    //TODO: implement transferal of kinetic energy, or in other words "bounce"
    //      This may require the addition of mass values for objects
    
    //Undo move left or right
    xPos = xPos_old;

    //Undo move up or down
    yPos = yPos_old;

}

void MovingObject::get_values(float* xPos_out, float* yPos_out, float* Angle_out, float* xVel_out, float* yVel_out, float* rotVel_out)
{
    *xPos_out = xPos;
    *yPos_out = yPos;
    *Angle_out = Angle;
    *xVel_out = xVel;
    *yVel_out = yVel;
    *rotVel_out = rotVel;
}

void MovingObject::get_values(float* xPos_out, float* yPos_out, float* Angle_out)
{
    *xPos_out = xPos;
    *yPos_out = yPos;
    *Angle_out = Angle;
}
