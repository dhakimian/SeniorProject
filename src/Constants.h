#ifndef _CONSTANTS_H
#define _CONSTANTS_H

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int LEVEL_WIDTH = 2400;
const int LEVEL_HEIGHT = 1600;

enum TextureIndex {
    BACKGROUND,
    SHIP,
    THR_B,
    THR_L,
    THR_R,
    THR_F,
};
 
struct Circle
{
    int x, y;
    int r;
};

#endif
