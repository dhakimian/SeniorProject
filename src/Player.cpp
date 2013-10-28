/*This source code was based off part of a tutorial source file from lazyfoo.net which had the following 
 * copyright notice at the top:*/
/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
 * and may not be redistributed without written permission.*/
#include "Player.h"

Player::Player(float xp, float yp, float ang )
{
    // acceleration rate
    SHIP_ACCEL = 0.07;
    SHIP_REV_ACCEL = 0.04;
    SHIP_ROT_ACCEL = 0.03;

    xPos = xp;
    yPos = yp;

    Collider.x = xPos;
    Collider.y = yPos;
    Collider.r = 30;

    Angle = ang;

    MAX_HP = 100;
    hitpoints = 100;

    TEX_INDEX = PLAYER;
}

//client side code
void Player::render( int x, int y, float ang, const Uint8* currentKeyStates )
{
    // here is my(robs) added code that implements a cool ship that has some moving parts.

    //local variables resembling if movement keys are pushed. Includes both wasd and updownleftright.
    //makes less to type in each if statement
    bool upKey = currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_W];
    bool downKey = currentKeyStates[SDL_SCANCODE_DOWN] || currentKeyStates[SDL_SCANCODE_S];
    bool leftKey = currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_A];
    bool rightKey = currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_D];
    bool strafeLeft = currentKeyStates[SDL_SCANCODE_Q];
    bool strafeRight = currentKeyStates[SDL_SCANCODE_E];

    //renders the thruster images according to which button you pushed. works for both wasd and up/down/left/rt keys 
    //
    if(upKey)
        textures[PLAYER_THR_B].render( x, y, NULL, ang );
    if(leftKey && !downKey)
        textures[PLAYER_THR_L].render( x, y, NULL, ang );
    if(rightKey && !downKey)
        textures[PLAYER_THR_R].render( x, y, NULL, ang );
    if(downKey)
        textures[PLAYER_THR_F].render( x, y, NULL, ang );
    if(rightKey && downKey)
        textures[PLAYER_THR_R].render( x, y, NULL, ang );
    if(leftKey && downKey)
        textures[PLAYER_THR_L].render( x, y, NULL, ang );

    //these conditionals draw different wing orentations depending on which direction the ship is turning.
    if(downKey && !upKey) {
        textures[PLAYER].render( x, y, NULL, ang);
        textures[PLAYER_WNG_B].render(x, y, NULL, ang);
    } else if(leftKey && !rightKey && !downKey) {
        textures[PLAYER_Tlt_L].render( x, y, NULL, ang);
        textures[PLAYER_WNG_L].render( x, y, NULL, ang);
    } else if(rightKey && !leftKey && !downKey) {
        textures[PLAYER_Tlt_R].render( x, y, NULL, ang);
        textures[PLAYER_WNG_R].render( x, y, NULL, ang);
    } else if(upKey && !downKey && !leftKey && !rightKey && !strafeLeft && !strafeRight) {
        textures[PLAYER].render( x, y, NULL, ang);
        textures[PLAYER_WNG_NORM].render( x, y, NULL, ang);
    } else if(downKey && leftKey && rightKey) {
        textures[PLAYER].render( x, y, NULL, ang);
        textures[PLAYER_WNG_B].render( x, y, NULL, ang);
    } else if(leftKey && rightKey && downKey) {
        textures[PLAYER].render( x, y, NULL, ang);
        textures[PLAYER_WNG_B].render( x, y, NULL, ang);
    } else if((downKey && upKey) || (leftKey && rightKey)) {
        textures[PLAYER].render( x, y, NULL, ang);
        textures[PLAYER_WNG_NORM].render( x, y, NULL, ang);
    } else if(strafeRight && !strafeLeft) {
        textures[PLAYER_Tlt_R].render( x, y, NULL, ang);
        textures[PLAYER_WNG_NORM].render( x, y, NULL, ang);
    } else if(strafeLeft && !strafeRight) {
        textures[PLAYER_Tlt_L].render( x, y, NULL, ang);
        textures[PLAYER_WNG_NORM].render( x, y, NULL, ang);
    } else if(upKey && !downKey && !leftKey && !rightKey && strafeLeft && strafeRight) {
        textures[PLAYER].render( x, y, NULL, ang);
        textures[PLAYER_WNG_NORM].render( x, y, NULL, ang);
    } else if(!downKey && !upKey && !leftKey && !rightKey) {
        textures[PLAYER].render( x, y, NULL, ang);
        textures[PLAYER_WNG_NORM].render( x, y, NULL, ang);
    }
}
