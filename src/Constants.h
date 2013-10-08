#ifndef _CONSTANTS_H
#define _CONSTANTS_H

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int LEVEL_WIDTH = 2400;
const int LEVEL_HEIGHT = 1600;

enum TextureIndex {
    BACKGROUND,
    PLAYER,
    PLAYER_THR_B,
    PLAYER_THR_F,
    PLAYER_THR_L,
    PLAYER_THR_R,
    PLAYER_WNG_B,
    PLAYER_WNG_NORM,
    PLAYER_WNG_F,
    PLAYER_WNG_L,
    PLAYER_WNG_R,
    PLAYER_Tlt_R,
    PLAYER_Tlt_L,
};
 
struct Circle
{
    int x, y;
    int r;
};

#endif