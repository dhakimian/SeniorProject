#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include <vector>
#include "LTexture.h"

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const int Render_Radius = 800;

const int LEVEL_WIDTH = 3200;
const int LEVEL_HEIGHT = 3200;

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
    "media/aliens/alienship.png",
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
    "media/player/Health/health0.png"
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
    ALIEN,
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
    HEALTH_0
};

extern std::vector<std::string> images;// (imgarr, imgarr + sizeof(imgarr) / sizeof(imgarr[0]) );

extern std::vector<LTexture> textures;// (images.size());
 
struct Circle
{
    int x, y;
    int r;
};

#endif
