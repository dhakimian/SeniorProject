#ifndef _MOVINGOBJECT_H
#define _MOVINGOBJECT_H

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

#include "Object.h"

class MovingObject : public Object
{
    public:
        //Initializes variables
        MovingObject();

        //Deallocates memory
        //~MovingObject();

        void update();

        //functions for sending private values to other functions in bulk
        //(to avoid making a bunch of separate public 'get' methods)
        void get_values(float* xPos_out, float* yPos_out, float* Angle_out);
        void get_values(float* xPos_out, float* yPos_out, float* xVel_out, float* yVel_out, float* Angle_out, float* rotVel_out);

    protected:
        //object's current velocity
        float xVel, yVel;

        //ship's current rotational velocity
        float rotVel;

};

#endif
