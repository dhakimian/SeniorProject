#ifndef _OBJECT_H
#define _OBJECT_H

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#endif

#include <math.h>
#include <string>

#include "Constants.h"
#include "Util.h"
#include "LTexture.h"
#include "Collision.h"

class Object
{
    public:

        //Initializes variables
        Object();

        //Deallocates memory
        //~Object();

        virtual void update();

        //function for sending private values to other functions in bulk
        //(to avoid making a bunch of separate public 'get' methods)
        void get_values(float* xPos_out, float* yPos_out, float* Angle_out);
        void get_values(float* xPos_out, float* yPos_out, float* Angle_out, float* xVel_out, float* yVel_out, float* rotVel_out);

        virtual void render( int x, int y, float ang );

        virtual void onCollide( Object* collided_with );

        virtual void takeDamage(int amount);

        virtual Circle get_collider();

        int get_tex_index();

        virtual int get_type();

        int get_hitpoints();
        
        bool is_dead();

    protected:

        //the index of the default image to render for instances of this object
        int TEX_INDEX;

        //whether or not the image is to be animated
        bool animated;
        //whether the animation loops or not
        bool anim_loops;
        //if animated, which frame to render
        int frame_num;
        //how many frames in the animation; defaults tiles_x*tiles_y
        int num_frames;
        //how many tiles of an animation are on each row and column of the image
        int tiles_x, tiles_y;
        //animation frame dimensions
        int frame_w, frame_h;

        //object's current position (represents the center of the ship, not the topleft corner)
        float xPos, yPos;

        //object's current angle
        float Angle;

        //object's current velocity
        float xVel, yVel;

        //ship's current rotational velocity
        float rotVel;

        //copies of previous values in case of collision
        float xPos_old, yPos_old, xVel_old, yVel_old, rotVel_old;

        //Collider for this object
        //TODO:make this a shape superclass that can be either a circle or SDL_Rect
        //     because we may want some (stationary) objects to have a rectangular hitbox
        Circle Collider;

        //objects's maximum hitpoints
        int MAX_HP;

        //object's current hitpoints
        int hitpoints;

        bool can_take_damage;

        //if this is true, the object will be removed from the objects vector next cycle
        bool dead;

};

#endif
