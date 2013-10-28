#include "Object.h"

Object::Object()
{
    xPos = 1.0;
    yPos = 1.0;
    Angle = 0;

    Collider.x = xPos;
    Collider.y = yPos;
    Collider.r = Collider.r;

    TEX_INDEX = 1;
}

void Object::get_values(float* xPos_out, float* yPos_out, float* Angle_out)
{
    *xPos_out = xPos;
    *yPos_out = yPos;
    *Angle_out = Angle;
}

void Object::render( int x, int y, float ang )
{
    textures[TEX_INDEX].render( x, y, NULL, ang );
}

void Object::render( int x, int y, float ang, const Uint8* currentKeyStates )
{
    render( x, y, ang );
}
