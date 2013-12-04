#ifndef _VEC2D_H
#define _VEC2D_H

#include <math.h>

class Vec2D
{
    public:
        //Initializes variables
        Vec2D();
        Vec2D(float x, float y);

        //Deallocates memory
        //~Vec2D();

        float get_x();
        float get_y();
        void set_x(float x);
        void set_y(float y);
        void set(float x, float y);
        float get_dist(Vec2D v2);
        float get_length();
        float dot(Vec2D v2);
        Vec2D add(Vec2D v2);
        Vec2D subtract(Vec2D v2);
        Vec2D multiply(float scale);
        Vec2D normalize();

    private:
        float X, Y;

};

#endif
