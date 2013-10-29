/**
 * CS-130   Fall 2013
 * Software Development Project
     *** Spaceship Game ***

 * Group Members:
 *  Daniel Hakimian
 *  Taylor Martin
 *  Mason Neal
 *  Rob Schneider
 */

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#endif
#include <iostream>
#include <string>
#include <vector>

#include "Constants.h"
#include "Util.h"
#include "LTexture.h"
//#include "LTimer.h"
#include "Player.h"
#include "Alien.h"
#include "Planet.h"

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//The texture that everything adjacent will be rendered to before being rotated relative to the ship
LTexture gTargetTexture;

//The angle at which the target texture is rendered
float Angle_targ = -100.0;

//The velocity at which that angle changes
float rotVel_targ = 0.0;
float rotAccel_targ = 0.0;

std::vector<std::string> images (imgarr, imgarr + sizeof(imgarr) / sizeof(imgarr[0]) );

std::vector<LTexture> textures (images.size());

std::vector<Object*> objects; // list of all the objects currently in the level
//Player player;
int player = 0;

std::vector<Player*> players;

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Enable VSync
        if( !SDL_SetHint( SDL_HINT_RENDER_VSYNC, "1" ) )
        {
            printf( "Warning: VSync not enabled!" );
        }

        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        gWindow = SDL_CreateWindow( "Spaceship Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    for( unsigned int i=0; i<images.size(); i++ )
    {
        textures[i].setRenderer(gRenderer);
        if( !textures[i].loadFromFile( images[i] ) )
        {
            std::cout << "Failed to load '" << images[i] << "'!" << std::endl;
            success = false;
        }
    }

    //Load texture target
    gTargetTexture.setRenderer(gRenderer);
    if( !gTargetTexture.createBlank( SCREEN_WIDTH + Render_Radius, SCREEN_HEIGHT + Render_Radius, SDL_TEXTUREACCESS_TARGET ) )
    {
        printf( "Failed to create target texture!\n" );
        success = false;
    }

    //these are only here temporarily -- they should be in loadObjects once that is being used
    objects.push_back( new Planet(500.0, 500.0) );
    objects.push_back( new Alien(200.0, 0.0, -35.0) );
    objects.push_back( new Ship(0.0, 0.0, 35.0) );

    players.push_back( new Player(100, 100, 135) );
    players.push_back( new Player(300, 100, -90) );
    players.push_back( new Player(100, 300, 0) );

    objects.push_back( players[0] );
    objects.push_back( players[1] );
    objects.push_back( players[2] );
    //objects.push_back( &player );
    return success;
}

//bool loadObjects()
//{
//}

