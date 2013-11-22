#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include <vector>
#include "LTexture.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

const int Render_Radius = 1000;

const int targ_w = SCREEN_WIDTH + Render_Radius;
const int targ_h = SCREEN_HEIGHT + Render_Radius;

const int targ_cx = targ_w/2; //The center of the target image, which is...
const int targ_cy = targ_h/2; //...usually where the player is centered 

//the distance between the current and target position is divided by this number and...
//...stored in the appropriate accel/(vel?) var
// bigger number -> slower snap  smaller number -> faster snap
const float rotDeccel_targ = 15.0;
const float Deccel_targ = 10.0;
const float Deccel_cam = 15.0;

//must be a multiple of bg tile dimensions (currently 800x800)
//otherwise edge-wrapping will be funky
//in units of pixels? - rob
const int LEVEL_WIDTH = 32000;
const int LEVEL_HEIGHT = 32000;

static const std::string imgarr[] = {
    "media/bg_image.gif",
    "media/player/SF_Ship/ship_body.png",
    "media/player/SF_Ship/jet_forward.png",
    "media/player/SF_Ship/jet_reverse.png",
    "media/player/SF_Ship/jet_leftTurn.png",
    "media/player/SF_Ship/jet_rightTurn.png",
    "media/player/SF_Ship/wings_reverse.png",
    "media/player/SF_Ship/wings_normal.png",
    "media/player/SF_Ship/wings_forward.png",
    "media/player/SF_Ship/wings_leftTurn.png",
    "media/player/SF_Ship/wings_rightTurn.png",
    "media/player/SF_Ship/ship_body_Rtilt.png",
    "media/player/SF_Ship/ship_body_Ltilt.png",
    "media/laser1.png",
    "media/laser2.png",
    "media/laser3.png",
    "media/laser4.png",
    "media/aliens/alienship.png",
    "media/Planet_A.png",
    "media/player/Health/health15.png",
    "media/player/Health/health14.png",
    "media/player/Health/health13.png",
    "media/player/Health/health12.png",
    "media/player/Health/health11.png",
    "media/player/Health/health10.png",
    "media/player/Health/health9.png",
    "media/player/Health/health8.png",
    "media/player/Health/health7.png",
    "media/player/Health/health6.png",
    "media/player/Health/health5.png",
    "media/player/Health/health4.png",
    "media/player/Health/health3.png",
    "media/player/Health/health2.png",
    "media/player/Health/health1.png",
    "media/player/Health/health0.png",
    "media/Asteroid.png",
    "media/Mini_Asteroid.png",
    "media/Very_Mini_Asteroid.png",
    "media/explosions/explode1/ex01.png",
    "media/explosions/explode1/ex02.png",
    "media/explosions/explode1/ex03.png",
    "media/explosions/explode1/ex04.png",
    "media/explosions/explode1/ex05.png",
    "media/explosions/explode1/ex06.png",
    "media/explosions/explode1/ex07.png",
    "media/explosions/explode1/ex08.png",
    "media/explosions/explode1/ex09.png",
    "media/explosions/explode1/ex10.png",
    "media/explosions/explode1/ex11.png",
    "media/explosions/explode1/ex12.png",
    "media/explosions/explode1/ex13.png",
    "media/explosions/explode1/ex14.png",
    "media/explosions/explode1/ex15.png",
    "media/explosions/explode1/ex16.png",
    "media/explosions/explode1/ex17.png",
    "media/explosions/explode1/ex18.png",
    "media/explosions/explode1/ex19.png",
    "media/explosions/explode1/ex20.png",
    "media/explosions/explode1/ex21.png",
    "media/explosions/explode1/ex22.png",
    "media/explosions/explode1/ex23.png",
    "media/explosions/explode1/ex24.png",
    "media/explosions/explode1/ex25.png",
    "media/explosions/explode1/ex26.png",
    "media/explosions/explode1/ex27.png",
    "media/explosions/explode1/ex28.png",
    "media/explosions/explode1/ex29.png",
    "media/explosions/explode1/ex30.png",
    "media/explosions/explode1/ex31.png",
    "media/explosions/explode1/ex32.png",
    "media/explosions/explode1/ex33.png",
    "media/explosions/explode1/ex34.png",
    "media/player/SF_Ship/ship_body_t2.png",
    "media/player/SF_Ship/ship_body_Rtilt_t2.png",
    "media/player/SF_Ship/ship_body_Ltilt_t2.png",
    "media/minimap/minimap.png",
    "media/Powerup/powerup1.png"
};

// these must be in the same order as the above
enum TextureIndex { // Constants containing the index numbers of the vector of images used by the program
    BACKGROUND,    // 0
    PLAYER,      // 1
    PLAYER_THR_B,  // 2
    PLAYER_THR_F,  // etc...   // a hash would probably work instead, but this works too.
    PLAYER_THR_L,
    PLAYER_THR_R,
    PLAYER_WNG_B,
    PLAYER_WNG_NORM,
    PLAYER_WNG_F,
    PLAYER_WNG_L,
    PLAYER_WNG_R,
    PLAYER_Tlt_R,
    PLAYER_Tlt_L,
    LASER1,
    LASER2,
    LASER3,
    LASER4,
    ALIEN,
    PLANET,
    HEALTH_15,
    HEALTH_14,
    HEALTH_13,
    HEALTH_12,
    HEALTH_11,
    HEALTH_10,
    HEALTH_9,
    HEALTH_8,
    HEALTH_7,
    HEALTH_6,
    HEALTH_5,
    HEALTH_4,
    HEALTH_3,
    HEALTH_2,
    HEALTH_1,
    HEALTH_0,
    ASTEROID,
    MINI_ASTEROID,
    VERY_MINI_ASTEROID,
    EXP_0,
    EXP_1,
    EXP_2,
    EXP_3,
    EXP_4,
    EXP_5,
    EXP_6,
    EXP_7,
    EXP_8,
    EXP_9,
    EXP_10,
    EXP_11,
    EXP_12,
    EXP_13,
    EXP_14,
    EXP_15,
    EXP_16,
    EXP_17,
    EXP_18,
    EXP_19,
    EXP_20,
    EXP_21,
    EXP_22,
    EXP_23,
    EXP_24,
    EXP_25,
    EXP_26,
    EXP_27,
    EXP_28,
    EXP_29,
    EXP_30,
    EXP_31,
    EXP_32,
    EXP_33,
    PLAYER_O,
    PLAYER_O_Tlt_R,
    PLAYER_O_Tlt_L,
    MAP,
    POWERUP
};

extern std::vector<std::string> images;

extern std::vector<LTexture> textures;

class Object; // forward declaration for the following vector
extern std::vector<Object*> objects;
 
struct Circle
{
    int x, y;
    int r;
};

#endif
