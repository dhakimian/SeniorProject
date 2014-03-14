#ifndef _LASER_H
#define _LASER_H

#include "MovingObject.h"
#include "Explosion.h"

class Laser : public MovingObject
{
    public:
        //Initializes variables
        Laser();

        Object* clone() { return new Laser(*this); }

        //how fast laser moves relative to ship (at the time of firing)
        static constexpr float VEL = 10;

        //how many cycles a laser lasts before it disappears
        static const int LIFESPAN = 100;

        void update();

        void upgrade();

        void onCollide( Object* collided_with );

        //void set_values(float x, float y, float ang, float xv, float yv, int time);
        void set_values(Object* ship, float x, float y, float ang, float xv, float yv);

        int get_time_left();

        Object* get_owner();

    private:
        //how many cycles the laser missile has left before it disappears
        int time_left;

        //weapon level determins the strength of the laser
        int weapon_level;

        //player who shot this laser
        Object* owner;


};

#endif
