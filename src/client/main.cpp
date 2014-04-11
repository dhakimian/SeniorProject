/**
 *      CS-195   Spring 2014
 *        Senior Project
 *     *** Spaceship Game ***
 *
 *        Group Members:
 *     Daniel Hakimian (head)
 *     Matt Johnston (helper)
 *     Tim Swanson (helper)
 */

#ifdef __clang__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_net/SDL_net.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_net.h>
#endif

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <unistd.h>

#include "Constants.h"
#include "Util.h"
#include "LTexture.h"
#include "LTimer.h"
#include "Player.h"
#include "Alien.h"
#include "Planet.h"
#include "Laser.h"
#include "Asteroid.h"
#include "Explosion.h"
#include "Powerup.h"

using namespace std;

//int sleep_time = ;

bool g_show_minimap = true;

//Whether client should update g_objects locally whenever it doesn't receive a new gamestate from server
const bool g_LocalUpdates = false;
//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
TTF_Font* gFont = NULL;

//The texture that everything adjacent will be rendered to before being rotated relative to the ship
LTexture gTargetTexture;

//The texture that the minimap is rendered to before being rotated relative to the ship
LTexture gMinimap;

//The angle at which the target texture is rendered
float g_Angle_targ = 30.0;

//The velocity at which that angle changes
float g_rotVel_targ = 0.0;

//these (similar to the above) deal with motion/position of the target texture
float g_xOffset_targ = 2;
float g_yOffset_targ = 2;
float g_xVel_targ = 0.0;
float g_yVel_targ = 0.0;

//these deal with motion/position of the contents of the target texture
float g_xPos_cam = SCREEN_WIDTH/2;
float g_yPos_cam = SCREEN_HEIGHT/2;
float g_xVel_cam = 0.0;
float g_yVel_cam = 0.0;

//this is where the camera is centered on, or where it will be centered on after it finishes snapping
//(Pos_cam is the camera's current position, Pos_camdest is the destination of the camera)
float g_xPos_camdest = SCREEN_WIDTH/2;
float g_yPos_camdest = SCREEN_HEIGHT/2;
float g_Angle_camdest = 0.0;

//boolean config options
bool g_targ_Follow_Rotation = true;
bool g_targ_Ship_Centered = false;

vector<string> g_imgfiles (imgarr, imgarr + sizeof(imgarr) / sizeof(imgarr[0]) );
vector<LTexture> g_textures (g_imgfiles.size());

vector<string> g_sndfiles (sndarr, sndarr + sizeof(sndarr) / sizeof(sndarr[0]) );
vector<Mix_Chunk*> g_sounds (g_sndfiles.size(), NULL );

vector<Object*> g_objects; // list of all the objects currently in the level
vector<const void*> g_ObjectIDs; // list of identifiers for objects. Must be in same order as g_objects

Player* g_player = NULL;

Mix_Music* g_music = NULL;

TTF_Font* g_font = NULL;
SDL_Color g_font_color = { 255, 0, 0, 255 };
LTexture g_fps_text;
stringstream g_ss_fps;
float g_fps;

UDPsocket g_sd;       /* Socket descriptor */
IPaddress srvadd;

bool init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Enable VSync
        if( !SDL_SetHint( SDL_HINT_RENDER_VSYNC, "1" ) ) {
            printf( "Warning: VSync not enabled!" );
        }

        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        //gWindow = SDL_CreateWindow( "Spaceship Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        gWindow = SDL_CreateWindow( "Spaceship Game", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        //gWindow = SDL_CreateWindow( "Spaceship Game", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL ) {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL ) {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }

                //Initialize SDL_ttf
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }
            }
        }

        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
            printf( "SDL could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

        /* Initialize SDL_net */
        if (SDLNet_Init() < 0) {
            fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
            exit(EXIT_FAILURE);
        }

    }

    return success;
}

