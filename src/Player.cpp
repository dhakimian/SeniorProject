/*This source code was based off part of a tutorial source file from lazyfoo.net which had the following 
 * copyright notice at the top:*/
/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
 * and may not be redistributed without written permission.*/
#include "Player.h"

Player::Player()
{
    // acceleration rate
    SHIP_ACCEL = 0.07;
    SHIP_REV_ACCEL = 0.04;
    SHIP_ROT_ACCEL = 0.03;

    xPos = (float) SCREEN_WIDTH / 2;
    yPos = (float) SCREEN_HEIGHT / 2;

    Collider.x = xPos;
    Collider.y = yPos;
    Collider.r = 20;

    xVel = 0.0;
    yVel = 0.0;

    Angle = 0.0;

    rotVel = 0.0;

    MAX_HP = 100;
    cur_hp = 100;
}

/*
void Player::handleEvent( SDL_Event& e )
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    if( currentKeyStates[ SDL_SCANCODE_UP ] )
        thrust_b();
    if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
        thrust_f();
    if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
        thrust_l();
    if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
        thrust_r();
}
*/
