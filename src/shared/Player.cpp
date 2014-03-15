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
    TEX_INDEX = PLAYER;

    persistent = true;

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
    shootKey = false;

    TYPE = T_PLAYER;
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
}

void Player::handle_keystate(Keystate keystate)
{
    upKey = keystate.upKey;
    downKey = keystate.downKey;
    leftKey = keystate.leftKey;
    rightKey = keystate.rightKey;
    strafeLeft = keystate.strafeLeft;
    strafeRight = keystate.strafeRight;
    shootKey = keystate.shootKey;
}

void Player::update()
{
    Ship::update();
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
            Mix_PlayChannel(7, g_sounds[THRUST], 0);
        else
            Mix_Resume(7);
    }
    if(!(rightKey || leftKey || upKey || downKey || strafeRight || strafeLeft) && SOUND_ON)
    {
        Mix_Pause(7);
    }
}

void Player::render( int x, int y, float ang, bool centered )
{
    // here is my(robs) added code that implements a cool ship that has some moving parts.

    //renders the thruster images according to which keys are pressed.
    if(upKey)
        g_textures[PLAYER_THR_B].render_center( x, y, NULL, ang );
    if(leftKey && !downKey)
        g_textures[PLAYER_THR_L].render_center( x, y, NULL, ang );
    if(rightKey && !downKey)
        g_textures[PLAYER_THR_R].render_center( x, y, NULL, ang );
    if(downKey)
        g_textures[PLAYER_THR_F].render_center( x, y, NULL, ang );
    if(rightKey && downKey)
        g_textures[PLAYER_THR_R].render_center( x, y, NULL, ang );
    if(leftKey && downKey)
        g_textures[PLAYER_THR_L].render_center( x, y, NULL, ang );

    //these conditionals draw different wing orentations depending on which direction the ship is turning.
    if(downKey && !upKey) {
        g_textures[TEX_TEAM_INDEX_BODY].render_center( x, y, NULL, ang);
        g_textures[PLAYER_WNG_B].render_center(x, y, NULL, ang);
    } else if(leftKey && !rightKey && !downKey) {
        g_textures[TEX_TEAM_INDEX_L].render_center( x, y, NULL, ang);
        g_textures[PLAYER_WNG_L].render_center( x, y, NULL, ang);
    } else if(rightKey && !leftKey && !downKey) {
        g_textures[TEX_TEAM_INDEX_R].render_center( x, y, NULL, ang);
        g_textures[PLAYER_WNG_R].render_center( x, y, NULL, ang);
    } else if(upKey && !downKey && !leftKey && !rightKey && !strafeLeft && !strafeRight) {
        g_textures[TEX_TEAM_INDEX_BODY].render_center( x, y, NULL, ang);
        g_textures[PLAYER_WNG_NORM].render_center( x, y, NULL, ang);
    } else if(downKey && leftKey && rightKey) {
        g_textures[TEX_TEAM_INDEX_BODY].render_center( x, y, NULL, ang);
        g_textures[PLAYER_WNG_B].render_center( x, y, NULL, ang);
    } else if(leftKey && rightKey && downKey) {
        g_textures[TEX_TEAM_INDEX_BODY].render_center( x, y, NULL, ang);
        g_textures[PLAYER_WNG_B].render_center( x, y, NULL, ang);
    } else if((downKey && upKey) || (leftKey && rightKey)) {
        g_textures[TEX_TEAM_INDEX_BODY].render_center( x, y, NULL, ang);
        g_textures[PLAYER_WNG_NORM].render_center( x, y, NULL, ang);
    } else if(strafeRight && !strafeLeft) {
        g_textures[TEX_TEAM_INDEX_R].render_center( x, y, NULL, ang);
        g_textures[PLAYER_WNG_NORM].render_center( x, y, NULL, ang);
    } else if(strafeLeft && !strafeRight) {
        g_textures[TEX_TEAM_INDEX_L].render_center( x, y, NULL, ang);
        g_textures[PLAYER_WNG_NORM].render_center( x, y, NULL, ang);
    } else if(upKey && !downKey && !leftKey && !rightKey && strafeLeft && strafeRight) {
        g_textures[TEX_TEAM_INDEX_BODY].render_center( x, y, NULL, ang);
        g_textures[PLAYER_WNG_NORM].render_center( x, y, NULL, ang);
    } else if(!downKey && !upKey && !leftKey && !rightKey) {
        g_textures[TEX_TEAM_INDEX_BODY].render_center( x, y, NULL, ang);
        g_textures[PLAYER_WNG_NORM].render_center( x, y, NULL, ang);
    }
}
