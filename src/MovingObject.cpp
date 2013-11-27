#include "MovingObject.h"
#include "Laser.h"
#include <iostream>

MovingObject::MovingObject()
{
    xVel = 0.0;
    yVel = 0.0;
    rotVel = 0.0;

    Collider.x = xPos;
    Collider.y = yPos;

    can_take_damage = true;
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

    //Collider.x = xPos;
    //Collider.y = yPos;

    bool overlapping = false;

    //check if object is already colliding
    for( uint i=0; i<objects.size(); i++ )
    {
        Circle other_collider = objects[i]->get_collider();
        if( solid && objects[i]->is_solid()
                && (objects[i] != this)
                && checkCollision( Collider, other_collider )
                )
        {
            overlapping = true;
            if( (Collider.x - other_collider.x) < 0 )
                xVel -= Separation_vel;
            else
                xVel += Separation_vel;

            if( (Collider.y - other_collider.y) < 0 )
                yVel -= Separation_vel;
            else
                yVel += Separation_vel;
        }
    }

    if( rotVel > 20 )
        takeDamage(1);

    //Move the object left or right
    xPos = fmod( (xPos + xVel + LEVEL_WIDTH), LEVEL_WIDTH );

    //Move the object up or down
    yPos = fmod( (yPos + yVel + LEVEL_HEIGHT), LEVEL_HEIGHT );

    // apparently fmod (float modulo) doesn't do negative numbers (I think it takes the abs val)
    // so to get around this I just shift the number line to avoid passing negatives to fmod, 
    // hence the added LEVEL_WIDTH/LEVEL_HEIGHT in the first args

    //Rotate the object clockwise or counter-clockwise
    Angle = fmod( (Angle + rotVel + 360), 360 );

    xVel -= (Speed_Decay * xVel);
    yVel -= (Speed_Decay * yVel);
    rotVel -= ((Speed_Decay/5) * rotVel);

    Collider.x = xPos;
    Collider.y = yPos;

    //overlapping=false;
    //Collision checks
    if( !overlapping )
    {
        for( uint i=0; i<objects.size(); i++ )
        {
            Circle other_collider = objects[i]->get_collider();
            if( checkCollision( Collider, other_collider ) && (objects[i] != this) )
                onCollide( objects[i] );
        }
    }
}

void MovingObject::onCollide( Object* collided_with )
{
    if( solid && collided_with->is_solid() )
    {
        float xPos_other, yPos_other, Angle_other, xVel_other, yVel_other, rotVel_other;
        collided_with->get_values(&xPos_other, &yPos_other, &Angle_other, &xVel_other, &yVel_other, &rotVel_other);

        collided_with->set_values( xPos_other, yPos_other, Angle_other, xVel_other+xVel/VD, yVel_other+yVel/VD, rotVel_other );

        xVel = -xVel/VD;
        yVel = -yVel/VD;
        rotVel /= 2;
        /*
        xVel = 0.0;
        yVel = 0.0;
        rotVel = 0.0;
        //TODO: implement transferal of kinetic energy, or in other words "bounce"
        //      This may require the addition of mass values for objects
        */

        //Undo move left or right
        xPos = xPos_old;

        //Undo move up or down
        yPos = yPos_old;

        Collider.x = xPos;
        Collider.y = yPos;
        /////

        //damage the object depending on how fast it was moving when it collided
        float vel_old_squared = abs( xVel_old * xVel_old ) + abs( yVel_old * yVel_old );
        float vel_other_squared = abs( xVel_other * xVel_other ) + abs( yVel_other * yVel_other );
        int damage = abs( vel_old_squared - vel_other_squared ) * Collision_Damage_multiplier;
        //if( damage > 0 )
            //std::cout<<damage<<" collision damage"<<std::endl;
        takeDamage( damage );
        collided_with->takeDamage( damage );
        /*
    } else {
        if( collided_with->get_type() == T_EXPLOSION )
        {
            takeDamage(1);
        }
        //else if( )
        //{
        //}
        */
    }
}
