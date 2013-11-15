#ifndef _ASTEROID_H
#define _ASTEROID_H

#include "MovingObject.h"

class Asteroid : public MovingObject
{
    public:
        //Initializes variables
        Asteroid(float x, float y, float ang, float xv, float yv, int size);

        void update();

        int size;
        void set_size(int s);
        void split();

        int get_type();
};

#endif
