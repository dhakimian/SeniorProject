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

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

static const std::string imgarr[] = {
    "media/bg_image.gif",
    //"media/solid_bg.png",
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
    "media/player/SF_Ship/ship_body_Ltilt.png"
};
std::vector<std::string> images (imgarr, imgarr + sizeof(imgarr) / sizeof(imgarr[0]) );

std::vector<LTexture> textures (images.size());

//std::vector<Object> objects; // list of all the objects currently in the level

std::vector<ImgInstance> cur_images; // the images to be rendered this frame, with their coords and angle

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

bool loadMedia(SDL_Renderer* ren)
{
    //Loading success flag
    bool success = true;

    for( unsigned int i=0; i<images.size(); i++ )
    {
        if( !textures[i].loadFromFile( gRenderer, images[i] ) )
        {
            std::cout << "Failed to load '" << images[i] << "'!" << std::endl;
            success = false;
        }
    }

    return success;
}

//void render(SDL_Renderer* ren, int camX, int camY)
void render(SDL_Renderer* ren, Player* player)
{
    float xPos, yPos, Angle; 
    player->get_values(&xPos, &yPos, &Angle);

    int xScreenPos = SCREEN_WIDTH/2 ;    //The position on the screen where the ship resides..
    int yScreenPos = SCREEN_HEIGHT*3/4; //..as the world moves relative to it

    SDL_Point center;

    int tile_w = textures[BACKGROUND].getWidth();
    int tile_h = textures[BACKGROUND].getHeight();
    for( int i=0; i<LEVEL_WIDTH; i+= tile_w )
        for( int j=0; j<LEVEL_HEIGHT; j+=tile_h )
        {
            center.x = xPos - i;
            center.y = yPos - j;
            textures[BACKGROUND].render( ren, i+xScreenPos-xPos, j+yScreenPos-yPos, NULL, -Angle, &center);
        }

    xScreenPos -= textures[PLAYER].getWidth()/2;  //shift the coords so that the center of the image..
    yScreenPos -= textures[PLAYER].getHeight()/2; //..(not the top left corner of the image) will be...
                                                  //..on the point of the ship's position

    textures[PLAYER].render( ren, xScreenPos, yScreenPos );

    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

    // here is my(robs) added code that implements a cool ship that has some moving parts.

    //local variables resembling if movement keys are pushed. Includes both wasd and updownleftright.
    //makes less to type in each if statement
    bool rightKey = currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_D];
    bool leftKey = currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_A];
    bool upKey = currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_W];
    bool downKey = currentKeyStates[SDL_SCANCODE_DOWN] || currentKeyStates[SDL_SCANCODE_S];

    //renders the thruster images according to which button you pushed. works for both wasd and up/down/left/rt keys 
    //
    if(upKey)
        textures[PLAYER_THR_B].render( ren, xScreenPos, yScreenPos );
    if(leftKey)
        textures[PLAYER_THR_L].render( ren, xScreenPos, yScreenPos );
    if(rightKey)
        textures[PLAYER_THR_R].render( ren, xScreenPos, yScreenPos );
    if(downKey)
        textures[PLAYER_THR_F].render( ren, xScreenPos, yScreenPos );
    //these conditionals draw different wing orentations depending on which direction the ship is turning.
    if(downKey && !upKey){
        textures[PLAYER].render( ren, xScreenPos, yScreenPos );
        textures[PLAYER_WNG_B].render(ren, xScreenPos, yScreenPos);}
    if(leftKey && !rightKey && !downKey){
        textures[PLAYER_Tlt_L].render( ren, xScreenPos, yScreenPos );
        textures[PLAYER_WNG_L].render(ren, xScreenPos, yScreenPos);}
    if(rightKey && !leftKey && !downKey){
        textures[PLAYER_Tlt_R].render( ren, xScreenPos, yScreenPos );    
        textures[PLAYER_WNG_R].render(ren, xScreenPos, yScreenPos);}
    if(upKey && !downKey && !leftKey && !rightKey){
        textures[PLAYER].render( ren, xScreenPos, yScreenPos );    
        textures[PLAYER_WNG_F].render(ren, xScreenPos, yScreenPos);}
    if((downKey && upKey) || (leftKey && rightKey)){ 
        textures[PLAYER].render( ren, xScreenPos, yScreenPos );   
        textures[PLAYER_WNG_NORM].render(ren, xScreenPos, yScreenPos);}
    if(!downKey && !upKey && !leftKey && !rightKey){
        textures[PLAYER].render( ren, xScreenPos, yScreenPos );
        textures[PLAYER_WNG_NORM].render(ren, xScreenPos, yScreenPos);}

}

//handle actions based on current key state
void handle_keystate(Player* player)
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

    bool upKey = currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_W];
    bool downKey = currentKeyStates[SDL_SCANCODE_DOWN] || currentKeyStates[SDL_SCANCODE_S];
    bool leftKey = currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_A];
    bool rightKey = currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_D];

    if(upKey)
        player->thrust_b();
    if(downKey)
        player->thrust_f();
    if(leftKey)
        player->thrust_l();
    if(rightKey)
        player->thrust_r();

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
        if( !loadMedia(gRenderer) )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;
            //The dot that will be moving around on the screen
            Player player;

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
                            case SDLK_q:
                                quit = true;
                                break;
                            case SDLK_ESCAPE:
                                quit = true;
                                break;
                            case SDLK_c:
                                float xPos, yPos, Angle; 
                                player.get_values(&xPos, &yPos, &Angle);
                                std::cout << "x: " << xPos << " | y: " << yPos << std::endl;
                                break;
                        }
                    }
                }

                //handle actions based on current key state
                handle_keystate( &player );

                //Move the ship
                player.update();

                //Clear screen
                //SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
                SDL_RenderClear( gRenderer );

                //Render objects
                render( gRenderer, &player );

                //Update screen
                SDL_RenderPresent( gRenderer );
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
