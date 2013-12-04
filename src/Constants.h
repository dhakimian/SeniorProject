#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include <vector>
#include "LTexture.h"
#ifdef __APPLE__
#include <SDL2_mixer/SDL_mixer.h>
#else
#include <SDL_mixer.h>
#endif

typedef unsigned int uint;

const bool MUSIC_ON = false;
const bool SOUND_ON = false;

//Screen dimension constants
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 700;

const int Render_Radius = 1000;

const int Minimap_Radius = 2000;

const int TARG_W = SCREEN_WIDTH + Render_Radius;
const int TARG_H = SCREEN_HEIGHT + Render_Radius;

const int TARG_cX = TARG_W/2; //The center of the target image, which is...
const int TARG_cY = TARG_H/2; //...usually where the player is centered 

//the distance between the current and target position is divided by this number and...
//...stored in the appropriate accel/(vel?) var
// bigger number -> slower snap  smaller number -> faster snap
const float rotDeccel_targ = 15.0;
const float Deccel_targ = 10.0;
const float Deccel_cam = 15.0;

//speed at which objects that are overlapping move away from each other
const float Separation_vel = 0.01;

//how much the velocity of objects decays each cycle (as a percentage of current speed)
//you can think of this as the speed lost due to collisions with tiny particles of space debris
const float Speed_Decay = 0.002;

//This number is multiplied by an object's velocity(^2?) to calculate collision damage
const float Collision_Damage_multiplier = 30;

const float CVD = 5; //COLLISION_VEL_DIVIDER
const float LOSS_FACTOR = 2;

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
    "media/lasers/laser1.png",
    "media/lasers/laser2.png",
    "media/lasers/laser3.png",
    "media/lasers/laser4.png",
    "media/aliens/alienship.png",
    "media/planets/Planet_A.png",
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
    "media/asteroids/Asteroid.png",
    "media/asteroids/Mini_Asteroid.png",
    "media/asteroids/Tiny_Asteroid.png",
    "media/explosions/explosion1.png",
    "media/player/SF_Ship/ship_body_t2.png",
    "media/player/SF_Ship/ship_body_Rtilt_t2.png",
    "media/player/SF_Ship/ship_body_Ltilt_t2.png",
    "media/Powerup/powerup1.png",
    "media/minimap/minimap.png",
    "media/minimap/minimap-shipfriendly.png",
    "media/minimap/minimap-shipenemy.png",
    "media/minimap/minimap-planet.png",
    "media/minimap/minimap-asteroid.png",
    "media/minimap/minimap-asteroidmini.png",
    "media/minimap/minimap-asteroidtiny.png"

};

// these must be in the same order as the above
enum TextureIndex
{                  // Constants containing the index numbers of the vector of images used by the program
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
    TINY_ASTEROID,
    EXPLOSION,
    PLAYER_O,
    PLAYER_O_Tlt_R,
    PLAYER_O_Tlt_L,
    POWERUP,
    MAP,
    ICON_SHIP_FRIENDLY,
    ICON_SHIP_ENEMY,
    ICON_PLANET,
    ICON_ASTEROID,
    ICON_ASTEROIDMINI,
    ICON_ASTEROIDTINY

};

static const std::string sndarr[] = {
    "media/sounds/thrust.wav",
    "media/sounds/singleLaser.wav",
    "media/sounds/doubleLaser.wav",
    "media/sounds/hyperLaser.wav",
    "media/sounds/Hit.wav",
    "media/sounds/shipexplode.wav",
    "media/sounds/Powerup.wav"
};

enum SoundIndex
{
    THRUST,
    SINGLE_LASER,
    DOUBLE_LASER,
    HYPER_LASER,
    HIT,
    SHIP_EXPLODE,
    GET_POWERUP
};

extern std::vector<std::string> imgfiles;
extern std::vector<LTexture> textures;

//class Mix_Chunk; //forward declaration for the following vector
extern std::vector<std::string> sndfiles;
extern std::vector<Mix_Chunk*> sounds;

class Object; // forward declaration for the following vector
extern std::vector<Object*> objects;
 
enum ObjectType { // Constants for identifying object type, to avoid doing string compares
    T_OBJ,        // T_ stands for type_
    T_MOVOBJ,
    T_SHIP,
    T_PLAYER,
    T_ALIEN,
    T_LASER,
    T_PLANET,
    T_ASTEROID,
    T_EXPLOSION
};

struct Circle
{
    int x, y;
    int r;
};

#endif
