#ifndef _MOVINGOBJECT_H
#define _MOVINGOBJECT_H

#include "Object.h"
#ifdef __APPLE__
#include <SDL2_mixer/SDL_mixer.h>
#else
#include <SDL_mixer.h>
#endif

class MovingObject : public Object
{
    public:
        //Initializes variables
        MovingObject();

        //Deallocates memory
        //~MovingObject();

        void update();

        void onCollide( Object* collided_with );
        void whenColliding( Object* colliding_with );

        int get_type();

    protected:

};

#endif
