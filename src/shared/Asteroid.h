#ifndef _ASTEROID_H
#define _ASTEROID_H

#include "MovingObject.h"

class Asteroid : public MovingObject
{
    public:
        //Initializes variables
        Asteroid(); //Empty constructor. Only use if you will be copying data from another instance of this class (like with memcpy)
        Asteroid(float x, float y, float ang, float xv, float yv, float rv, int size);

        void update();

        int size;
        void set_size(int s);
        int get_size();
        void split();

        Object* clone() { return new Asteroid(*this); }

    private:

        //how many smaller asteroids a bigger one splits into
        int split_num;
        float mass_max; //the mass of the largest size of asteroid
        int powerup_chance; //percentage chance that a powerup will spawn when the asteroid splits

};

#endif
