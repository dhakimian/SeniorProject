/*This source code was based off part of a tutorial source file from lazyfoo.net which had the following 
 * copyright notice at the top:*/
/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
 * and may not be redistributed without written permission.*/
#include "Player.h"
#include <iostream>

Player::Player(int teamnumber, float xp, float yp, float ang )
{
    xPos = xp;
    yPos = yp;

    Collider.x = xPos;
    Collider.y = yPos;

    Angle = ang;

    MAX_HP = 1000;
    hitpoints = MAX_HP;

    Respawn_time = 500;
    respawn_time_rem = Respawn_time;

    team = teamnumber;

    TEX_INDEX = PLAYER_BODY;

    persistent = true;

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
    if ( this->is_dead() )
    {
        respawn_time_rem--;
        //std::cout<<"Respawn in: "<<respawn_time_rem<<std::endl;
        if( respawn_time_rem <= 0 )
        {
            respawn_time_rem = Respawn_time;
            //std::cout<<"Respawning"<<std::endl;
            respawn();
        }
    }
    else
    {
        //std::cout<<"updateteam: "<<team;
        //std::cout<<" | TEX_INDEX: "<<TEX_INDEX<<std::endl;
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
}

void Player::respawn()
{
    set_values( frandBetween(0,LEVEL_WIDTH),
            frandBetween(0,LEVEL_HEIGHT),
            frandBetween(0,360),
            0,0,0);
    Collider.x = xPos;
    Collider.y = yPos;
    dead=false;
    hitpoints = MAX_HP;
    soundindex = 0;
    Cooldown = 30;
    for( uint i=0; i < laser_pool.size(); i++ )
        laser_pool[i]->reset();
    for( uint i=0; i<active_lasers.size(); i++ )
        active_lasers[i]->reset();

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

    LTexture* bodycolor_tex = &g_textures[PLAYER_BODY_COLOR];
    LTexture* tltLcolor_tex = &g_textures[PLAYER_Tlt_L_COLOR];
    LTexture* tltRcolor_tex = &g_textures[PLAYER_Tlt_R_COLOR];
    RGB teamcolor = TeamColors[team-1];
    bodycolor_tex->setColor( teamcolor.r, teamcolor.g, teamcolor.b );
    tltLcolor_tex->setColor( teamcolor.r, teamcolor.g, teamcolor.b );
    tltRcolor_tex->setColor( teamcolor.r, teamcolor.g, teamcolor.b );

    //these conditionals draw different wing orentations depending on which direction the ship is turning.
    if(downKey && !upKey) {
        g_textures[PLAYER_BODY].render_center( x, y, NULL, ang);
        bodycolor_tex->render_center( x, y, NULL, ang);
        g_textures[PLAYER_WNG_B].render_center( x, y, NULL, ang);
    } else if(leftKey && !rightKey && !downKey) {
        g_textures[PLAYER_Tlt_L].render_center( x, y, NULL, ang);
        tltLcolor_tex->render_center( x, y, NULL, ang);
        g_textures[PLAYER_WNG_L].render_center( x, y, NULL, ang);
    } else if(rightKey && !leftKey && !downKey) {
        g_textures[PLAYER_Tlt_R].render_center( x, y, NULL, ang);
        tltRcolor_tex->render_center( x, y, NULL, ang);
        g_textures[PLAYER_WNG_R].render_center( x, y, NULL, ang);
    } else if(upKey && !downKey && !leftKey && !rightKey && !strafeLeft && !strafeRight) {
        g_textures[PLAYER_BODY].render_center( x, y, NULL, ang);
        bodycolor_tex->render_center( x, y, NULL, ang);
        g_textures[PLAYER_WNG_NORM].render_center( x, y, NULL, ang);
    } else if(downKey && leftKey && rightKey) {
        g_textures[PLAYER_BODY].render_center( x, y, NULL, ang);
        bodycolor_tex->render_center( x, y, NULL, ang);
        g_textures[PLAYER_WNG_B].render_center( x, y, NULL, ang);
    } else if(leftKey && rightKey && downKey) {
        g_textures[PLAYER_BODY].render_center( x, y, NULL, ang);
        bodycolor_tex->render_center( x, y, NULL, ang);
        g_textures[PLAYER_WNG_B].render_center( x, y, NULL, ang);
    } else if((downKey && upKey) || (leftKey && rightKey)) {
        g_textures[PLAYER_BODY].render_center( x, y, NULL, ang);
        bodycolor_tex->render_center( x, y, NULL, ang);
        g_textures[PLAYER_WNG_NORM].render_center( x, y, NULL, ang);
    } else if(strafeRight && !strafeLeft) {
        g_textures[PLAYER_Tlt_R].render_center( x, y, NULL, ang);
        tltRcolor_tex->render_center( x, y, NULL, ang);
        g_textures[PLAYER_WNG_NORM].render_center( x, y, NULL, ang);
    } else if(strafeLeft && !strafeRight) {
        g_textures[PLAYER_Tlt_L].render_center( x, y, NULL, ang);
        tltLcolor_tex->render_center( x, y, NULL, ang);
        g_textures[PLAYER_WNG_NORM].render_center( x, y, NULL, ang);
    } else if(upKey && !downKey && !leftKey && !rightKey && strafeLeft && strafeRight) {
        g_textures[PLAYER_BODY].render_center( x, y, NULL, ang);
        bodycolor_tex->render_center( x, y, NULL, ang);
        g_textures[PLAYER_WNG_NORM].render_center( x, y, NULL, ang);
    } else if(!downKey && !upKey && !leftKey && !rightKey) {
        g_textures[PLAYER_BODY].render_center( x, y, NULL, ang);
        bodycolor_tex->render_center( x, y, NULL, ang);
        g_textures[PLAYER_WNG_NORM].render_center( x, y, NULL, ang);
    }
}
