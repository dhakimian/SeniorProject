#include "Powerup.h"
#include "Ship.h"
#include <iostream>

Powerup::Powerup(float x, float y, float ang, float xv, float yv, float rv)
{
    xPos = x;
    yPos = y;
    Collider.x = xPos;
    Collider.y = yPos;
    Collider.r = 20;
    Angle = ang;
    xVel = xv;
    yVel = yv;
    rotVel = rv;
    mass = 5;

    //animated = true;
    //frames_x = 4;
    //frames_y = 1;
    //frame_delay = 5;

    TEX_INDEX = POWERUP;
}

int Powerup::get_type()
{ return T_POWERUP; }

void Powerup::onCollide( Object* collided_with )
{
    //if( collided_with->is_type(T_SHIP) )
    if( collided_with->get_type() == T_PLAYER )
    {
        std::cout<<"onC"<<std::endl;
        Ship* ship = (Ship*)collided_with;
        ship->weapons_upgrade();
        dead = true;
    }
    else if( collided_with->get_type() == T_LASER )
        dead = true;
    else
        MovingObject::onCollide( collided_with );

}

void Powerup::whenColliding( Object* colliding_with )
{
    //if( colliding_with->is_type(T_SHIP) )
    if( colliding_with->get_type() == T_PLAYER )
    {
        std::cout<<"whenC"<<std::endl;
        Ship* ship = (Ship*)colliding_with;
        ship->weapons_upgrade();
        dead = true;
    }
    else
        MovingObject::whenColliding( colliding_with );
}
