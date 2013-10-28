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

        virtual void update();

        //function for sending private values to other functions in bulk
        //(to avoid making a bunch of separate public 'get' methods)
        void get_values(float* xPos_out, float* yPos_out, float* Angle_out);

        virtual void render( int x, int y, float ang );
        virtual void render( int x, int y, float ang, const Uint8* currentKeyStates );

        virtual int get_cRad();

        int get_tex_index();

    protected:
        //radius of object's collider, centered on xPos,yPos
        int C_RAD;

        //the index of the default image to render for instances of this object
        int TEX_INDEX;

        //object's current position (represents the center of the ship, not the topleft corner)
        float xPos, yPos;

        //object's current angle
        float Angle;

};

#endif
