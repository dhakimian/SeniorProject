#include "MovingObject.h"
#include "Laser.h"

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

    bool overlapping = false;

    /*
    //check if object is already colliding
    for( int i=0; i<objects.size(); i++ )
    {
        Circle other_collider = objects[i]->get_collider();
        if( checkCollision( Collider, other_collider ) && (objects[i] != this)
                && objects[i]->get_type() != T_LASER )
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
    */

    ///* MEGA RANDOM BOUNCING
    //check if object is already colliding
    for( int i=0; i<objects.size(); i++ )
    {
        Circle other_collider = objects[i]->get_collider();
        if( checkCollision( Collider, other_collider ) && (objects[i] != this)
                && objects[i]->get_type() != T_LASER
                && this->get_type() != T_LASER )
        {
            overlapping = true;
            float r = (rand()%300+10)/100;
            if( (Collider.x - other_collider.x) < 0 )
                xVel = -r;
            else
                xVel = r;

            r = (rand()%300+10)/100;
            if( (Collider.y - other_collider.y) < 0 )
                yVel = -r;
            else
                yVel = r;
        }
    }
    //*/

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
    if( !overlapping )
    {
        for( int i=0; i<objects.size(); i++ )
        {
            Circle other_collider = objects[i]->get_collider();
            if( checkCollision( Collider, other_collider ) && (objects[i] != this) )
                onCollide( objects[i] );
        }
    }
}

void MovingObject::onCollide( Object* collided_with )
{
    if( collided_with->get_type() == T_LASER )
    {
        Laser* laser = (Laser*) collided_with;
        //prevent laser from doing damage for 5 cycles to avoid damaging the ship shooting the laser
        if( laser->get_time_left() < Laser::LIFESPAN-5 )
        {
            takeDamage(10);
        }
    } else {
        /////
        xVel = 0.0;
        yVel = 0.0;
        rotVel = 0.0;
        //TODO: implement transferal of kinetic energy, or in other words "bounce"
        //      This may require the addition of mass values for objects

        //Undo move left or right
        xPos = xPos_old;

        //Undo move up or down
        yPos = yPos_old;

        //Collider.x = xPos;
        //Collider.y = yPos;
        /////

        //damage the object depending on how fast it was moving when it collided
        float vel_old_squared = abs( xVel_old * xVel_old ) + abs( yVel_old * yVel_old );
        //float vel_other_squared = abs( 
        int damage = vel_old_squared / 5;
        takeDamage( damage );
        collided_with->takeDamage( damage );
    }

}
