#ifndef _OBJECT_H
#define _OBJECT_H

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

class Object
{
    public:
        //Initializes variables
        Object();

        //Deallocates memory
        //~Object();

        void update();

        //function for sending private values to other functions in bulk
        //(to avoid making a bunch of separate public 'get' methods)
        void get_values(float* xPos_out, float* yPos_out, float* Angle_out);

    protected:
        float xPos, yPos;

        float Angle;

        Circle Collider;


};

#endif