/*
bool init_net() {
    // Open a socket
    if (!(g_sd = SDLNet_UDP_Open(0)))
    {
        fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }

    // Resolve server name
    if (SDLNet_ResolveHost(&srvadd, argv[1], atoi(argv[2])) == -1)
    {
        fprintf(stderr, "SDLNet_ResolveHost(%s %d): %s\n", argv[1], atoi(argv[2]), SDLNet_GetError());
        exit(EXIT_FAILURE);
    }
}
*/

bool loadMedia() {
    //Loading success flag
    bool success = true;

    //load textures
    for( uint i=0; i<g_imgfiles.size(); i++ )
    {
        g_textures[i].setRenderer(gRenderer);
        if( !g_textures[i].loadFromFile( g_imgfiles[i] ) ) {
            cout << "Failed to load '" << g_imgfiles[i] << "'!" << endl;
            success = false;
        }
    }

    //load sounds
    if( SOUND_ON ) {
        for( uint i=0; i<g_sounds.size(); i++ )
        {
            g_sounds[i] = Mix_LoadWAV( g_sndfiles[i].c_str() );
            if( g_sounds[i] == NULL ) {
                cout << "Failed to load '" << g_sndfiles[i] << "'!" << endl;
                success = false;
            }
        }
    }

    //Load texture target
    gTargetTexture.setRenderer(gRenderer);
    if( !gTargetTexture.createBlank( TARG_W, TARG_H, SDL_TEXTUREACCESS_TARGET ) ) {
        printf( "Failed to create main target texture!\n" );
        success = false;
    }

    //Load minimap target tex
    gMinimap.setRenderer(gRenderer);
    if( !gMinimap.createBlank( g_textures[MAP].getWidth(), g_textures[MAP].getHeight(), SDL_TEXTUREACCESS_TARGET ) ) {
        printf( "Failed to create minimap target texture!\n" );
        success = false;
    }
    else {
        //Set standard alpha blending
        gMinimap.setBlendMode( SDL_BLENDMODE_BLEND );
    }

    //load music
    if( MUSIC_ON ) {
        g_music = Mix_LoadMUS( "media/sounds/Amb.mp3" );
        if( g_music == NULL )
        {
            printf( "Failed to load game music! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }
    }

    gFont = TTF_OpenFont( "media/fonts/courier_new.ttf", 14 );
    if( gFont == NULL )
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        g_fps_text.setRenderer(gRenderer);
        g_fps_text.setFont(gFont);
    }


    return success;
}

void loadObjects() { //load initial map objects
}

void render_bg() {
    //render the background tiles that are within a certain radius of the camera, and also...
    //...render tiles on the other side of a wrap to replace the void
    int tile_w = g_textures[BACKGROUND].getWidth();
    int tile_h = g_textures[BACKGROUND].getHeight();
    for( int i=0; i<LEVEL_WIDTH; i+= tile_w ) {
        for( int j=0; j<LEVEL_HEIGHT; j+=tile_h ) {
            bool render = false;
            int xrc = i+TARG_cX-g_xPos_cam; // X render coordinate
            int yrc = j+TARG_cY-g_yPos_cam; // Y render coordinate

            int tilePos_x = i + tile_w/2;
            int tilePos_y = j + tile_h/2;

            // only render if within a certain radius
            if( fabs(tilePos_x - g_xPos_cam) < Render_Radius && fabs(tilePos_y - g_yPos_cam) < Render_Radius )
                render = true;
            else { //image is not close enough, so don't render, but first...
                //...check if the image would be close enough if the map literally wrapped, so...
                //...we can render tiles from the other side of an edge-wrap to eliminate the void
                if( fabs(tilePos_x + LEVEL_WIDTH - g_xPos_cam) < Render_Radius ) {//r
                    xrc += LEVEL_WIDTH; render = true;}
                if( fabs(tilePos_y + LEVEL_HEIGHT - g_yPos_cam) < Render_Radius ) {//b
                    yrc += LEVEL_HEIGHT; render = true;}
                if( fabs(tilePos_x - LEVEL_WIDTH - g_xPos_cam) < Render_Radius ) {//l
                    xrc -= LEVEL_WIDTH; render = true;}
                if( fabs(tilePos_y - LEVEL_HEIGHT - g_yPos_cam) < Render_Radius ) {//t
                    yrc -= LEVEL_HEIGHT; render = true;}
            }
            if( render )
                g_textures[BACKGROUND].render( xrc, yrc );
            //else they are not close enough, so don't render them.
        }
    }
}

void render_objects() {
    //loop through the list of currently present g_objects to render them
    for( uint i=0; i<g_objects.size(); i++ )
    //for( int i=g_objects.size()-1; i>=0; i-- )
    {
        float xPos, yPos, Angle;
        g_objects[i]->get_values(&xPos, &yPos, &Angle);
        //cout<<i<<": "<<xPos<<", "<<yPos<<", "<<Angle<<endl;
        //int tex_index = g_objects[i]->get_tex_index();

        bool render = false;

        int xrc = xPos+TARG_cX-g_xPos_cam; // X render coordinate
        int yrc = yPos+TARG_cY-g_yPos_cam; // Y render coordinate

        // only render if within a certain radius
        //if( fabs( xPos - g_xPos_cam ) < Render_Radius && fabs( yPos - g_yPos_cam ) < Render_Radius )
        if( distanceSquared(xPos, yPos, g_xPos_cam, g_yPos_cam) < Render_Radius*Render_Radius )
            render = true;
        else {//object is not close enough, so don't render, but first...
            //...check if the object would be close enough if the map literally wrapped, so we can...
            //...render g_objects from the other side of an edge-wrap so they don't disapper near edges
            if( fabs( xPos + LEVEL_WIDTH - g_xPos_cam ) < Render_Radius ) {//r
                xrc += LEVEL_WIDTH; render = true;}
            if( fabs( yPos + LEVEL_HEIGHT - g_yPos_cam ) < Render_Radius ) {//b
                yrc += LEVEL_HEIGHT; render = true;}
            if( fabs( xPos - LEVEL_WIDTH - g_xPos_cam ) < Render_Radius ) {//l
                xrc -= LEVEL_WIDTH; render = true;}
            if( fabs( yPos - LEVEL_HEIGHT - g_yPos_cam ) < Render_Radius ) {//t
                yrc -= LEVEL_HEIGHT; render = true;}
        }
        if( render )
            g_objects[i]->render(xrc, yrc, Angle, true);
        //else they are not close enough, so don't render them.
    }
}

void render_healthbar() {
    //this code is the health bar
    float xp, yp;
    xp = (SCREEN_WIDTH / 2) - 151;
    yp = 1;
    //code for drawing the right ammount of health increments depending on palyers health
    int player_health = g_player->get_hitpoints();
    if(player_health > 935)
        g_textures[HEALTH_15].render(xp, yp);
    else if(player_health > 870)
        g_textures[HEALTH_14].render(xp, yp);
    else if(player_health > 805)
        g_textures[HEALTH_13].render(xp, yp);
    else if(player_health > 740)
        g_textures[HEALTH_12].render(xp, yp);
    else if(player_health > 675)
        g_textures[HEALTH_11].render(xp, yp);
    else if(player_health > 610)
        g_textures[HEALTH_10].render(xp, yp);
    else if(player_health > 545)
        g_textures[HEALTH_9].render(xp, yp);
    else if(player_health > 480)
        g_textures[HEALTH_8].render(xp, yp);
    else if(player_health > 415)
        g_textures[HEALTH_7].render(xp, yp);
    else if(player_health > 350)
        g_textures[HEALTH_6].render(xp, yp);
    else if(player_health > 285)
        g_textures[HEALTH_5].render(xp, yp);
    else if(player_health > 220)
        g_textures[HEALTH_4].render(xp, yp);
    else if(player_health > 155)
        g_textures[HEALTH_3].render(xp, yp);
    else if(player_health > 90)
        g_textures[HEALTH_2].render(xp, yp);
    else if(player_health > 25)
        g_textures[HEALTH_1].render(xp, yp);
    else
        g_textures[HEALTH_0].render(xp, yp);

}

void render_minimap() {
    gMinimap.setAsRenderTarget();
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
    SDL_RenderClear( gRenderer );

    g_textures[MAP].render(0, 0);
    //if a directional tracking system is implemented, we can modify the MAP texture to have a
    //pointer of some sort on it, and rotate it here before rendering to it, so that the minimap
    //can also act as a compass that points to our target

    for( uint i=0; i<g_objects.size(); i++ )
    {
        float xPos, yPos, Angle;
        g_objects[i]->get_values(&xPos, &yPos, &Angle);

        int xrc = xPos-g_xPos_cam;
        int yrc = yPos-g_yPos_cam;

        //edgewrapping stuff
        if( fabs( xPos + LEVEL_WIDTH - g_xPos_cam ) < Minimap_Radius ) //r
            xrc += LEVEL_WIDTH;
        if( fabs( yPos + LEVEL_HEIGHT - g_yPos_cam ) < Minimap_Radius ) //b
            yrc += LEVEL_HEIGHT;
        if( fabs( xPos - LEVEL_WIDTH - g_xPos_cam ) < Minimap_Radius ) //l
            xrc -= LEVEL_WIDTH;
        if( fabs( yPos - LEVEL_HEIGHT - g_yPos_cam ) < Minimap_Radius ) //t
            yrc -= LEVEL_HEIGHT;

        if( fabs(distanceSquared(xrc+g_xPos_cam, yrc+g_yPos_cam, g_xPos_cam, g_yPos_cam))
                < Minimap_Radius*Minimap_Radius ) {
            xrc *= ( ( (float)g_textures[MAP].getWidth()/2 ) / (Minimap_Radius) ); //scale down the coords
            yrc *= ( ( (float)g_textures[MAP].getHeight()/2 ) / (Minimap_Radius) ); //to fit on the minimap

            xrc += g_textures[MAP].getWidth()/2;  //shift the coords so that they are centered on
            yrc += g_textures[MAP].getHeight()/2; //the center of the minimap, not 0,0

            if( g_objects[i]->get_type() == T_PLAYER ) {
                if( g_objects[i] == g_player )
                    g_textures[ICON_SHIP_YOU].render_center(xrc, yrc, NULL, Angle);
                else if( g_player->get_team() == g_objects[i]->get_team()
                        && g_player->get_team() >= 0 )
                    g_textures[ICON_SHIP_FRIENDLY].render_center(xrc, yrc, NULL, Angle);
                else
                    g_textures[ICON_SHIP_ENEMY].render_center(xrc, yrc, NULL, Angle);
            }
            else if( g_objects[i]->get_type() == T_PLANET )
                g_textures[ICON_PLANET].render_center(xrc, yrc, NULL, Angle);
            else if( g_objects[i]->get_type() == T_ALIEN )
                g_textures[ICON_SHIP_ENEMY].render_center(xrc, yrc, NULL, Angle);
            else if( g_objects[i]->get_type() == T_ASTEROID ) {
                Asteroid* ast = (Asteroid*) g_objects[i];
                if( ast->get_size() == 1 )
                    g_textures[ICON_ASTEROID].render_center(xrc, yrc, NULL, Angle);
                else if( ast->get_size() == 2 )
                    g_textures[ICON_ASTEROIDMINI].render_center(xrc, yrc, NULL, Angle);
                else if( ast->get_size() == 3 )
                    g_textures[ICON_ASTEROIDTINY].render_center(xrc, yrc, NULL, Angle);
                //tiny asteroid are too small to be picked up on long range sensors?
            }
        }
    }

    //Reset render target to the window
    SDL_SetRenderTarget( gRenderer, NULL );

    gMinimap.render( 5, 5, NULL, -g_Angle_targ );
}

void render_fps() {
    if( !g_fps_text.loadFromRenderedText( g_ss_fps.str().c_str(), g_font_color ) ) {
        printf( "Unable to render FPS texture!\n" );
    }
    g_fps_text.render( ( SCREEN_WIDTH - 110 ), 10 );
}

void render_overlay() {
    if( g_player != NULL )
    {
        render_healthbar();
        if( g_show_minimap )
            render_minimap();
    }
    render_fps();
}

void render() {
    //set the image as the render target
    gTargetTexture.setAsRenderTarget();
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
    SDL_RenderClear( gRenderer );

    float xPos_pl, yPos_pl, Angle_pl, xVel_pl, yVel_pl, rotVel_pl; // pl -> player
    if( g_player != NULL )
        g_player->get_values(&xPos_pl, &yPos_pl, &Angle_pl, &xVel_pl, &yVel_pl, &rotVel_pl);

    if( g_player != NULL ) {
        g_xPos_camdest = xPos_pl;
        g_yPos_camdest = yPos_pl;
        if( g_targ_Follow_Rotation )
            g_Angle_camdest = Angle_pl;
    }

    render_bg();

    render_objects();

    //Reset render target to the window
    SDL_SetRenderTarget( gRenderer, NULL );

    float diff_ang;
    //if( g_targ_Follow_Rotation )
        diff_ang = g_Angle_camdest - g_Angle_targ;
    //else
        //diff_ang = 0 - g_Angle_targ;

    if( diff_ang < -180 )
        diff_ang += 360;
    if( diff_ang >= 180 )
        diff_ang -= 360;

    g_rotVel_targ = diff_ang/rotDeccel_targ;
    if( g_targ_Follow_Rotation && g_player != NULL )
            g_rotVel_targ += rotVel_pl;

    g_Angle_targ = fmod( (g_Angle_targ + g_rotVel_targ + 360), 360 );

    int x_offset_dest, y_offset_dest;
    //1.5->top or left
    //2->middle
    //3->bottom or right
    x_offset_dest = 2;

    if( g_targ_Ship_Centered )
    //if( g_Follow_Ship && g_targ_Ship_Centered )
        y_offset_dest = 2;
    else
        y_offset_dest = 3;

    float diff_x = x_offset_dest - g_xOffset_targ;
    float diff_y = y_offset_dest - g_yOffset_targ;

    g_xVel_targ = diff_x/Deccel_targ;
    g_yVel_targ = diff_y/Deccel_targ;

    g_xOffset_targ += g_xVel_targ;
    g_yOffset_targ += g_yVel_targ;

    ///--///
    gTargetTexture.render( -(Render_Radius/g_xOffset_targ), -(Render_Radius/g_yOffset_targ), NULL, -g_Angle_targ );
    ///--///

    diff_x = g_xPos_camdest - g_xPos_cam;
    diff_y = g_yPos_camdest - g_yPos_cam;

    if( diff_x < -LEVEL_WIDTH/2 )
        diff_x += LEVEL_WIDTH;
    if( diff_y < -LEVEL_HEIGHT/2 )
        diff_y += LEVEL_HEIGHT;
    if( diff_x >= LEVEL_WIDTH/2 )
        diff_x -= LEVEL_WIDTH;
    if( diff_y >= LEVEL_HEIGHT/2 )
        diff_y -= LEVEL_HEIGHT;

    g_xVel_cam = xVel_pl + diff_x/Deccel_cam;
    g_yVel_cam = yVel_pl + diff_y/Deccel_cam;

    g_xPos_cam = fmod( (g_xPos_cam + g_xVel_cam + LEVEL_WIDTH), LEVEL_WIDTH );
    g_yPos_cam = fmod( (g_yPos_cam + g_yVel_cam + LEVEL_HEIGHT), LEVEL_HEIGHT );

    render_overlay();
}

Keystate get_keystate(const Uint8* currentKeyStates) {
    Keystate keystate;

    keystate.upKey = currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_W];
    keystate.downKey = currentKeyStates[SDL_SCANCODE_DOWN] || currentKeyStates[SDL_SCANCODE_S];
    keystate.leftKey = currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_A];
    keystate.rightKey = currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_D];
    keystate.strafeLeft = currentKeyStates[SDL_SCANCODE_Q];
    keystate.strafeRight = currentKeyStates[SDL_SCANCODE_E];
    keystate.shootKey = currentKeyStates[SDL_SCANCODE_SPACE];

    return keystate;
}

