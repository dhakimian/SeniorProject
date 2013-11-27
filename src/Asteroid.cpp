#include "Asteroid.h"

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
    set_size(s);
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
        for (int i=0; i<2; i++) {
            //objects.push_back(new Asteroid(xPos, yPos, Angle, ((double) rand()/RAND_MAX) -0.5, ((float) rand()/RAND_MAX)-0.5, size));
            objects.push_back( new Asteroid(xPos+rand()%7-3, yPos+rand()%7-3, Angle, 0, 0, rand()%7-3, size) );
        }
    }
    else dead = true;
}

int Asteroid::get_type()
{
    return T_ASTEROID;
}
