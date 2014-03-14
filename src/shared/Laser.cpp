#include "Laser.h"
#include <iostream>

Laser::Laser()
{
    Collider.r = 2;
    Collider.x = xPos;
    Collider.y = yPos;

    solid = false;
    persistent = true;

    TEX_INDEX = LASER1;
    weapon_level = 1;

    TYPE = T_LASER;
}

Object* Laser::get_owner()
{
    return owner;
}

void Laser::set_values(Object* ship, float x, float y, float ang, float xv, float yv)
{
    owner = ship;
    xPos = x;
    yPos = y;
    Angle = ang;
    xVel = xv;
    yVel = yv;
    time_left = LIFESPAN;
    dead = false;
}

int Laser::get_time_left()
{
    return time_left;
}

void Laser::update()
{
    time_left--;
    if( time_left <= 0 ) {
        dead = true;
    } else
        MovingObject::update();
}

void Laser::upgrade()
{
    weapon_level++;
    //std::cout<<"UPGRADE! "<<weapon_level<<std::endl;
    if (weapon_level == 1)
        TEX_INDEX = LASER1;
    else if (weapon_level == 2)
        TEX_INDEX = LASER2;
    else if (weapon_level == 3)
        TEX_INDEX = LASER3;
    else
        TEX_INDEX = LASER4;
   //also change collider dimention depending on how the images change
}

void Laser::onCollide( Object* collided_with )
{
    //if( collided_with->is_solid() && collided_with != owner )
    if( collided_with->is_solid() && collided_with != owner
            && ( collided_with->get_team() != owner->get_team()
                || collided_with->get_team() < 0 ) )
    {
        if( SOUND_ON )
            Mix_PlayChannel( 1, g_sounds[HIT], 0 );
        collided_with->takeDamage(100);
        //collided_with->takeDamage(65); //resulting explosion does 35 damage to equal 100
        g_objects.push_back( new Explosion(xPos, yPos, xVel/10, yVel/10) );
        dead = true;
    }
}
