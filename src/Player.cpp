/*This source code was based off part of a tutorial source file from lazyfoo.net which had the following 
 * copyright notice at the top:*/
/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
 * and may not be redistributed without written permission.*/
#include "Player.h"

Player::Player(float xp, float yp, float ang )
{
    xPos = xp;
    yPos = yp;

    Collider.x = xPos;
    Collider.y = yPos;

    Angle = ang;

    MAX_HP = 100;
    hitpoints = MAX_HP;

    TEX_INDEX = PLAYER;

    upKey = false;
    downKey = false;
    leftKey = false;
    rightKey = false;
    strafeLeft = false;
    strafeRight = false;

}

int Player::get_type()
{
    return T_PLAYER;
}

void Player::handle_keystate(const Uint8* currentKeyStates)
{
    upKey = currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_W];
    downKey = currentKeyStates[SDL_SCANCODE_DOWN] || currentKeyStates[SDL_SCANCODE_S];
    leftKey = currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_A];
    rightKey = currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_D];
    strafeLeft = currentKeyStates[SDL_SCANCODE_Q];
    strafeRight = currentKeyStates[SDL_SCANCODE_E];
    shootKey = currentKeyStates[SDL_SCANCODE_SPACE];

    if(upKey)
        thrust_b();
    if(downKey)
        thrust_f();
    if(leftKey)
        rot_l();
    if(rightKey)
        rot_r();
    if(strafeLeft)
        thrust_r();
    if(strafeRight)
        thrust_l();
    if(shootKey)
        shoot();

}

//client side code
void Player::render( int x, int y, float ang )
{
    // here is my(robs) added code that implements a cool ship that has some moving parts.


    //renders the thruster images according to which keys are pressed.
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