void render()
{
    //set the image as the render target
    gTargetTexture.setAsRenderTarget();
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
    SDL_RenderClear( gRenderer );

    int xScreenPos = (SCREEN_WIDTH+Render_Radius)/2 ; //The center of the target image, which is...
    int yScreenPos = (SCREEN_HEIGHT+Render_Radius)/2; //...also where the player is centered 

    float xPos_pl, yPos_pl, Angle_pl, xVel_pl, yVel_pl, rotVel_pl; // pl -> player
    players[player]->get_values(&xPos_pl, &yPos_pl, &Angle_pl, &xVel_pl, &yVel_pl, &rotVel_pl);
    
    //render the background tiles that are within a certain radius of the player, and also...
    //...render tiles on the other side of a wrap to replace the void
    int tile_w = textures[BACKGROUND].getWidth();
    int tile_h = textures[BACKGROUND].getHeight();
    for( int i=0; i<LEVEL_WIDTH; i+= tile_w )
    {
        for( int j=0; j<LEVEL_HEIGHT; j+=tile_h )
        {
            bool render = false;
            int xrc = i+xScreenPos-xPos_pl; // X render coordinate
            int yrc = j+yScreenPos-yPos_pl; // Y render coordinate

            int tilePos_x = i + tile_w/2;
            int tilePos_y = j + tile_h/2;

            // only render if within a certain radius of the player
            if( abs( tilePos_x - xPos_pl ) < Render_Radius && abs( tilePos_y - yPos_pl ) < Render_Radius )
                render = true;
                //textures[BACKGROUND].render( i+xScreenPos-xPos_pl, j+yScreenPos-yPos_pl);
            else { //image is not close enough, so don't render, but first...
                //...check if the image would be close enough if the map actually wrapped, so...
                //...we can render tiles from the other side of an edge-wrap to eliminate the void
                if( abs( tilePos_x + LEVEL_WIDTH - xPos_pl ) < Render_Radius ) //r
                    {xrc += LEVEL_WIDTH; render = true;}
                if( abs( tilePos_y + LEVEL_HEIGHT - yPos_pl ) < Render_Radius ) //b
                    {yrc += LEVEL_HEIGHT; render = true;}
                if( abs( tilePos_x - LEVEL_WIDTH - xPos_pl ) < Render_Radius ) //l
                    {xrc -= LEVEL_WIDTH; render = true;}
                if( abs( tilePos_y - LEVEL_HEIGHT - yPos_pl ) < Render_Radius ) //t
                    {yrc -= LEVEL_HEIGHT; render = true;}
            }
            if( render )
                textures[BACKGROUND].render( xrc, yrc );
            //else they are not close enough, so don't render them.
        }
    }

    SDL_Point center;
    center.x = xScreenPos;
    center.y = yScreenPos;

    int xScreenPos_ren, yScreenPos_ren;

    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

    //loop through the list of currently present objects to render them
    for( unsigned int i=0; i<objects.size(); i++ )
    {
        float xPos, yPos, Angle; 
        objects[i]->get_values(&xPos, &yPos, &Angle);
        int tex_index = objects[i]->get_tex_index();

        bool render = false;
        xScreenPos_ren = xScreenPos - textures[tex_index].getWidth()/2;
        yScreenPos_ren = yScreenPos - textures[tex_index].getWidth()/2;
        int xrc = xPos+xScreenPos_ren-xPos_pl; // X render coordinate
        int yrc = yPos+yScreenPos_ren-yPos_pl; // Y render coordinate

        // only render if within a certain radius of the player
        if( abs( xPos - xPos_pl ) < Render_Radius && abs( yPos - yPos_pl ) < Render_Radius )
            render = true;
        else {//object is not close enough, so don't render, but first...
            //...check if the object would be close enough if the map actually wrapped, so we can...
            //...render objects from the other side of an edge-wrap so they don't disapper near edges
            if( abs( xPos + LEVEL_WIDTH - xPos_pl ) < Render_Radius ) //r
                {xrc += LEVEL_WIDTH; render = true;}
            if( abs( yPos + LEVEL_HEIGHT - yPos_pl ) < Render_Radius ) //b
                {yrc += LEVEL_HEIGHT; render = true;}
            if( abs( xPos - LEVEL_WIDTH - xPos_pl ) < Render_Radius ) //l
                {xrc -= LEVEL_WIDTH; render = true;}
            if( abs( yPos - LEVEL_HEIGHT - yPos_pl ) < Render_Radius ) //t
                {yrc -= LEVEL_HEIGHT; render = true;}
        }
        if( render )
            objects[i]->render(xrc, yrc, Angle, currentKeyStates);
        //else they are not close enough, so don't render them.
    }

    //Reset render target to the window
    SDL_SetRenderTarget( gRenderer, NULL );

    /*
    float TARG_ROT_ACCEL = 0.02;
    //if( (rotVel_pl - rotVel_targ) </> ___ && abs(rotVel_targ - rotVel_pl) < 180 )
    if( Angle_targ < Angle_pl && abs(Angle_targ - Angle_pl) > 180 )
    //if( rotVel_targ < rotVel_pl )
    {
        rotVel_targ += TARG_ROT_ACCEL;
        //Angle_targ += 1;
    } else if( Angle_targ > Angle_pl && abs(Angle_targ - Angle_pl) <= 180 )
    // else if( rotVel_targ > rotVel_pl )
    {
        rotVel_targ -= TARG_ROT_ACCEL;
        //Angle_targ -= 1;
    }

    if( abs(Angle_targ - Angle_pl) < 0.1 )
    //if(Angle_targ == Angle_pl)
    {
        //std::cout<<"eq"<<std::endl;
        rotVel_targ = rotVel_pl;
    }
    */

    float diff = abs(Angle_pl - Angle_targ);
    std::cout << diff << std::endl;
    if( diff < 180 )
        rotAccel_targ = -diff/20.0;
    else if( diff >= 180 )
        rotAccel_targ = -diff/20.0;
    //std::cout<<rotAccel_targ<<" a | v ";
    rotVel_targ = rotVel_pl + rotAccel_targ;
    //std::cout<<rotVel_targ<<std::endl;
    /*
    rotVel_targ = (Angle_pl - Angle_targ)/10.0;
    std::cout<<rotVel_targ<<std::endl;
    */

    Angle_targ = fmod( (Angle_targ + rotVel_targ + 360), 360 );

    //gTargetTexture.render( -(Render_Radius/2), -(Render_Radius/3), NULL, -Angle_pl, &center );
    gTargetTexture.render( -(Render_Radius/2), -(Render_Radius/3), NULL, -Angle_targ, &center );
    //std::cout<<Angle_pl<<" angPL | angT "<<Angle_targ<<std::endl;

    //anything rendered past here will be overlayed on top of the screen
    //everything before gets rotated with the ship

    //this code is the health bar
    float xp, yp;
    xp = (SCREEN_WIDTH / 2) - 151;
    yp = 1;
    //code for drawing the right ammount of health increments depending on palyers health
    int player_health = players[player]->hitpoints;
    if(player_health > 93.5)
        textures[HEALTH_15].render(xp, yp);
    else if(player_health > 87)
        textures[HEALTH_14].render(xp, yp);
    else if(player_health > 80.5)
        textures[HEALTH_13].render(xp, yp);
    else if(player_health > 74)
        textures[HEALTH_12].render(xp, yp);
    else if(player_health > 67.5)
        textures[HEALTH_11].render(xp, yp);
    else if(player_health > 61)
        textures[HEALTH_10].render(xp, yp);
    else if(player_health > 54.5)
        textures[HEALTH_9].render(xp, yp);
    else if(player_health > 48)
        textures[HEALTH_8].render(xp, yp);
    else if(player_health > 41.5)
        textures[HEALTH_7].render(xp, yp);
    else if(player_health > 35)
        textures[HEALTH_6].render(xp, yp);
    else if(player_health > 28.5)
        textures[HEALTH_5].render(xp, yp);
    else if(player_health > 22)
        textures[HEALTH_4].render(xp, yp);
    else if(player_health > 15.5)
        textures[HEALTH_3].render(xp, yp);
    else if(player_health > 9)
        textures[HEALTH_2].render(xp, yp);
    else if(player_health > 2.5)
        textures[HEALTH_1].render(xp, yp);
    else
        textures[HEALTH_0].render(xp, yp);

    //test code to make sure hit fuction in the ship class is working. it lowers the players health if you press the K key     
    if(currentKeyStates[SDL_SCANCODE_K])
    {
        players[player]->hitpoints -= 1;
    }

}

