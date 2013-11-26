#ifndef _PLANET_H
#define _PLANET_H

#include "Object.h"

class Planet : public Object
{
    public:
        //Initializes variables
        Planet(float xp = 0.0, float yp = 0.0, float ang = 0.0 );

        //Deallocates memory
        //~Planet();

        int get_type();

    private:
        //gravity radius of effect
        int G_RAD;

};

#endif
