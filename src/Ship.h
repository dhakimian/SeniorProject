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
//#include "MovingObject.h"

class Ship // : public MovingObject
{
    public:

        //Constructor: initializes the variables
        Ship();

        //Movement functions
        void thrust_b();
        void thrust_l();
        void thrust_r();
        void thrust_f();

        // update the position based on current velocity
        void update_pos();

        //functions for sending private values to other functions in bulk
        void get_values(float* xPos_out, float* yPos_out, float* xVel_out, float* yVel_out, float* Angle_out, float* rotVel_out);
        void get_values(float* xPos_out, float* yPos_out, float* Angle_out);

        //SDL_Point getCenter();

    protected:

        // Unenforced Constants
        //----------------------//
        //int SHIP_RADIUS;

        // acceleration rate
        float SHIP_ACCEL;
        float SHIP_REV_ACCEL;
        float SHIP_ROT_ACCEL;

        //ship's maximum hitpoints
        int MAX_HP;

        //----------------------//

        //ship's collider
        Circle Collider;

        //ship's current position (represents the center of the ship, not the topleft corner)
        float xPos, yPos;

        //ship's current velocity
        float xVel, yVel;

        //ship's current angle
        float Angle;

        //ship's current rotational velocity
        float rotVel;

        //ship's current hitpoints
        int cur_hp;
        
};
#endif
