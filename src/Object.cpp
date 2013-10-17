#include "Object.h"

Object::Object()
{
    xPos = (float) SCREEN_WIDTH / 2;
    yPos = (float) SCREEN_HEIGHT / 2;
    Angle = 0;

    Collider.x = xPos;
    Collider.y = yPos;
    Collider.r = Collider.r;
}

void Object::get_values(float* xPos_out, float* yPos_out, float* Angle_out)
{
    *xPos_out = xPos;
    *yPos_out = yPos;
    *Angle_out = Angle;
}
