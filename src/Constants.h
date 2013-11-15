#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include <vector>
#include "LTexture.h"

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

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

//speed at which objects that are overlapping move away from each other
const float Separation_vel = 0.01;

//must be a multiple of bg tile dimensions (currently 800x800)
//otherwise edge-wrapping will be funky
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
    "media/Tiny_Asteroid.png"
};

// these must be in the same order as the above
enum TextureIndex { // Constants containing the index numbers of the vector of images used by the program
    BACKGROUND,    // 0
    PLAYER,        // 1
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
    LASER,
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
    TINY_ASTEROID
};

enum ObjectType { // Constants for identifying object type, to avoid doing string compares
    T_OBJ,        // T_ stands for type_
    T_MOVOBJ,
    T_SHIP,
    T_PLAYER,
    T_ALIEN,
    T_LASER,
    T_PLANET,
    T_ASTEROID
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
