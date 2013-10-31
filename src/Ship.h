#ifndef _SHIP_H
#define _SHIP_H

#include "MovingObject.h"

class Ship : public MovingObject
{
    public:

        //Constructor: initializes the variables
        Ship(float xp = (float) SCREEN_WIDTH / 2, float yp = (float) SCREEN_HEIGHT / 2, float ang=0.0 );

        //Movement functions
        void thrust_b();
        void thrust_f();
        void rot_l();
        void rot_r();
        void thrust_l();
        void thrust_r();
        
        //ship's current hitpoints
        int hitpoints;
    protected:

        // Unenforced Constants
        //----------------------//

        // acceleration rate
        float SHIP_ACCEL;
        float SHIP_REV_ACCEL;
        float SHIP_ROT_ACCEL;

        //ship's maximum hitpoints
        int MAX_HP;

        //----------------------//

        
        
};
#endif
