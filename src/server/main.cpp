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

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_net/SDL_net.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_net.h>
#endif

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

#include "Constants.h"
#include "Util.h"
#include "LTexture.h"
#include "Player.h"
#include "Alien.h"
#include "Planet.h"
#include "Laser.h"
#include "Asteroid.h"
#include "Explosion.h"
#include "Powerup.h"

using namespace std;

int tick = 0;
//int sleep_time = ;

bool g_show_minimap = true;

bool RENDER = false;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

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
bool g_targ_Follow_Rotation = false;
bool g_targ_Camera_Centered = true;
bool g_Following_Ship = true;

vector<string> g_imgfiles (imgarr, imgarr + sizeof(imgarr) / sizeof(imgarr[0]) );
vector<LTexture> g_textures (g_imgfiles.size());

vector<string> g_sndfiles (sndarr, sndarr + sizeof(sndarr) / sizeof(sndarr[0]) );
vector<Mix_Chunk*> g_sounds (g_sndfiles.size(), NULL );

vector<Object*> g_objects; // list of all the objects currently in the level
//Player player;
int player = 0;

vector<Player*> g_players;

void cycle_player() {
    //if( g_Following_Ship )
        player = fmod( (float)player+1, g_players.size() );
}
void toggle_camera() {
    if( g_Following_Ship ) {
        g_targ_Follow_Rotation = !g_targ_Follow_Rotation;
        g_targ_Camera_Centered = !g_targ_Camera_Centered;
    }
}

Mix_Music* g_music = NULL;

UDPsocket g_sd;       /* Socket descriptor */

bool init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    } else {
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
        //gWindow = SDL_CreateWindow( "Spaceship Game", 400, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        gWindow = SDL_CreateWindow( "Spaceship Game", 400, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL ) {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        } else {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL ) {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            } else {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }

        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
            printf( "SDL could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

    }

    return success;
}

bool init_net() {
    bool success = true;

    /* Initialize SDL_net */
    if (SDLNet_Init() < 0) {
        fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
        success = false;
    }

    /* Open a socket */
    if (!(g_sd = SDLNet_UDP_Open(2000))) {
        fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
        success = false;
    }

    return success;
}

