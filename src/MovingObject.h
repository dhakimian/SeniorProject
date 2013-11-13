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

        //functions for sending private values to other functions in bulk
        //(to avoid making a bunch of separate public 'get' methods)
        void get_values(float* xPos_out, float* yPos_out, float* Angle_out);
        void get_values(float* xPos_out, float* yPos_out, float* xVel_out, float* yVel_out, float* Angle_out, float* rotVel_out);

    protected:
        //object's current velocity
        float xVel, yVel;

        //ship's current rotational velocity
        float rotVel;

        //copies of previous values in case of collision
        float xPos_old, yPos_old, xVel_old, yVel_old, rotVel_old;

};

#endif
