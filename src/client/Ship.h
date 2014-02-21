#ifndef _SHIP_H
#define _SHIP_H

#include "MovingObject.h"
#include "Laser.h"
#include <vector>
#ifdef __APPLE__
#include <SDL2_mixer/SDL_mixer.h>
#else
#include <SDL_mixer.h>
#endif


class Ship : public MovingObject
{
    public:

        //Constructor: initializes the variables
        Ship(float xp = (float) SCREEN_WIDTH / 2, float yp = (float) SCREEN_HEIGHT / 2, float ang=0.0 );

        //Movement functions
        void thrust_b();
        void thrust_f();
        void rot_l();
        void rot_r();
        void thrust_l();
        void thrust_r();

        void update();

        void onCollide( Object* collided_with );

        int get_type();

        //shoots a laser
        void shoot();

        //makes the lasers more powerful when you pickup a powerup
        void weapons_upgrade();

    protected:

        // Unenforced Constants
        //----------------------//

        // acceleration rate
        float SHIP_ACCEL;
        float SHIP_REV_ACCEL;
        float SHIP_ROT_ACCEL;
        //----------------------//

        Mix_Chunk *shoot_sound_current_strength;
        int soundindex;
        int Upgrade_cooldown;
        int upgrade_cooldown_rem;

        //The size of the laser object pool
        int pool_size;

        //laser object pool
        std::vector<Laser*> laser_pool;

        //a copy of which laser objects are currently in the objects vector
        std::vector<Laser*> active_lasers;

        //time needed between shots
        int Cooldown;
        //time remaining before another laser can be shot
        int cooldown_rem;

};
#endif
