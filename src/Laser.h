#ifndef _LASER_H
#define _LASER_H

#include "MovingObject.h"
#ifdef __APPLE__
#include <SDL2_mixer/SDL_mixer.h>
#else
#include <SDL_mixer.h>
#endif

class Laser : public MovingObject
{
    public:
        //Initializes variables
        Laser();

        //Deallocates memory
        //~Laser();

        //how fast laser moves relative to ship (at the time of firing)
        static constexpr float VEL = 15;

        //how many cycles a laser lasts before it disappears
        static const int LIFESPAN = 100;

        void update();

        //call the function explode when the laser collides.
        void explode();

        //upgrade the laser to a new strength and look and sound. so far there are only 3 upgrades
        void upgrade(); 

        void set_values(float x, float y, float ang, float xv, float yv, int time);
        //int representing sound channel
        int channelint;
    private:
        //how many cycles the laser missile has left before it disappears
        int time_left;
        //strength of the laser
        int time_powerup;
        //weapon level determins the strength of the 
        int weapon_level;
        //renders a different explosion image depending on the index
        float img_index = -1;
        //boolean saying weather or not the laser collided with something.
        bool boom = false;
        //plays an explosions sound
        Mix_Chunk *explode_sound = NULL;
        


};

#endif
