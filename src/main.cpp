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

std::vector<std::string> images = {
    "media/bg_image.gif",
    "media/ship.png",
    "media/ship_thr_b.png",
    "media/ship_thr_l.png",
    "media/ship_thr_r.png",
    //"media/ship_thr_f.png",
};

std::vector<LTexture> textures (images.size());

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

    /*
    if( !background.loadFromFile( ren, "media/bg_image.gif" ) ) {
        printf( "Failed to load background image!\n" );
        success = false;
    }
    if( !shipTex.loadFromFile( ren, "media/ship.png" ) ) {
        printf( "Failed to load ship texture!\n" );
        success = false;
    }
    if( !thr_bTex.loadFromFile( ren, "media/ship_thr_b.png" ) ) {
        printf( "Failed to load rear thrust texture!\n" );
        success = false;
    }
    if( !thr_lTex.loadFromFile( ren, "media/ship_thr_l.png" ) ) {
        printf( "Failed to load port thrust texture!\n" );
        success = false;
    }
    if( !thr_rTex.loadFromFile( ren, "media/ship_thr_r.png" ) ) {
        printf( "Failed to load starboard thrust texture!\n" );
        success = false;
    }
    */
    /*
       if( !thr_fTex.loadFromFile( ren, "media/ship_thr_f.png" ) ) {
       printf( "Failed to load front thrust texture!\n" );
       success = false;
       }
       */

    return success;
}

//void render(SDL_Renderer* ren, int camX, int camY)
void render(SDL_Renderer* ren, Player* player)
{
    float xPos, yPos, Angle; 
    player->get_values(xPos, yPos, Angle);
    //int xPosRel = (int)xPos - camX; //position relative to the camera
    //int yPosRel = (int)yPos - camY; //position relative to the camera
    //Render the the ship
    //textures[SHIP].render( ren, xPosRel, yPosRel, NULL, Angle );

    int xScreenPos = SCREEN_WIDTH/2;    //The position on the screen where the ship resides..
    int yScreenPos = SCREEN_HEIGHT-150; //..as the world moves relative to it

    SDL_Point center;
    float center_x = xPos + (textures[SHIP].getWidth() / 2);
    float center_y = yPos + (textures[SHIP].getHeight() / 2);

    int tile_w = textures[BACKGROUND].getWidth();
    int tile_h = textures[BACKGROUND].getHeight();
    for( int i=0; i<LEVEL_WIDTH; i+= tile_w )
        for( int j=0; j<LEVEL_HEIGHT; j+=tile_h )
        {
            center.x = center_x - i;
            center.y = center_y - j;
            textures[BACKGROUND].render( ren, i+xScreenPos-xPos, j+yScreenPos-yPos, NULL, -Angle, &center);
        }
    //textures[BACKGROUND].render( ren, xScreenPos-xPos, yScreenPos-yPos, NULL, -Angle, &center);
    textures[SHIP].render( ren, xScreenPos, yScreenPos );

    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    if( currentKeyStates[ SDL_SCANCODE_UP ] )
        textures[THR_B].render( ren, xScreenPos, yScreenPos );
    if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
        textures[THR_L].render( ren, xScreenPos, yScreenPos );
    if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
        textures[THR_R].render( ren, xScreenPos, yScreenPos );
    //if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
        //textures[THR_F].render( ren, (int)xPos, (int)yPos, NULL, Angle, &center );
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
                        }
                    }
                }

                //Handle input for the dot
                player.handleEvent( e );

                //Move the dot
                player.move();

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

/*
int main(int argc, char **argv){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (win == nullptr){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr){
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Surface *bmp = SDL_LoadBMP("hello_world.bmp");
    if (bmp == nullptr){
        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if (tex == nullptr){
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, tex, NULL, NULL);
    SDL_RenderPresent(ren);

    SDL_Delay(2000);

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
*/
