#ifndef _POWERUP_H
#define _POWERUP_H

#include "MovingObject.h"

class Powerup : public MovingObject
{
    public:
        //Initializes variables
        Powerup(float x, float y, float ang, float xv, float yv, float rv=frandBetween(-30,30)/10);

        void onCollide( Object* collided_with );
        void whenColliding( Object* colliding_with );

        int get_type();

    private:

};

#endif
