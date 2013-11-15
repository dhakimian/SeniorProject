#ifndef _MOVINGOBJECT_H
#define _MOVINGOBJECT_H

#include "Object.h"

class MovingObject : public Object
{
    public:
        //Initializes variables
        MovingObject();

        //Deallocates memory
        //~MovingObject();

        void update();

        void onCollide( Object* collided_with );

        int get_type();

    protected:

};

#endif
