#ifndef _MOVINGOBJECT_H
#define _MOVINGOBJECT_H

#include "Object.h"

class MovingObject
{
    public:
        //Initializes variables
        MovingObject();

        //Deallocates memory
        ~MovingObject();

    private:
        float xVel, yVel;

};

#endif
