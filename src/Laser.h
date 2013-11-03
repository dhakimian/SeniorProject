#ifndef _LASER_H
#define _LASER_H

#include "MovingObject.h"

class Laser : public MovingObject
{
    public:
        //Initializes variables
        Laser();

        //Deallocates memory
        //~Laser();

        //how fast laser moves relative to ship (at the time of firing)
        static const float VEL = 10;

        //how many cycles a laser lasts before it disappears
        static const int LIFESPAN = 100;

        void update();

        void set_values(float x, float y, float ang, float xv, float yv, int time);

    private:
        //how many cycles the laser missile has left before it disappears
        int time_left;


};

#endif
