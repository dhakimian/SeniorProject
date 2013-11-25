#include "Object.h"
#include <iostream>

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
    solid = true;
    team = -1;

    dead = false;

    animated = false;
    anim_loops = true;
    frame_num = 0;
    num_frames = 0;
    frame_w = 0;
    frame_h = 0;
    frames_x = 0;
    frames_y = 0;

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

int Object::get_team()
{
    return team;
}

int Object::get_hitpoints()
{
    return hitpoints;
}

bool Object::is_dead()
{
    return dead;
}

bool Object::is_solid()
{
    return solid;
}

void Object::render( int x, int y, float ang )
{
    if( animated )
    {
        LTexture* tex = &textures[TEX_INDEX];
        SDL_Rect frame;

        if( frame_w == 0 )
        {
            if( frames_x == 0 )
            {
                std::cerr<<"Either frame_w or frames_x must be defined for animated textures"<<std::endl;
                return;
            } else {
                frame_w = tex->getWidth()/frames_x;
            }
        }
        if( frame_h == 0 )
        {
            if( frames_y == 0 )
            {
                std::cerr<<"Either frame_h or frames_y must be defined for animated textures"<<std::endl;
                return;
            } else {
                frame_h = tex->getHeight()/frames_y;
            }
        }

        if( frames_x == 0 )
            frames_x = tex->getWidth()/frame_w;
        if( frames_y == 0 )
            frames_y = tex->getHeight()/frame_h;

        if( num_frames == 0 )
            num_frames = frames_x * frames_y;

        frame.w = frame_w;
        frame.h = frame_h;
        frame.x = (frame_num % frames_x) * frame_w;
        frame.y = (frame_num / frames_x) * frame_h;
        x += (tex->getWidth()/2-frame.w/2);
        y += (tex->getHeight()/2-frame.h/2);

        tex->render( x, y, &frame, ang );

        //if( (time % something) == 0 )
        //{
            //frame_num = (frame_num + 1) % num_frames;
            frame_num++;
            if( frame_num >= num_frames )
            {
                if( anim_loops )
                    frame_num %= num_frames;
                else
                    frame_num--;
            }
        //}

    } else
        textures[TEX_INDEX].render( x, y, NULL, ang );
}
