/*This source code was based off part of a tutorial source file from lazyfoo.net which had the following 
 * copyright notice at the top:*/
/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
 * and may not be redistributed without written permission.*/

#include "Ship.h"

Ship::Ship(float xp, float yp, float ang )
{
    // acceleration rates
    SHIP_ACCEL = 0.07;
    SHIP_REV_ACCEL = 0.04;
    //SHIP_STRAFE_ACCEL = 
    SHIP_ROT_ACCEL = 0.03;

    Collider.r = 30;

    xPos = xp;
    yPos = yp;

    xVel = 0.0;
    yVel = 0.0;

    Angle = ang;

    rotVel = 0.0;

    pool_size = 5;
    Req_Cooldown = 30;
    cooldown = 0;

    for( int i=0; i<pool_size; i++ )
        laser_pool.push_back( new Laser() );

    TEX_INDEX = PLAYER;
}

int Ship::get_type()
{
    return T_SHIP;
}

int Ship::get_hitpoints()
{
    return hitpoints;
}

void Ship::update()
{
    if( hitpoints <= 0 )
        dead = true;
    else
    {
        MovingObject::update();
        if( cooldown > 0 )
            cooldown--;
        for( unsigned int i=0; i<active_lasers.size(); i++ )
        {
            if( active_lasers[i]->is_dead() )
            {
                laser_pool.push_back( active_lasers[i] );
                active_lasers.erase( active_lasers.begin()+i );
                i--;
            }
        }
    }
}

void Ship::onCollide( Object* collided_with )
{
    if( collided_with->get_type() == T_LASER )
    {
        Laser* laser = (Laser*) collided_with;
        //prevent laser from doing damage for 5 cycles to avoid damaging the ship shooting the laser
        if( laser->get_time_left() < 95 )
            takeDamage(10);
    } else {
        MovingObject::onCollide( collided_with );

        //damage the ship depending on how fast it was moving when it collided
        float vel_old_squared = abs( xVel_old * xVel_old ) + abs( yVel_old * yVel_old );
        int damage = vel_old_squared / 5;
        takeDamage( damage );
        collided_with->takeDamage( damage );
    }
}

void Ship::takeDamage( int amount )
{
    hitpoints -= amount;
}

void Ship::thrust_b() // fire rear thrusters, moving the ship forward
{
    double ang = M_PI * Angle;
    ang = ang / 180;
    xVel += SHIP_ACCEL * sin(ang);
    yVel -= SHIP_ACCEL * cos(ang);
}

void Ship::thrust_f() // fire forward thrusters, moving the ship backwards
{
    double ang = M_PI * Angle;
    ang = ang / 180;
    xVel -= SHIP_REV_ACCEL * sin(ang);
    yVel += SHIP_REV_ACCEL * cos(ang);
}

void Ship::rot_l()
{
    rotVel -= SHIP_ROT_ACCEL;
}

void Ship::rot_r()
{
    rotVel += SHIP_ROT_ACCEL;
}

void Ship::thrust_l() // fire port-side thrusters, moving the ship right
{
    double ang = M_PI * Angle;
    ang = ang / 180;
    xVel += SHIP_REV_ACCEL * cos(ang);
    yVel += SHIP_REV_ACCEL * sin(ang);
}

void Ship::thrust_r() // fire starboard thrusters, moving the ship left
{
    double ang = M_PI * Angle;
    ang = ang / 180;
    xVel -= SHIP_REV_ACCEL * cos(ang);
    yVel -= SHIP_REV_ACCEL * sin(ang);
}

void Ship::shoot()
{
    if( cooldown <= 0 && laser_pool.size() > 0 )
    {
        //shoot a laser;
        double ang = M_PI * Angle;
        ang = ang / 180;
        float xv = xVel + Laser::VEL * sin(ang);
        float yv = yVel - Laser::VEL * cos(ang);
        //laser_pool.back()->set_values(xPos, yPos, Angle, xv, yv, Laser::LIFESPAN);
        laser_pool.back()->set_values(xPos, yPos, Angle, xv, yv);

        active_lasers.push_back( laser_pool.back() );
        objects.push_back( laser_pool.back() );
        laser_pool.pop_back();
        cooldown = Req_Cooldown;
    }

}
