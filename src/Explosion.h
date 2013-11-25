#ifndef _EXPLOSION_H
#define _EXPLOSION_H

#include "MovingObject.h"

class Explosion : public MovingObject
{
    public:
        //Initializes variables
        Explosion(float xp, float yp, float xv = 0.0, float yv = 0.0);

        void update();

        int get_type();

    private:

        int prev_frame_num;

};

#endif
