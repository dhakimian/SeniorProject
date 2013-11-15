#ifndef _ASTEROID_H
#define _ASTEROID_H

#include "MovingObject.h"

class Asteroid : public MovingObject
{
    public:
        //Initializes variables
        Asteroid(float x, float y, float ang, float xv, float yv, int size);

	int size;
        //Deallocates memory
        //~Asteroid();
	void set_size();
	
	void split();
};

#endif
