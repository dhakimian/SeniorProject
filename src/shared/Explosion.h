#ifndef _EXPLOSION_H
#define _EXPLOSION_H

#include "MovingObject.h"

class Explosion : public MovingObject
{
    public:
        //Initializes variables
        Explosion(); //Empty constructor. Only use if you will be copying data from another instance of this class (like with memcpy)
        Explosion(float xp, float yp, float xv = 0.0, float yv = 0.0);

        void update();

        Object* clone() { return new Explosion(*this); }

    private:

        int prev_frame_num;

};

#endif
