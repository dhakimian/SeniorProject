/*This source code was based off part of a tutorial source file from lazyfoo.net which had the following 
 * copyright notice at the top:*/
/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
 * and may not be redistributed without written permission.*/
#include "Player.h"

Player::Player(int teamnumber, float xp, float yp, float ang )
{
    xPos = xp;
    yPos = yp;

    Collider.x = xPos;
    Collider.y = yPos;

    Angle = ang;

    MAX_HP = 1000;
    hitpoints = MAX_HP;

    team = teamnumber;

    if (team == 2)
    {
        //TEX_INDEX = PLAYER_O;
        TEX_TEAM_INDEX_BODY = PLAYER_O;
        TEX_TEAM_INDEX_L = PLAYER_O_Tlt_L;
        TEX_TEAM_INDEX_R = PLAYER_O_Tlt_R;
    }else if (team == 3)
    {
        //TEX_INDEX = PLAYER_O;
        TEX_TEAM_INDEX_BODY = PLAYER_O;
        TEX_TEAM_INDEX_L = PLAYER_O_Tlt_L;
        TEX_TEAM_INDEX_R = PLAYER_O_Tlt_R;
    }else if (team == 4)
    {
        //TEX_INDEX = PLAYER_O;
        TEX_TEAM_INDEX_BODY = PLAYER_O;
        TEX_TEAM_INDEX_L = PLAYER_O_Tlt_L;
        TEX_TEAM_INDEX_R = PLAYER_O_Tlt_R;
    }else{
    //TEX_INDEX = PLAYER;
    TEX_TEAM_INDEX_BODY = PLAYER;
    TEX_TEAM_INDEX_L = PLAYER_Tlt_L;
    TEX_TEAM_INDEX_R = PLAYER_Tlt_R;
    }

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

    if( SOUND_ON && (rightKey || leftKey || upKey || downKey || strafeRight || strafeLeft ) && (hitpoints > 0) )
    {
        if(Mix_Playing(7) == 0 )
            Mix_PlayChannel(7, sounds[THRUST], 0);
        else
            Mix_Resume(7);
    }
    if(!(rightKey || leftKey || upKey || downKey || strafeRight || strafeLeft) && SOUND_ON)
    {
        Mix_Pause(7);
    }


}

//client side code
void Player::render( int x, int y, float ang, bool centered )
{
    // here is my(robs) added code that implements a cool ship that has some moving parts.


    //renders the thruster images according to which keys are pressed.
    if(upKey)
        textures[PLAYER_THR_B].render_center( x, y, NULL, ang );
    if(leftKey && !downKey)
        textures[PLAYER_THR_L].render_center( x, y, NULL, ang );
    if(rightKey && !downKey)
        textures[PLAYER_THR_R].render_center( x, y, NULL, ang );
    if(downKey)
        textures[PLAYER_THR_F].render_center( x, y, NULL, ang );
    if(rightKey && downKey)
        textures[PLAYER_THR_R].render_center( x, y, NULL, ang );
    if(leftKey && downKey)
        textures[PLAYER_THR_L].render_center( x, y, NULL, ang );

    //these conditionals draw different wing orentations depending on which direction the ship is turning.
    if(downKey && !upKey) {
        textures[TEX_TEAM_INDEX_BODY].render_center( x, y, NULL, ang);
        textures[PLAYER_WNG_B].render_center(x, y, NULL, ang);
    } else if(leftKey && !rightKey && !downKey) {
        textures[TEX_TEAM_INDEX_L].render_center( x, y, NULL, ang);
        textures[PLAYER_WNG_L].render_center( x, y, NULL, ang);
    } else if(rightKey && !leftKey && !downKey) {
        textures[TEX_TEAM_INDEX_R].render_center( x, y, NULL, ang);
        textures[PLAYER_WNG_R].render_center( x, y, NULL, ang);
    } else if(upKey && !downKey && !leftKey && !rightKey && !strafeLeft && !strafeRight) {
        textures[TEX_TEAM_INDEX_BODY].render_center( x, y, NULL, ang);
        textures[PLAYER_WNG_NORM].render_center( x, y, NULL, ang);
    } else if(downKey && leftKey && rightKey) {
        textures[TEX_TEAM_INDEX_BODY].render_center( x, y, NULL, ang);
        textures[PLAYER_WNG_B].render_center( x, y, NULL, ang);
    } else if(leftKey && rightKey && downKey) {
        textures[TEX_TEAM_INDEX_BODY].render_center( x, y, NULL, ang);
        textures[PLAYER_WNG_B].render_center( x, y, NULL, ang);
    } else if((downKey && upKey) || (leftKey && rightKey)) {
        textures[TEX_TEAM_INDEX_BODY].render_center( x, y, NULL, ang);
        textures[PLAYER_WNG_NORM].render_center( x, y, NULL, ang);
    } else if(strafeRight && !strafeLeft) {
        textures[TEX_TEAM_INDEX_R].render_center( x, y, NULL, ang);
        textures[PLAYER_WNG_NORM].render_center( x, y, NULL, ang);
    } else if(strafeLeft && !strafeRight) {
        textures[TEX_TEAM_INDEX_L].render_center( x, y, NULL, ang);
        textures[PLAYER_WNG_NORM].render_center( x, y, NULL, ang);
    } else if(upKey && !downKey && !leftKey && !rightKey && strafeLeft && strafeRight) {
        textures[TEX_TEAM_INDEX_BODY].render_center( x, y, NULL, ang);
        textures[PLAYER_WNG_NORM].render_center( x, y, NULL, ang);
    } else if(!downKey && !upKey && !leftKey && !rightKey) {
        textures[TEX_TEAM_INDEX_BODY].render_center( x, y, NULL, ang);
        textures[PLAYER_WNG_NORM].render_center( x, y, NULL, ang);
    }
}

