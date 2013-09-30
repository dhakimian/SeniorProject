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
        static constexpr float SHIP_ACCEL = 0.08;
        static constexpr float SHIP_REV_ACCEL = 0.05;
        static constexpr float SHIP_ROT_ACCEL = 0.03;

        //Constructor: initializes the variables
        Player();

        //Takes key presses and adjusts the dot's velocity
        void handleEvent( SDL_Event& e );

        //bool checkCollision( 
        void move();

        void render(SDL_Renderer* ren);

        bool loadMedia(SDL_Renderer* ren);

        void freeMedia();

    private:
        //the textures that will be used
        //LTexture shipTex;
        //LTexture thr_bTex;
        //LTexture thr_lTex;
        //LTexture thr_rTex;
        //LTexture thr_fTex;

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
