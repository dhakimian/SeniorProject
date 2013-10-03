#ifndef _PLAYER_H
#define _PLAYER_H

#include <math.h>
#include <string>
#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#endif

#include "Constants.h"
#include "Util.h"
#include "LTexture.h"
//#include "Ship.h"

class Player// : public Ship
{
    public:
        static const int SHIP_WIDTH = 39;
        static const int SHIP_HEIGHT = 46;

        // acceleration rate
        static constexpr float SHIP_ACCEL = 0.07;
        static constexpr float SHIP_REV_ACCEL = 0.05;
        static constexpr float SHIP_ROT_ACCEL = 0.03;

        //Constructor: initializes the variables
        Player();

        //Takes key presses and adjusts the dot's velocity
        void handleEvent( SDL_Event& e );

        //bool checkCollision( 
        void move();

        //functions for sending private values to other functions in bulk
        void get_values(float& xPos_out, float& yPos_out, float& xVel_out, float& yVel_out, float& Angle_out, float& rotVel_out);
        void get_values(float& xPos_out, float& yPos_out, float& Angle_out);

    private:
        //ship's position
        float xPos, yPos;

        //ship's current velocity
        float xVel, yVel;

        //ship's current angle
        float Angle;

        //ship's current rotational velocity
        float rotVel;
};
#endif
