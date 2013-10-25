#ifndef _CONSTANTS_H
#define _CONSTANTS_H

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int Render_Radius = 800;

const int LEVEL_WIDTH = 2400;
const int LEVEL_HEIGHT = 1600;

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
 
struct Circle
{
    int x, y;
    int r;
};

#endif