//handle actions based on current key state
void handle_keystate()
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

    bool upKey = currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_W];
    bool downKey = currentKeyStates[SDL_SCANCODE_DOWN] || currentKeyStates[SDL_SCANCODE_S];
    bool leftKey = currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_A];
    bool rightKey = currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_D];
    bool strafeLeft = currentKeyStates[SDL_SCANCODE_Q];
    bool strafeRight = currentKeyStates[SDL_SCANCODE_E];

    if(upKey)
        players[player]->thrust_b();
    if(downKey)
        players[player]->thrust_f();
    if(leftKey)
        players[player]->rot_l();
    if(rightKey)
        players[player]->rot_r();
    if(strafeLeft)
        players[player]->thrust_r();
    if(strafeRight)
        players[player]->thrust_l();

}


void close()
{
    //Free loaded images
    for( unsigned int i=0; i<textures.size(); i++ )
    {
        textures[i].free();
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


int main( int argc, char* args[] )
{
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;


            //While application is running
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    if( e.type == SDL_KEYDOWN )
                    {
                        switch( e.key.keysym.sym ) {
                            case SDLK_f:
                                toggle_fullscreen(gWindow);
                                break;
                            case SDLK_ESCAPE:
                                quit = true;
                                break;
                            case SDLK_c:
                                float xPos, yPos, Angle; 
                                players[player]->get_values(&xPos, &yPos, &Angle);
                                std::cout <<"x: "<<xPos<< " y: "<<yPos<< " ang: "<<Angle<<std::endl;
                                break;
                            case SDLK_p:
                                player = fmod( player+1, players.size() );
                                break;
                        }
                    }
                }

                //handle actions based on current key state
                handle_keystate();

                //Move the ship
                //player.update();
                for( unsigned int i = 0; i<objects.size(); i++ )
                    objects[i]->update();

                //Clear screen
                //SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
                SDL_RenderClear( gRenderer );

                //Render objects
                render();
                //render( objects );

                //Update screen
                SDL_RenderPresent( gRenderer );
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
