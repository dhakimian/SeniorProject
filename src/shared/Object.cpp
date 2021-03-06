#include "Object.h"
#include <iostream>

Object::Object() {
    ID = this;

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
    mass = 30;
    score = 0;

    dead = false;
    persistent = false;

    animated = false;
    anim_loops = true;
    frame_delay = 0;
    frame_delay_left = frame_delay;
    frame_num = 0;
    num_frames = 0;
    frame_w = 0;
    frame_h = 0;
    frames_x = 0;
    frames_y = 0;

    fps = -1;

    red = 255;
    green = 255;
    blue = 255;
    Dmg_flash_dur = 10;
    dmg_flash_rem = 0;

    TEX_INDEX = 1;
    TYPE = T_OBJ;
}

void Object::update() {
    if( can_take_damage ) {
        if( dmg_flash_rem > 0 ) {
            dmg_flash_rem--;
            uint diff = 255 - green;
            green += diff/4;
            blue += diff/4;
        }
        if( dmg_flash_rem <= 0 ) {
            red = 255;
            green = 255;
            blue = 255;
        }
    }

    if( animated ) {
        if( num_frames == 0 )
            num_frames = frames_x * frames_y;

        //if( (time % something) == 0 )
        if( frame_delay_left == 0 ) {
            frame_delay_left = frame_delay;
            //frame_num = (frame_num + 1) % num_frames;
            frame_num++;
            if( frame_num >= num_frames ) {
                if( anim_loops )
                    frame_num %= num_frames;
                else
                    frame_num--;
            }
        }
        else
            frame_delay_left--;
    }
}

Object* Object::clone() {
}

void Object::onCollide( Object* collided_with ) {
}

void Object::whenColliding( Object* colliding_with ) {
}

void Object::takeDamage( int amount ) {
    if( can_take_damage && amount > 0 ) {
        hitpoints -= amount;
        dmg_flash_rem = Dmg_flash_dur;
        red = 255;
        green = 150;
        blue = 150;
    }
}

void Object::get_values(float* xPos_out, float* yPos_out, float* Angle_out, float* xVel_out, float* yVel_out, float* rotVel_out) {
    *xPos_out = xPos;
    *yPos_out = yPos;
    *Angle_out = Angle;
    *xVel_out = xVel;
    *yVel_out = yVel;
    *rotVel_out = rotVel;
}

void Object::get_values(float* xPos_out, float* yPos_out, float* Angle_out) {
    *xPos_out = xPos;
    *yPos_out = yPos;
    *Angle_out = Angle;
}

void Object::set_values(float xPos_in, float yPos_in, float Angle_in, float xVel_in, float yVel_in, float rotVel_in) {
    xPos = xPos_in;
    yPos = yPos_in;
    Angle = Angle_in;
    xVel = xVel_in;
    yVel = yVel_in;
    rotVel = rotVel_in;
}

void Object::set_values(float xPos_in, float yPos_in, float Angle_in) {
    xPos = xPos_in;
    yPos = yPos_in;
    Angle = Angle_in;
}

const void* Object::get_ID()
{ return ID; }

Circle Object::get_collider()
{ return Collider; }

int Object::get_tex_index()
{ return TEX_INDEX; }

int Object::get_type()
{ return TYPE; }

int Object::get_team()
{ return team; }

int Object::get_hitpoints()
{ return hitpoints; }

float Object::get_mass()
{ return mass; }

int Object::get_score()
{ return score; }

void Object::add_score( int amount ) {
    score += amount;
}

bool Object::is_solid()
{ return solid; }

bool Object::is_dead()
{ return dead; }

void Object::die()
{ dead = true; }

bool Object::is_persistent()
{ return persistent; }

void Object::render( int x, int y, float ang, bool centered ) {
    LTexture* tex = &g_textures[TEX_INDEX];
    tex->setColor( red, green, blue );
    /*
    if( !solid )
    {
       tex->setBlendMode( SDL_BLENDMODE_BLEND );
       tex->setAlpha( 155 );
    }
    */

    if( animated ) {
        //std::cout<<"animation"<<std::endl;
        //std::cout<<this->frame_num<<"/"<<this->num_frames<<std::endl;

        SDL_Rect frame;

        if( frame_w == 0 ) {
            if( frames_x == 0 ) {
                std::cerr<<"Either frame_w or frames_x must be defined for animated textures"<<std::endl;
                return;
            } else {
                frame_w = tex->getWidth()/frames_x;
            }
        }
        if( frame_h == 0 ) {
            if( frames_y == 0 ) {
                std::cerr<<"Either frame_h or frames_y must be defined for animated textures"<<std::endl;
                return;
            }
            else {
                frame_h = tex->getHeight()/frames_y;
            }
        }

        if( frames_x == 0 )
            frames_x = tex->getWidth()/frame_w;
        if( frames_y == 0 )
            frames_y = tex->getHeight()/frame_h;

        frame.w = frame_w;
        frame.h = frame_h;
        frame.x = (frame_num % frames_x) * frame_w;
        frame.y = (frame_num / frames_x) * frame_h;

        tex->render( x-frame.w/2, y-frame.h/2, &frame, ang );
    }
    else {
        if( centered )
            g_textures[TEX_INDEX].render_center( x, y, NULL, ang );
        else
            g_textures[TEX_INDEX].render( x, y, NULL, ang );
    }
}
