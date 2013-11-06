#include "Object.h"

Object::Object()
{
    xPos = 1.0;
    yPos = 1.0;
    Angle = 0;

    Collider.x = xPos;
    Collider.y = yPos;
    Collider.r = 1;

    dead = false;

    TEX_INDEX = 1;
}

void Object::update()
{
}

void Object::get_values(float* xPos_out, float* yPos_out, float* Angle_out)
{
    *xPos_out = xPos;
    *yPos_out = yPos;
    *Angle_out = Angle;
}

Circle Object::get_collider()
{
    return Collider;
}

int Object::get_tex_index()
{
    return TEX_INDEX;
}

bool Object::is_dead()
{
    return dead;
}

void Object::render( int x, int y, float ang )
{
    textures[TEX_INDEX].render( x, y, NULL, ang );
}
