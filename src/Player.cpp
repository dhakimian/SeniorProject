#include "Player.h"

Player::Player()
{
    xPos = (float) SCREEN_WIDTH / 2;
    yPos = (float) SCREEN_HEIGHT / 2;

    xVel = 0.0;
    yVel = 0.0;

    Angle = 0.0;

    rotVel = 0.0;
}

/*
   Player::~Player()
   {

   }
   */

void Player::handleEvent( SDL_Event& e )
{
    double ang = M_PI * Angle;
    ang = ang / 180;

    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    if( currentKeyStates[ SDL_SCANCODE_UP ] )
    {
        xVel += SHIP_ACCEL * sin(ang);
        yVel -= SHIP_ACCEL * cos(ang);
    }
    if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
    {
        xVel -= SHIP_REV_ACCEL * sin(ang);
        yVel += SHIP_REV_ACCEL * cos(ang);
    }
    if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
    {
        rotVel -= SHIP_ROT_ACCEL;
    }
    if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
    {
        rotVel += SHIP_ROT_ACCEL;
    }
}

void Player::move()
{
    //Move the ship left or right
    xPos += xVel;

    //If the ship went too far to the left
    if( xPos < 0 )
    {
        xPos = 0.0;
        xVel = 0.0;
    }
    //If the ship went too far to the right
    if ( xPos + SHIP_WIDTH > LEVEL_WIDTH )
    {
        xPos = (float) LEVEL_WIDTH - SHIP_WIDTH;
        xVel = 0.0;
    }

    //Move the ship up or down
    yPos += yVel;

    //If the ship went too far up
    if( yPos < 0 )
    {
        yPos = 0.0;
        yVel = 0.0;
    }
    //If the ship went too far down
    if( yPos + SHIP_HEIGHT > LEVEL_HEIGHT )
    {
        yPos = (float) LEVEL_HEIGHT - SHIP_HEIGHT;
        yVel = 0.0;
    }

    Angle += rotVel;
}

void Player::get_values(float& xPos_out, float& yPos_out, float& xVel_out, float& yVel_out, float& Angle_out, float& rotVel_out)
{
    xPos_out = xPos;
    yPos_out = yPos;
    xVel_out = xVel;
    yVel_out = yVel;
    Angle_out = Angle;
    rotVel_out = rotVel;
}

void Player::get_values(float& xPos_out, float& yPos_out, float& Angle_out)
{
    xPos_out = xPos;
    yPos_out = yPos;
    Angle_out = Angle;
}
