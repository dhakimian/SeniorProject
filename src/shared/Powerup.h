#ifndef _POWERUP_H
#define _POWERUP_H

#include "MovingObject.h"

class Powerup : public MovingObject
{
    public:
        //Initializes variables
        Powerup(); //Empty constructor. Only use if you will be copying data from another instance of this class (like with memcpy)
        Powerup(float x, float y, float ang, float xv, float yv, float rv=frandBetween(-30,30)/10);

        void onCollide( Object* collided_with );
        void whenColliding( Object* colliding_with );

        Object* clone() { return new Powerup(*this); }

    private:

};

#endif
