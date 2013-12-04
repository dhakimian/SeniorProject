/*
 * This code stolen/adapted from source linked to from here:
 * http://stackoverflow.com/questions/345838/ball-to-ball-collision-detection-and-handling
 */
#include "Vec2D.h"

Vec2D::Vec2D()
{
    set_x(0);
    set_y(0);
}

Vec2D::Vec2D(float x, float y)
{
    set_x(x);
    set_y(y);
}

void Vec2D::set_x(float x)
{
    X = x;
}

void Vec2D::set_y(float y)
{
    Y = y;
}

void Vec2D::set(float x, float y)
{
    set_x(x);
    set_y(y);
}

float Vec2D::get_x()
{ return X; }

float Vec2D::get_y()
{ return Y; }

float Vec2D::dot(Vec2D v2)
{
    return (float) get_x() * v2.get_x() + get_y() * v2.get_y();
}

float Vec2D::get_length()
{
    return (float) sqrt( X*X + Y*Y );
}

float Vec2D::get_dist(Vec2D v2)
{
    return (float) sqrt(
            (v2.get_x() - get_x()) * (v2.get_x() - get_x())
            + (v2.get_y() - get_y()) * (v2.get_y() - get_y())
            );
}

Vec2D Vec2D::add(Vec2D v2)
{
    Vec2D result;
    result.set_x( get_x() + v2.get_x() );
    result.set_y( get_y() + v2.get_y() );
    return result;
}

Vec2D Vec2D::subtract(Vec2D v2)
{
    Vec2D result;
    result.set_x( get_x() - v2.get_x() );
    result.set_y( get_y() - v2.get_y() );
    return result;
}

Vec2D Vec2D::multiply(float scale)
{
    Vec2D result;
    result.set_x( get_x() * scale );
    result.set_y( get_y() * scale );
    return result;
}

Vec2D Vec2D::normalize()
{
    float len = get_length();
    if( len != 0.0 )
    {
        X /= len;
        Y /= len;
    } else {
        set_x(0.0);
        set_y(0.0);
    }
    return *this;
}
