#include "Object.h"

Object::Object()
{
    xPos = 1.0;
    yPos = 1.0;
    Angle = 0;

    xVel = 0.0;
    yVel = 0.0;
    rotVel = 0.0;

    Collider.x = xPos;
    Collider.y = yPos;
    Collider.r = 1;

    can_take_damage = false;

    dead = false;

    TEX_INDEX = 1;
}

void Object::update()
{
}

void Object::onCollide( Object* collided_with )
{
}

void Object::takeDamage( int amount )
{
    if( can_take_damage )
        hitpoints -= amount;
}

void Object::get_values(float* xPos_out, float* yPos_out, float* Angle_out, float* xVel_out, float* yVel_out, float* rotVel_out)
{
    *xPos_out = xPos;
    *yPos_out = yPos;
    *Angle_out = Angle;
    *xVel_out = xVel;
    *yVel_out = yVel;
    *rotVel_out = rotVel;
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

int Object::get_type()
{
    return T_OBJ;
}

int Object::get_hitpoints()
{
    return hitpoints;
}

bool Object::is_dead()
{
    return dead;
}

void Object::render( int x, int y, float ang )
{
    textures[TEX_INDEX].render( x, y, NULL, ang );
}
