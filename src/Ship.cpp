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
    teamnumber = 2;
    pool_size = 10;
    Req_Cooldown = 30;
    cooldown = 0;
    Req_upgrade_cooldown = 100;
    upgrade_cooldown = 0;

    hyperLaser = Mix_LoadWAV( "media/sounds/hyperLaser.wav" );
    singleLaser = Mix_LoadWAV( "media/sounds/singleLaser.wav" );
    doubleLaser = Mix_LoadWAV( "media/sounds/doubleLaser.wav" );
    shiphit = Mix_LoadWAV( "media/sounds/Hit.wav");
    shipPowerup = Mix_LoadWAV( "media/sounds/Powerup.wav");
    shipExplode = Mix_LoadWAV( "media/sounds/shipexplode.wav");
    shoot_sound_current_strength = singleLaser;


    for( int i=0; i<pool_size; i++ )
        laser_pool.push_back( new Laser() );
    for( int j=0; j<pool_size; j++ )
        laser_pool[j]->channelint = j;
}

void Ship::update()
{
    if( hitpoints <= 0 ){
        dead = true;
        Mix_PlayChannel( -1, shipExplode , 0);}
    else
    {
        MovingObject::update();
        if (upgrade_cooldown > 0)
            upgrade_cooldown--;
        //rob added this to make the ships decay over time so its easier to control, its not super noticable but its nice and makes it easier.
        xVel /= 1.005;
        yVel /= 1.005;
        rotVel /= 1.005;
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
void Ship::weapons_upgrade()
{
    Mix_PlayChannel( -1, shipPowerup, 0);
    if (upgrade_cooldown == 0){  
        soundindex += 1;
        for(int i=0; i < pool_size; i++ ){
            laser_pool[i]->upgrade();}
        if (soundindex == 2)
        {
            upgrade_cooldown = Req_upgrade_cooldown;
            shoot_sound_current_strength = doubleLaser;
            Req_Cooldown = 23;
        }
        else if (soundindex == 3)
        {
            upgrade_cooldown = Req_upgrade_cooldown;
            shoot_sound_current_strength = doubleLaser;
            Req_Cooldown = 17;
        }
        else if (soundindex == 4)
        {
            upgrade_cooldown = Req_upgrade_cooldown;
            shoot_sound_current_strength = hyperLaser;
            Req_Cooldown = 14;
        }
        else if (soundindex >= 5)
        {
            upgrade_cooldown = Req_upgrade_cooldown;
            shoot_sound_current_strength = singleLaser;
            Req_Cooldown = 10;
        }
    }
}

void Ship::shoot()
{
    if( cooldown <= 0 && laser_pool.size() > 0 )
    {
        //shoot a laser;
        Mix_PlayChannel( -1, shoot_sound_current_strength, 0 );
        double ang = M_PI * Angle;
        ang = ang / 180;
        float xv = xVel + Laser::VEL * sin(ang);
        float yv = yVel - Laser::VEL * cos(ang);
        laser_pool.back()->set_values(xPos, yPos, Angle, xv, yv, Laser::LIFESPAN);

        active_lasers.push_back( laser_pool.back() );
        objects.push_back( laser_pool.back() );
        laser_pool.pop_back();
        cooldown = Req_Cooldown;
    }

}
