#ifndef _BOMB_H
#define _BOMB_H

#include "MovingObject.h"

class Bomb : public MovingObject
{
    public:
        //Initializes variables
        Bomb();

        //Deallocates memory
        //~Bomb();

        //how fast Bomb moves relative to ship (at the time of firing)
        static constexpr float BVEL = 12;

        //how many cycles a Bomb lasts before it disappears
        static const int BLIFESPAN = 50;

        void update();
        void explode();

        void set_values(float x, float y, float ang, float xv, float yv, int time);

    private:
        //how many cycles the laser missile has left before it disappears
        int time_left;
        float img_index;
        bool boom;
        


};

#endif