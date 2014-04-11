#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include <vector>
#include "LTexture.h"
#ifdef __clang__
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_net/SDL_net.h>
#else
#include <SDL_mixer.h>
#include <SDL_net.h>
#endif

typedef unsigned int uint;

const bool MUSIC_ON = false;
const bool SOUND_ON = false;

//Screen dimension constants
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 700;

const int Render_Radius = 1000;

// Should be <= min(LEVEL_WIDTH, LEVEL_HEIGHT)/2, or things will jump around
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

//speed at which g_objects that are overlapping move away from each other
const float Separation_vel = 0.01;

//how much the velocity of g_objects decays each cycle (as a percentage of current speed)
//you can think of this as the speed lost due to collisions with tiny particles of space debris
const float Speed_Decay = 0.0005;

//This number is multiplied by an object's velocity to calculate collision damage
const float Collision_Damage_multiplier = 30;

const float LOSS_FACTOR = 2;

//Maximum number of objects (and consquently packets)
const int MAX_OBJECTS = 512;

//how many consecutive updates need to be missed on the client before it considers the connection to the server lost
const int SERVER_CONNECTION_LOST_THRESHOLD = 50;

//how many consecutive updates from a client the server needs to miss before considering its connection to that client lost
const int CLIENT_CONNECTION_LOST_THRESHOLD = 20;

//must be a multiple of bg tile dimensions (currently 800x800)
//otherwise edge-wrapping will be funky
const int LEVEL_WIDTH = 4000;
const int LEVEL_HEIGHT = 4000;
//const int LEVEL_WIDTH = 32000;
//const int LEVEL_HEIGHT = 32000;

static const std::string imgarr[] = {
    "media/bg_image.gif",
    "media/player/SF_Ship/ship_body.png",
    "media/player/SF_Ship/ship_body_color.png",
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
    "media/player/SF_Ship/ship_body_Rtilt_color.png",
    "media/player/SF_Ship/ship_body_Ltilt.png",
    "media/player/SF_Ship/ship_body_Ltilt_color.png",
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
    "media/Powerup/powerup1.png",
    "media/minimap/minimap.png",
    "media/minimap/minimap-shipyou.png",
    "media/minimap/minimap-shipfriendly.png",
    "media/minimap/minimap-shipenemy.png",
    "media/minimap/minimap-planet.png",
    "media/minimap/minimap-asteroid.png",
    "media/minimap/minimap-asteroidmini.png",
    "media/minimap/minimap-asteroidtiny.png"

};

// these must be in the same order as the above
enum TextureIndex {     // Constants containing the index numbers of the vector of images used by the program
    BACKGROUND,         // 0
    PLAYER_BODY,        // 1
    PLAYER_BODY_COLOR,  // 2
    PLAYER_THR_B,       // 3
    PLAYER_THR_F,       // etc...   // a hash would probably work instead, but this works too.
    PLAYER_THR_L,
    PLAYER_THR_R,
    PLAYER_WNG_B,
    PLAYER_WNG_NORM,
    PLAYER_WNG_F,
    PLAYER_WNG_L,
    PLAYER_WNG_R,
    PLAYER_Tlt_R,
    PLAYER_Tlt_R_COLOR,
    PLAYER_Tlt_L,
    PLAYER_Tlt_L_COLOR,
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
    POWERUP,
    MAP,
    ICON_SHIP_YOU,
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

enum SoundIndex {
    THRUST,
    SINGLE_LASER,
    DOUBLE_LASER,
    HYPER_LASER,
    HIT,
    SHIP_EXPLODE,
    GET_POWERUP
};

struct RGB {
    int r, g, b;
    RGB(int r, int g, int b) {
        this->r=r;
        this->g=g;
        this->b=b;
    }
};

static const RGB TeamColors[] = {
    RGB(0, 0, 255),   //blue
    RGB(255, 155, 0), //orange
    RGB(255, 0, 255), //purple
    RGB(0, 255, 0)    //green
};

extern std::vector<std::string> g_imgfiles;
extern std::vector<LTexture> g_textures;

//class Mix_Chunk; //forward declaration for the following vector
extern std::vector<std::string> g_sndfiles;
extern std::vector<Mix_Chunk*> g_sounds;

class Object; // forward declaration for the following vector
extern std::vector<Object*> g_objects;

enum ObjectType { // Constants for identifying object type, to avoid doing string compares
    T_OBJ,        // T_ stands for type_
    T_MOVOBJ,
    T_SHIP,
    T_PLAYER,
    T_ALIEN,
    T_LASER,
    T_PLANET,
    T_ASTEROID,
    T_EXPLOSION,
    T_POWERUP
};

struct Circle
{
    int x, y;
    int r;
};

struct Keystate
{
    bool upKey, downKey, leftKey, rightKey, strafeLeft, strafeRight, shootKey;
    Keystate() {
        upKey = downKey = leftKey = rightKey = strafeLeft = strafeRight = shootKey = false;
    }
};

struct Connection
{
    IPaddress address;
    int packets_recvd, prev_packets_recvd, consec_missed, packets_sent;
    float server_fps;

    Connection( IPaddress addr, int pr, int ppr=0, int cm=0, int ps=0 ) {
        address = addr;
        packets_recvd = pr;
        prev_packets_recvd = ppr;
        consec_missed = cm;
        packets_sent = ps;
        server_fps = -1;
    }

};

// http://stackoverflow.com/questions/589985/vectors-structs-and-stdfind
struct find_addr : std::unary_function<Connection, bool> {
    IPaddress addr;
    find_addr(IPaddress addr):addr(addr) { }
    bool operator()(Connection const& c) const {
        return (c.address.host == addr.host && c.address.port == addr.port );
    }
};

struct find_port : std::unary_function<Connection, bool> {
    IPaddress addr;
    find_port(IPaddress addr):addr(addr) { }
    bool operator()(Connection const& c) const {
        return ( c.address.port == addr.port );
    }
};

#endif
