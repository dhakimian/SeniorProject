#include "Asteroid.h"
#include "Powerup.h"

Asteroid::Asteroid()
{
}

Asteroid::Asteroid(float x, float y, float ang, float xv, float yv, float rv, int s)
{
    xPos = x;
    yPos = y;
    Collider.x = xPos;
    Collider.y = yPos;
    Angle = ang;
    xVel = xv;
    yVel = yv;
    rotVel = rv;
    split_num = 3;
    mass_max = 90;
    powerup_chance = 10;
    set_size(s);

    TYPE = T_ASTEROID;
}

void Asteroid::set_size(int s)
{
    size = s;
    switch( size )
    {
        case 1:
            Collider.r = 50;
            TEX_INDEX = ASTEROID;
            hitpoints = 300;
            break;
        case 2:
            Collider.r = 25;
            TEX_INDEX = MINI_ASTEROID;
            hitpoints = 200;
            break;
        case 3:
            Collider.r = 15;
            TEX_INDEX = TINY_ASTEROID;
            hitpoints = 100;
    }
    mass = mass_max * ( pow( 1/(float)split_num, size-1 ) );
}

int Asteroid::get_size()
{ return size; }

void Asteroid::update()
{
    MovingObject::update();
    if( hitpoints <= 0 )
        split();
} 

void Asteroid::split()
{ 
    if(size < 3){
        set_size(size+1);
        float xva = 0; //x_vel accumulator
        float yva = 0; //y_vel accumulator
        for (int i=0; i<split_num-1; i++)
        {
            float xVel_new = frandBetween(-15,15)/10;
            float yVel_new = frandBetween(-15,15)/10;
            xva += xVel_new;
            yva += yVel_new;
            g_objects.push_back( new Asteroid(xPos+randBetween(-3,3), yPos+randBetween(-3,3), Angle, xVel+xVel_new, yVel+yVel_new, frandBetween(-20,20)/10, size ) );
        }
        if( rand()%100 < powerup_chance )
            g_objects.push_back( new Powerup( xPos, yPos, Angle, xVel+frandBetween(-15,15)/10, yVel+frandBetween(-15,15)/10 ) );
        xPos += randBetween(-3,3);
        yPos += randBetween(-3,3);
        xVel -= xva; //Ensure that the sum of all the velocities of the parts...
        yVel -= yva; //...is equal to zero, for conservation of momentum or something
        rotVel = frandBetween(-20,20)/10;
    }
    else dead = true;
}

