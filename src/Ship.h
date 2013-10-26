#ifndef _SHIP_H
#define _SHIP_H

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#endif
#include <math.h>
#include <string>

#include "Constants.h"
#include "Util.h"
#include "LTexture.h"
#include "MovingObject.h"

class Ship : public MovingObject
{
    public:

        //Constructor: initializes the variables
        Ship();

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
