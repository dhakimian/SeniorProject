#ifndef _OBJECT_H
#define _OBJECT_H

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
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

        virtual Object* clone();

        //function for sending private values to other functions in bulk
        //(to avoid making a bunch of separate public 'get' methods)
        void get_values(float* xPos_out, float* yPos_out, float* Angle_out);
        void get_values(float* xPos_out, float* yPos_out, float* Angle_out, float* xVel_out, float* yVel_out, float* rotVel_out);

        void set_values(float xPos_in, float yPos_in, float Angle_in);
        void set_values(float xPos_in, float yPos_in, float Angle_in, float xVel_in, float yVel_in, float rotVel_in);

        virtual void render( int x, int y, float ang, bool centered=false );

        virtual void onCollide( Object* collided_with );
        virtual void whenColliding( Object* colliding_with );

        virtual void takeDamage(int amount);

        virtual Circle get_collider();

        int get_tex_index();

        int get_type();

        int get_team();

        int get_hitpoints();

        float get_mass();

        bool is_solid();

        bool is_dead();

        void die();

        bool is_persistent();

    protected:

        //the index of the default image to render for instances of this object
        int TEX_INDEX;

        //type identifier for this class (defined in Consatants)
        int TYPE;

        //amount of rgb in the image. defaults to full 255 for each, can be reduced to colorize image
        int red, green, blue;

        bool animated; //whether or not the image is to be animated
        bool anim_loops; //whether the animation loops or not
        int frame_delay; //how many cycles to wait between frames
        int frame_delay_left; //how many cycles to wait before going to the next frame
        int frame_num; //if animated, which frame to render
        int num_frames; //how many frames in the animation; defaults to frames_x*frames_y
                        //(you would use this if you didn't have enough frames to fill their image)
        int frames_x, frames_y; //how many frames of an animation are on each row and column of the image
        int frame_w, frame_h; //animation frame dimensions

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

        //whether this object should behave as a solid in collisions or ghost through everything
        bool solid;

        //objects's maximum hitpoints
        int MAX_HP;

        //object's current hitpoints
        int hitpoints;

        //object's mass in unspecified arbitrary units
        float mass;

        //self-explanatory
        bool can_take_damage;

        //how many cycles the object flashes red after taking damage
        int Dmg_flash_dur;
        //how many cycles are left to appear red
        int dmg_flash_rem;

        //The number of the team this object is on
        //(objects on the same team can not damage or collide with each other)
        //(objects on team==-1 CAN damage and collide with each other)
        int team;

        //if this is true, the object will be removed from the objects vector next cycle
        bool dead;

        //if this is true, the object will not be deleted when it is "dead".
        //This is necessary for things like lasers, which are pooled and re-used
        bool persistent;

};

#endif