bool loadMedia() {
    //Loading success flag
    bool success = true;

    //load textures
    for( uint i=0; i<g_imgfiles.size(); i++ ) {
        g_textures[i].setRenderer(gRenderer);
        if( !g_textures[i].loadFromFile( g_imgfiles[i] ) ) {
            cout << "Failed to load '" << g_imgfiles[i] << "'!" << endl;
            success = false;
        }
    }

    if( SOUND_ON ) {
        //load sounds
        for( uint i=0; i<g_sounds.size(); i++ ) {
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

    if( MUSIC_ON ) {
        //load music
        g_music = Mix_LoadMUS( "media/sounds/Amb.mp3" );
        if( g_music == NULL ) {
            printf( "Failed to load game music! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }
    }

    return success;
}

void loadObjects() { //load initial map objects
    g_objects.push_back( new Planet(1350.0, 1350.0) );
    g_objects.push_back( new Alien(1000.0, 750.0, 1065.0) );
    //g_objects.push_back( new Asteroid(-200.0, -200.0, 0.0, ((double) rand()/RAND_MAX)-0.5, ((double) rand()/RAND_MAX)-0.5, rand()%7-3, 1) );
    g_objects.push_back( new Asteroid(800.0, 800.0, 0.0, -1, -1, frandBetween(-20,20)/10, 1) );
    //g_objects.push_back( &player );

    //g_players.push_back( new Player(1, 900, 1100, 0) );
    //g_players.push_back( new Player(1, 900, 900, -45) );
    //g_players.push_back( new Player(2, 1100, 900, 180) );
    //g_players.push_back( new Player(2, 1100, 1100, 225) );

    for( uint i=0; i<g_players.size(); i++ )
        g_objects.push_back( g_players[i] );

    /* ROCKS EVERYWHERE!
    for( int i=0; i<200; i++ )
        g_objects.push_back( new Asteroid(randBetween(-500,2500), randBetween(-500,2500), rand()%360,
                    frandBetween(-10,10)/10, frandBetween(-10,10)/10, frandBetween(-20,20)/10, 1) );
    */

    /* EXPLOSION!
       for( int i=0; i<150; i++ )
       g_objects.push_back( new Asteroid(700+frandBetween(-10,10)/10,800+frandBetween(-10,10)/10,rand()%360,0,0,0,1) );
       */


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
    int player_health = g_players[player]->get_hitpoints();
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
                if( g_objects[i] == g_players[player] )
                    g_textures[ICON_SHIP_YOU].render_center(xrc, yrc, NULL, Angle);
                else if( g_players[player]->get_team() == g_objects[i]->get_team()
                        && g_players[player]->get_team() >= 0 )
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

void render_overlay() {
    if( g_players.size() > 0 )
        render_healthbar();
    if( g_show_minimap )
        render_minimap();
}

void render()
{
    //set the image as the render target
    gTargetTexture.setAsRenderTarget();
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
    SDL_RenderClear( gRenderer );

    if( g_players.size() == 0) {
        g_Following_Ship = false;
        g_targ_Follow_Rotation = false;
        g_targ_Camera_Centered = true;
    }

    float xPos_pl, yPos_pl, Angle_pl, xVel_pl, yVel_pl, rotVel_pl; // pl -> player
    if( g_players.size() > 0)
        g_players[player]->get_values(&xPos_pl, &yPos_pl, &Angle_pl, &xVel_pl, &yVel_pl, &rotVel_pl);

    if( g_Following_Ship ) {
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
    if( g_Following_Ship && g_targ_Follow_Rotation )
            g_rotVel_targ += rotVel_pl;

    g_Angle_targ = fmod( (g_Angle_targ + g_rotVel_targ + 360), 360 );

    int x_offset_dest, y_offset_dest;
    //1.5->top or left
    //2->middle
    //3->bottom or right
    x_offset_dest = 2;

    if( g_targ_Camera_Centered )
    //if( g_Following_Ship && g_targ_Camera_Centered )
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

    if( g_Following_Ship ) {
        g_xVel_cam = xVel_pl + diff_x/Deccel_cam;
        g_yVel_cam = yVel_pl + diff_y/Deccel_cam;
    } else {
        g_xVel_cam = 0 + diff_x/Deccel_cam;
        g_yVel_cam = 0 + diff_y/Deccel_cam;
    }

    g_xPos_cam = fmod( (g_xPos_cam + g_xVel_cam + LEVEL_WIDTH), LEVEL_WIDTH );
    g_yPos_cam = fmod( (g_yPos_cam + g_yVel_cam + LEVEL_HEIGHT), LEVEL_HEIGHT );

    render_overlay();
}

void handle_keystate(const Uint8* currentKeyStates) {
    bool upKey = currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_W];
    bool downKey = currentKeyStates[SDL_SCANCODE_DOWN] || currentKeyStates[SDL_SCANCODE_S];
    bool leftKey = currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_A];
    bool rightKey = currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_D];
    bool rotLeft = currentKeyStates[SDL_SCANCODE_Q];
    bool rotRight = currentKeyStates[SDL_SCANCODE_E];

    double ang = M_PI * g_Angle_camdest;
    ang = ang / 180;

    if(upKey) {
        g_xPos_camdest += 10 * sin(ang);
        g_yPos_camdest -= 10 * cos(ang);
    }

    if(downKey) {
        g_xPos_camdest -= 10 * sin(ang);
        g_yPos_camdest += 10 * cos(ang);
    }

    if(leftKey) {
        g_xPos_camdest -= 10 * cos(ang);
        g_yPos_camdest -= 10 * sin(ang);
    }

    if(rightKey) {
        g_xPos_camdest += 10 * cos(ang);
        g_yPos_camdest += 10 * sin(ang);
    }

    if(rotLeft)
        g_Angle_camdest -= 2;

    if(rotRight)
        g_Angle_camdest += 2;

}

void close() {
    //Free loaded images
    for( uint i=0; i<g_textures.size(); i++ ) {
        g_textures[i].free();
    }

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}


//int main( int argc, char* args[] )
int main( int argc, char** argv ) {
    cout<<"Starting server"<<endl;

    if( argc == 2 ) {
        RENDER = (bool)argv[1];
    }

    if( RENDER ) {
        //Start up SDL and create window
        if( !init() ) {
            printf( "Failed to initialize!\n" );
            exit(EXIT_FAILURE);
        }
        //Load media
        if( !loadMedia() ) {
            printf( "Failed to load media!\n" );
            exit(EXIT_FAILURE);
        }
    }

    if( !init_net() ) {
        printf( "Failed to initialize net!\n" );
        exit(EXIT_FAILURE);
    }

    //Main loop flag
    bool quit = false;

    //list of unique host+port combinations that have connected to the server
    vector<Connection> connections;

    //keep a list of connections that were established then lost to allow reconnections to the same ship
    //vector<IPaddress> lost_connections;
    vector<Player*> lost_connections;

    //corresponding list of number of times a packet was received from that client
    //TODO: make struct with packets_recvd, prev_packets_recvd, num_missed

    //Event handler
    SDL_Event e;

    loadObjects();

    if( RENDER && MUSIC_ON )
        Mix_PlayMusic(g_music, -1);

    srand( time(NULL) );

    //While application is running
    while( !quit ) {
        if( RENDER ) {
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
                            g_players[player]->get_values(&xPos, &yPos, &Angle, &xVel, &yVel, &rotVel);
                            cout << "x: " << xPos << " | y: " << yPos << endl;
                            cout << "xv: " << xVel << " | yv: " << yVel << endl;
                            cout << "vel: "<<sqrt( xVel*xVel + yVel*yVel )<<endl;
                            break;
                        case SDLK_h:
                            cout<<g_players[player]->get_hitpoints()<<" HP"<<endl;
                            break;
                        case SDLK_c: //toggle camera mode
                            toggle_camera();
                            break;
                            //switch control between present Player ships
                        case SDLK_f:
                            g_Following_Ship = !g_Following_Ship;
                            if( !g_Following_Ship ) {
                                g_targ_Follow_Rotation = false;
                                g_targ_Camera_Centered = true;
                            }
                            break;
                        case SDLK_p:
                            cycle_player();
                            break;
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
        }

        UDPpacket *p;
        if (!(p = SDLNet_AllocPacket(128))) {
            fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
            exit(EXIT_FAILURE);
        }
        if (SDLNet_UDP_Recv(g_sd, p)) {
            vector<Connection>::iterator it;
            it = find_if( connections.begin(), connections.end(), find_addr(p->address) );
            vector<Player*>::iterator it2;
            if( it == connections.end() ) { //packet's address is not in connections vector
                it2 = find_if( lost_connections.begin(), lost_connections.end(), find_controller(p->address) );
                if( it2 == lost_connections.end() ) { //this is a new player
                    SDLNet_UDP_Bind(g_sd, 0, &p->address);
                    connections.push_back( Connection(p->address, 1, 0, 0) );
                    cout<<"Client connected with port "<<p->address.port<<"\n";
                    //cout<<"host: "<<p->address.host <<"\nport: "<<p->address.port <<endl;
                    cout<<"Current connections: "<<connections.size()<<endl;

                    Player* newplayer = new Player(p->address.port);
                    g_players.push_back( newplayer );
                    g_objects.push_back( newplayer );
                }
                else { //this is a reconnecting client
                    SDLNet_UDP_Bind(g_sd, 0, &p->address);
                    //connections.insert( connections.begin(), Connection(p->address, 1, 0, 0) );
                    //connections.insert( connections.begin() + (it2-lost_connections.begin()), Connection(p->address, 1, 0, 0) );
                    connections.push_back( Connection(p->address, 1, 0, 0) );
                    g_players.push_back( *it2 );
                    cout<<"Client reconnected with port "<<p->address.port<<"\n";
                    //cout<<"host: "<<p->address.host <<"\nport: "<<p->address.port <<endl;
                    cout<<"Current connections: "<<connections.size()<<endl;
                    lost_connections.erase( it2 );
                }
            }
            else //client is already connected. Read packet's keyboard state data
            {
                Keystate keystate;
                memcpy( &keystate, p->data, p->len );
                //if( connections.size() == g_players.size() )
                    g_players[it-connections.begin()]->handle_keystate(keystate);
                //else
                    //vector<Player*>::iterator it = 
                it->packets_recvd++;
                it->consec_missed = 0;
            }
        }

        for( int i=0; i<connections.size(); i++ ) {
            if( connections[i].packets_recvd == connections[i].prev_packets_recvd ) {
                connections[i].consec_missed++;
                if( connections[i].consec_missed >= CLIENT_CONNECTION_LOST_THRESHOLD ) {
                    lost_connections.push_back( g_players[i] );
                    Player* player = g_players[i];
                    player->handle_keystate( Keystate() );
                    g_players.erase( g_players.begin()+i );
                    //g_players.push_back( player );
                    cout<<"Lost connection to client with port "<<connections[i].address.port
                        <<" (missed "<<CLIENT_CONNECTION_LOST_THRESHOLD<<" consecutive packets)"<<endl;
                    SDLNet_UDP_Unbind( g_sd, 0 );
                    connections.erase( connections.begin()+i );
                    for( int i=0; i<connections.size(); i++ )
                        SDLNet_UDP_Bind(g_sd, 0, &connections[i].address);
                    continue;
                }
            }
            connections[i].prev_packets_recvd = connections[i].packets_recvd;
        }

        SDLNet_FreePacket(p);

        if( RENDER ) {
            //handle spectator mode actions based on current key state of server
            const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
            handle_keystate(currentKeyStates);
        }

        UDPpacket** p_out;
        if (!(p_out = SDLNet_AllocPacketV(g_objects.size(), MAX_OBJECTS * 16))) {
            fprintf(stderr, "SDLNet_AllocPacketV: %s\n", SDLNet_GetError());
            exit(EXIT_FAILURE);
        }
        for( int i=0; i<g_objects.size(); i++ ) {
            memcpy( p_out[i]->data, g_objects[i], sizeof(*g_objects[i]) );
            p_out[i]->len = sizeof(*g_objects[i]);
            p_out[i]->channel = 0;
        }

        //cout<<g_objects.size()<<endl;

        SDLNet_UDP_SendV(g_sd, p_out, g_objects.size() );
        //cout<<"sent packet"<<endl;

        SDLNet_FreePacketV(p_out);

        /*
        if (SDLNet_UDP_Recv(g_sd, p)) {
            SDLNet_UDP_Bind(g_sd, 0, &p->address);
            if (strcmp((char *)p->data, "p") == 0) {
                cycle_player();
                //sscanf("WOOparty!", "%s", (char *)p->data);
                //p->len = strlen((char *)p->data) + 1;
            } else if (strcmp((char *)p->data, "f") == 0) {
                g_Following_Ship = !g_Following_Ship;
            } else if (strcmp((char *)p->data, "l") == 0) {
                g_xPos_camdest -= 300;
            } else if (strcmp((char *)p->data, "r") == 0) {
                g_xPos_camdest += 300;
            } else if (strcmp((char *)p->data, "u") == 0) {
                g_yPos_camdest -= 300;
            } else if (strcmp((char *)p->data, "d") == 0) {
                g_yPos_camdest += 300;
            } else if (strcmp((char *)p->data, "get_state") == 0) {
                p->data = (Uint8*)&g_objects;
                p->len = sizeof(g_objects);
            }
            //SDLNet_UDP_Send(g_sd, -1, p);
        }
        */

        /*
        vector<const Uint8*> playerKeyStates ( g_connections.size() );
        for( int i=0; i<playerKeyStates.size(); i++ )
        {
            g_players[i]->handle_keystate(playerKeyStates[i]);
        }
        */

        for( uint i = 0; i<g_objects.size(); i++ )
        {
            if( g_objects[i]->is_dead() ) {
                if( !g_objects[i]->is_persistent() )
                    delete g_objects[i];
                g_objects.erase( g_objects.begin()+i );
                i--;
            } else
                g_objects[i]->update();
        }
        for( uint i = 0; i<g_players.size(); i++ )
        {
            if( g_players[i]->is_dead() )
                g_players[i]->update();
        }

        if( RENDER ) {
            //Clear screen
            SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
            SDL_RenderClear( gRenderer );

            //Render objects
            render();
            //render( g_objects );

            //Update screen
            SDL_RenderPresent( gRenderer );
        }

        if (!RENDER)
            usleep(15000);

            tick++;
    }

    //Free resources and close SDL

    if( RENDER )
        close();

    return 0;
}
