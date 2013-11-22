#include "Asteroid.h"

Asteroid::Asteroid(float x, float y, float ang, float xv, float yv, int s)
{
  xPos = x;
  yPos = y;
  Angle = ang;
  xVel = xv;
  yVel = yv;
  size = s;
  set_size();
  
}
void Asteroid::set_size()
{
if( size == 1){
  Collider.r = 50;
  TEX_INDEX = ASTEROID;
  }
  else if(size == 2){
    Collider.r = 25;
    TEX_INDEX = MINI_ASTEROID;
  }
  else if(size == 3){
    Collider.r == 15;
    TEX_INDEX = VERY_MINI_ASTEROID;
  }
}

void Asteroid::split()
{ 
  if(size < 3){
    size++;
    set_size();
    for (int i=0; i<2; i++) {
      objects.push_back(new Asteroid(xPos, yPos, Angle, ((double) rand()/RAND_MAX) -0.5, ((float) rand()/RAND_MAX)-0.5, size));
    }
  }
  else dead = true;
}