template <typename T>
void CopyObject( UDPpacket* p ) {
  //Either makes a new local object or updates the local object from the data in the packet
    T foo;
    memcpy( &foo, p->data, p->len );
    vector<const void*>::iterator it = find( g_ObjectIDs.begin(), g_ObjectIDs.end(), foo.get_ID() );

    if( it == g_ObjectIDs.end() ) //new object
    {
        g_ObjectIDs.push_back( foo.get_ID() );
        g_objects.push_back( foo.clone() );
        assert( g_ObjectIDs.size() == g_objects.size() );
    }
    else // object has been previously received: update it
    {
        *g_objects[it-g_ObjectIDs.begin()] = foo;
    }

}

void close() {
    //Free loaded images
    for( uint i=0; i<g_textures.size(); i++ )
    {
        g_textures[i].free();
    }

    //Free global font
    TTF_CloseFont( gFont );
    gFont = NULL;

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}


int main( int argc, char** argv ) {
    //Start up SDL and create window
    if( !init() ) {
        printf( "Failed to initialize!\n" );
    }
    else {
        /* Initialize SDL_net */
        if (SDLNet_Init() < 0) {
            fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
            exit(EXIT_FAILURE);
        }

        char* host = (char*)"localhost";
        int port = 2000;

        if (argc == 3) {
            host = argv[1];
            port = atoi(argv[2]);
        }
        else if (argc == 2) {
            host = argv[1];
        }

        /* Resolve server name  */
        if (SDLNet_ResolveHost(&srvadd, host, port) == -1) {
            fprintf(stderr, "SDLNet_ResolveHost(%s %d): %s\n", host, port, SDLNet_GetError());
            exit(EXIT_FAILURE);
        }

        // Open a socket on a random port
        if (!(g_sd = SDLNet_UDP_Open(0))) {
            fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
            exit(EXIT_FAILURE);
        }

        Uint16 myport;

        IPaddress *address;
        address=SDLNet_UDP_GetPeerAddress(g_sd, -1);
        if(!address) {
            fprintf(stderr, "SDLNet_UDP_GetPeerAddress: %s\n", SDLNet_GetError());
        }
        else {
            myport = address->port;
            cout<<"Opened socket on port "<<myport<<endl;
        }


        if( !loadMedia() ) { //Load media
            printf( "Failed to load media!\n" );
        }
        else {
            //Main loop flag
            bool quit = false;

            int cycle = 0;

            LTimer fps_timer;
            fps_timer.start();

            bool connected = false;

            //count consecutive local updates to determine whether connection has been lost
            int consec_missed_updates = 0;

            int prev_num_recvd = 0;

            //Event handler
            SDL_Event e;

            //loadObjects();

            if( MUSIC_ON )
                Mix_PlayMusic(g_music, -1);

            srand( time(NULL) ); // seed the random number generator with the current time

            //While application is running
            while( !quit ) {
                const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

                if( !connected && cycle%100 == 0 ) //only scan for server every 100 cycles
                {
                    printf("Looking for server at %s (port %d)...\n", host, port);
                    UDPpacket *p;
                    if (!(p = SDLNet_AllocPacket(128)))
                    {
                        fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
                        exit(EXIT_FAILURE);
                    }
                    p->address.host = srvadd.host;  /* Set the destination host */
                    p->address.port = srvadd.port;  /* And destination port */
                    Keystate keystate = get_keystate( currentKeyStates );
                    memcpy( p->data, &keystate, sizeof(keystate) );
                    p->len = sizeof(keystate);
                    SDLNet_UDP_Send(g_sd, -1, p);
                    SDLNet_FreePacket(p);
                }

                if( connected ) {
                    UDPpacket *kp;
                    if (!(kp = SDLNet_AllocPacket(128)))
                    {
                        fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
                        exit(EXIT_FAILURE);
                    }
                    kp->address.host = srvadd.host;  /* Set the destination host */
                    kp->address.port = srvadd.port;  /* And destination port */
                    Keystate keystate = get_keystate( currentKeyStates );
                    memcpy( kp->data, &keystate, sizeof(keystate) );
                    kp->len = sizeof(keystate);
                    SDLNet_UDP_Send(g_sd, -1, kp);
                    SDLNet_FreePacket(kp);
                }

                //get gamestate
                UDPpacket** p_in;
                if (!(p_in = SDLNet_AllocPacketV(MAX_OBJECTS, MAX_OBJECTS * 16))) {
                    fprintf(stderr, "SDLNet_AllocPacketV: %s\n", SDLNet_GetError());
                    exit(EXIT_FAILURE);
                }

                /* Wait a packet. UDP_Recv returns != 0 if a packet is coming */
                //cout<<"udpRecvV->"<<endl;
                int num_recvd = SDLNet_UDP_RecvV(g_sd, p_in);
                //cout<<"num_recvd: "<<num_recvd<<endl;
                if (num_recvd > 0) {
                    if( !connected ) {
                        connected = true;
                        cycle = 0;
                        fps_timer.start();
                        g_objects.clear();
                        g_ObjectIDs.clear();
                        g_player = NULL;
                        printf("Connected to server at %s (port %d)!\n", host, port);
                    }

                    //if( num_recvd == prev_num_recvd * 2 )
                        //num_recvd /= 2;

                    consec_missed_updates = 0;

                    //cout<<"got packet vector"<<endl;
                    //cout<<"num_recvd: "<<num_recvd<<endl;
                    //g_objects.resize( num_recvd );
                    for( int i=0; i<num_recvd; i++ ) {
                        //Object tmp = *(Object*)p_in[i]->data;
                        Object tmp;
                        memcpy( &tmp, p_in[i]->data, p_in[i]->len );
                        //memcpy( &tmp, p_in[i]->data, sizeof(tmp) );
                        //cout<<"tmpmemcpy"<<endl;
                        //Object* tmp = (Object*)p_in[i]->data;
                        //cout<<i<<" type: "<<tmp.get_type()<<endl;

                        if( tmp.get_type() == 0)
                            CopyObject<Object>( p_in[i] );
                        else if( tmp.get_type() == 1 )
                            CopyObject<MovingObject>( p_in[i] );
                        else if( tmp.get_type() == 2 )
                            CopyObject<Ship>( p_in[i] );
                        else if( tmp.get_type() == 3 )
                            CopyObject<Player>( p_in[i] );
                        else if( tmp.get_type() == 4 )
                            CopyObject<Alien>( p_in[i] );
                        else if( tmp.get_type() == 5 )
                            CopyObject<Laser>( p_in[i] );
                        else if( tmp.get_type() == 6 )
                            CopyObject<Planet>( p_in[i] );
                        else if( tmp.get_type() == 7 )
                            CopyObject<Asteroid>( p_in[i] );
                        else if( tmp.get_type() == 8 )
                            CopyObject<Explosion>( p_in[i] );
                        else if( tmp.get_type() == 9 )
                            CopyObject<Powerup>( p_in[i] );

                    }

                    /* --- find Player --- */
                    if( g_player == NULL || g_player->is_dead() ) {
                        for( uint i=0; i<g_objects.size(); i++ )
                        {
                            if( g_objects[i]->get_type() == T_PLAYER ) {
                                //Player* player = new Player(*g_objects[i]);
                                g_player = (Player*)g_objects[i];
                                //g_player = g_objects[i]->clone();
                                //cout<<player->get_controller()<<endl;
                                //cout<<myport<<endl;
                                if( g_player->get_controller() == myport )
                                    break;
                            }
                            g_player = NULL; //if here, none of objects were matching player objects
                        }
                    }

                    //check for dead local objects and get rid of them
                    for( uint i = 0; i<g_objects.size(); i++ )
                    {
                        if( g_objects[i]->is_dead() ) {
                            if( !g_objects[i]->is_persistent() )
                                delete g_objects[i];
                            g_objects.erase( g_objects.begin()+i );
                            g_ObjectIDs.erase( g_ObjectIDs.begin()+i );
                            assert( g_ObjectIDs.size() == g_objects.size() );
                            i--;
                        }
                    }
                    //if( g_player != NULL && g_player->is_dead() )
                        //delete g_player;
                        //g_player = NULL;

                    prev_num_recvd = num_recvd;

                    SDLNet_FreePacketV(p_in);

                }
                else { // no gamestate was received
                    consec_missed_updates++;
                    if( connected && consec_missed_updates >= SERVER_CONNECTION_LOST_THRESHOLD ) {
                        cout<<"Connection to server lost. (missed "<<SERVER_CONNECTION_LOST_THRESHOLD
                            <<" consecutive updates)"<<endl;
                        connected = false;
                    }

                    if( g_LocalUpdates && g_player != NULL ) {
                        //Update objects locally based on current state.
                        //Changes will be overwritten by next received state.
                        if( connected )
                            cout<<"local update"<<endl;

                        //auto size = g_objects.size();
                        for( uint i = 0; i<g_objects.size(); i++ )
                        {
                            if( g_objects[i]->is_dead() ) {
                                if( !g_objects[i]->is_persistent() )
                                    delete g_objects[i];
                                g_objects.erase( g_objects.begin()+i );
                                g_ObjectIDs.erase( g_ObjectIDs.begin()+i );
                                assert( g_ObjectIDs.size() == g_objects.size() );
                                i--;
                            } else
                                g_objects[i]->update();
                        }
                    }
                }

                //cout<<"g_objects.size(): "<<g_objects.size()<<endl;

                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 ) {
                    //User requests quit
                    if( e.type == SDL_QUIT ) {
                        quit = true;
                    }
                    if( e.type == SDL_KEYDOWN ) {
                        switch( e.key.keysym.sym ) {
                            case SDLK_F11:
                                toggle_fullscreen(gWindow);
                                break;
                            case SDLK_ESCAPE:
                                quit = true;
                                break;
                                //print current ship coords for debugging
                            case SDLK_TAB:
                                g_show_minimap = !g_show_minimap;
                                break;
                            case SDLK_x:
                                float xPos, yPos, Angle, xVel, yVel, rotVel; 
                                g_player->get_values(&xPos, &yPos, &Angle, &xVel, &yVel, &rotVel);
                                cout << "x: " << xPos << " | y: " << yPos << endl;
                                cout << "xv: " << xVel << " | yv: " << yVel << endl;
                                cout << "vel: "<<sqrt( xVel*xVel + yVel*yVel )<<endl;
                                break;
                            case SDLK_h:
                                cout<<g_player->get_hitpoints()<<" HP"<<endl;
                                break;
                            case SDLK_c: //toggle camera mode
                                g_targ_Follow_Rotation = !g_targ_Follow_Rotation;
                                g_targ_Ship_Centered = !g_targ_Ship_Centered;
                                break;
                                //switch control between present Player ships
                                //case SDLK_p:
                                //cycle_player();
                                //break;
                                //case SDLK_8:
                                //SOUND_ON = !SOUND_ON;
                                //break;
                            case SDLK_9:
                                Mix_PlayMusic( g_music, -1);
                                break;
                            case SDLK_0:
                                Mix_PauseMusic();
                                break;
                        }
                    }
                }

                //Calculate and correct fps
                g_fps = cycle / ( fps_timer.getTicks() / 1000.f );
                if( g_fps > 2000000 )
                    g_fps = 0;

                //Set text to be rendered
                g_ss_fps.str( "" );
                g_ss_fps << "FPS: " << g_fps;

                //cout << g_fps << endl;

                //handle keyboard state for things like rendering ship correctly based on keys pressed
                //if( g_player != NULL )
                    //g_player->handle_keystate(currentKeyStates);

                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
                SDL_RenderClear( gRenderer );

                //Render objects
                render();

                //Update screen
                SDL_RenderPresent( gRenderer );

                cycle++;
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
