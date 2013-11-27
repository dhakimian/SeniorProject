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
#include <SDL2_mixer/SDL_mixer.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#endif
#include <iostream>
#include <string>
#include <vector>
//#include <typeinfo>

#include "Constants.h"
#include "Util.h"
#include "LTexture.h"
#include "Player.h"
#include "Alien.h"
#include "Planet.h"
#include "Laser.h"
#include "Asteroid.h"
#include "Explosion.h"
//#include "PowerUp.h"

bool show_minimap = true;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//The texture that everything adjacent will be rendered to before being rotated relative to the ship
LTexture gTargetTexture;

//The texture that the minimap is rendered to before being rotated relative to the ship
LTexture gMinimap;

//The angle at which the target texture is rendered
float Angle_targ = 30.0;

//The velocity at which that angle changes
float rotVel_targ = 0.0;

//these (similar to the above) deal with motion/position of the target texture
float xOffset_targ = 2;
float yOffset_targ = 2;
float xVel_targ = 0.0;
float yVel_targ = 0.0;

//these deal with motion/position of the contents of the target texture
float xPos_cam = SCREEN_WIDTH/2;
float yPos_cam = SCREEN_HEIGHT/2;
float xVel_cam = 0.0;
float yVel_cam = 0.0;

//boolean config options
bool targ_Follow_Rotation = true;
bool targ_Ship_Centered = false;

std::vector<std::string> imgfiles (imgarr, imgarr + sizeof(imgarr) / sizeof(imgarr[0]) );
std::vector<LTexture> textures (imgfiles.size());

std::vector<std::string> sndfiles (sndarr, sndarr + sizeof(sndarr) / sizeof(sndarr[0]) );
std::vector<Mix_Chunk*> sounds (sndfiles.size(), NULL );

std::vector<Object*> objects; // list of all the objects currently in the level
//Player player;
int player = 0;

std::vector<Player*> players;

Mix_Music* music = NULL;

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

        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
            printf( "SDL could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //load textures
    for( uint i=0; i<imgfiles.size(); i++ )
    {
        textures[i].setRenderer(gRenderer);
        if( !textures[i].loadFromFile( imgfiles[i] ) )
        {
            std::cout << "Failed to load '" << imgfiles[i] << "'!" << std::endl;
            success = false;
        }
    }

    //load sounds
    for( uint i=0; i<sounds.size(); i++ )
    {
        sounds[i] = Mix_LoadWAV( sndfiles[i].c_str() );
        if( sounds[i] == NULL )
        {
            std::cout << "Failed to load '" << sndfiles[i] << "'!" << std::endl;
            success = false;
        }
    }

    //Load texture target
    gTargetTexture.setRenderer(gRenderer);
    if( !gTargetTexture.createBlank( TARG_W, TARG_H, SDL_TEXTUREACCESS_TARGET ) )
    {
        printf( "Failed to create main target texture!\n" );
        success = false;
    }

    //Load minimap target tex
    gMinimap.setRenderer(gRenderer);
    if( !gMinimap.createBlank( textures[MAP].getWidth(), textures[MAP].getHeight(), SDL_TEXTUREACCESS_TARGET ) )
    {
        printf( "Failed to create minimap target texture!\n" );
        success = false;
    }
    else {
        //Set standard alpha blending
        gMinimap.setBlendMode( SDL_BLENDMODE_BLEND );
    }

    //load music
    music = Mix_LoadMUS( "media/sounds/Amb.wav" );
    if( music == NULL )
    {
        printf( "Failed to load game music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    return success;
}

//load initial map objects
void loadObjects()
{
    objects.push_back( new Planet(350.0, 350.0) );
    objects.push_back( new Alien(0.0, -250.0, -35.0) );
    objects.push_back( new Asteroid(-200.0, -200.0, 0.0, ((double) rand()/RAND_MAX)-0.5, ((double) rand()/RAND_MAX)-0.5, rand()%7-3, 1) );
    //objects.push_back( &player );
    
    players.push_back( new Player(1, -100, 100, 0) );
    players.push_back( new Player(1, -100, -100, -45) );
    players.push_back( new Player(2, 100, -100, 180) );
    players.push_back( new Player(2, 100, 100, 225) );

    for( uint i=0; i<players.size(); i++ )
        objects.push_back( players[i] );

    /* ROCKS EVERYWHERE!
    for( int i=0; i<300; i++ )
        objects.push_back( new Asteroid(rand()%2000-1000,rand()%2000-1000,rand()%360,0,0,rand()%7-3,1) );
    */

    /* EXPLOSION!
    for( int i=0; i<150; i++ )
        objects.push_back( new Asteroid(-300+rand()%3-1,-200+rand()%3-1,rand()%360,0,0,0,1) );
    */


}

void render_bg()
{   //render the background tiles that are within a certain radius of the camera, and also...
    //...render tiles on the other side of a wrap to replace the void
    int tile_w = textures[BACKGROUND].getWidth();
    int tile_h = textures[BACKGROUND].getHeight();
    for( int i=0; i<LEVEL_WIDTH; i+= tile_w )
    {
        for( int j=0; j<LEVEL_HEIGHT; j+=tile_h )
        {
            bool render = false;
            int xrc = i+TARG_cX-xPos_cam; // X render coordinate
            int yrc = j+TARG_cY-yPos_cam; // Y render coordinate

            int tilePos_x = i + tile_w/2;
            int tilePos_y = j + tile_h/2;

            // only render if within a certain radius
            if( abs(tilePos_x - xPos_cam) < Render_Radius && abs(tilePos_y - yPos_cam) < Render_Radius )
                render = true;
            else { //image is not close enough, so don't render, but first...
                //...check if the image would be close enough if the map literally wrapped, so...
                //...we can render tiles from the other side of an edge-wrap to eliminate the void
                if( abs(tilePos_x + LEVEL_WIDTH - xPos_cam) < Render_Radius ) {//r
                    xrc += LEVEL_WIDTH; render = true;}
                if( abs(tilePos_y + LEVEL_HEIGHT - yPos_cam) < Render_Radius ) {//b
                    yrc += LEVEL_HEIGHT; render = true;}
                if( abs(tilePos_x - LEVEL_WIDTH - xPos_cam) < Render_Radius ) {//l
                    xrc -= LEVEL_WIDTH; render = true;}
                if( abs(tilePos_y - LEVEL_HEIGHT - yPos_cam) < Render_Radius ) {//t
                    yrc -= LEVEL_HEIGHT; render = true;}
            }
            if( render )
                textures[BACKGROUND].render( xrc, yrc );
            //else they are not close enough, so don't render them.
        }
    }
}

void render_objects()
{
    //loop through the list of currently present objects to render them
    for( uint i=0; i<objects.size(); i++ )
    //for( int i=objects.size()-1; i>=0; i-- )
    {
        float xPos, yPos, Angle; 
        objects[i]->get_values(&xPos, &yPos, &Angle);
        //int tex_index = objects[i]->get_tex_index();

        bool render = false;

        int xrc = xPos+TARG_cX-xPos_cam; // X render coordinate
        int yrc = yPos+TARG_cY-yPos_cam; // Y render coordinate

        // only render if within a certain radius
        //if( abs( xPos - xPos_cam ) < Render_Radius && abs( yPos - yPos_cam ) < Render_Radius )
        if( distanceSquared(xPos, yPos, xPos_cam, yPos_cam) < Render_Radius*Render_Radius )
            render = true;
        else {//object is not close enough, so don't render, but first...
            //...check if the object would be close enough if the map literally wrapped, so we can...
            //...render objects from the other side of an edge-wrap so they don't disapper near edges
            if( abs( xPos + LEVEL_WIDTH - xPos_cam ) < Render_Radius ) {//r
                xrc += LEVEL_WIDTH; render = true;}
            if( abs( yPos + LEVEL_HEIGHT - yPos_cam ) < Render_Radius ) {//b
                yrc += LEVEL_HEIGHT; render = true;}
            if( abs( xPos - LEVEL_WIDTH - xPos_cam ) < Render_Radius ) {//l
                xrc -= LEVEL_WIDTH; render = true;}
            if( abs( yPos - LEVEL_HEIGHT - yPos_cam ) < Render_Radius ) {//t
                yrc -= LEVEL_HEIGHT; render = true;}
        }
        if( render )
            objects[i]->render(xrc, yrc, Angle, true);
        //else they are not close enough, so don't render them.
    }
}

void render_healthbar()
{
    //this code is the health bar
    float xp, yp;
    xp = (SCREEN_WIDTH / 2) - 151;
    yp = 1;
    //code for drawing the right ammount of health increments depending on palyers health
    int player_health = players[player]->get_hitpoints();
    if(player_health > 935)
        textures[HEALTH_15].render(xp, yp);
    else if(player_health > 870)
        textures[HEALTH_14].render(xp, yp);
    else if(player_health > 805)
        textures[HEALTH_13].render(xp, yp);
    else if(player_health > 740)
        textures[HEALTH_12].render(xp, yp);
    else if(player_health > 675)
        textures[HEALTH_11].render(xp, yp);
    else if(player_health > 610)
        textures[HEALTH_10].render(xp, yp);
    else if(player_health > 545)
        textures[HEALTH_9].render(xp, yp);
    else if(player_health > 480)
        textures[HEALTH_8].render(xp, yp);
    else if(player_health > 415)
        textures[HEALTH_7].render(xp, yp);
    else if(player_health > 350)
        textures[HEALTH_6].render(xp, yp);
    else if(player_health > 285)
        textures[HEALTH_5].render(xp, yp);
    else if(player_health > 220)
        textures[HEALTH_4].render(xp, yp);
    else if(player_health > 155)
        textures[HEALTH_3].render(xp, yp);
    else if(player_health > 90)
        textures[HEALTH_2].render(xp, yp);
    else if(player_health > 25)
        textures[HEALTH_1].render(xp, yp);
    else
        textures[HEALTH_0].render(xp, yp);

}

void render_minimap()
{
    gMinimap.setAsRenderTarget();
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
    SDL_RenderClear( gRenderer );

    textures[MAP].render(0, 0);
    //if a directional tracking system is implemented, we can modify the MAP texture to have a
    //pointer of some sort on it, and rotate it here before rendering to it, so that the minimap
    //can also act as a compass that points to our target

    for( uint i=0; i<objects.size(); i++ )
    {
        float xPos, yPos, Angle; 
        objects[i]->get_values(&xPos, &yPos, &Angle);

        int xrc = xPos-xPos_cam;
        int yrc = yPos-yPos_cam;

        //edgewrapping stuff
        if( abs( xPos + LEVEL_WIDTH - xPos_cam ) < Minimap_Radius ) //r
            xrc += LEVEL_WIDTH;
        if( abs( yPos + LEVEL_HEIGHT - yPos_cam ) < Minimap_Radius ) //b
            yrc += LEVEL_HEIGHT;
        if( abs( xPos - LEVEL_WIDTH - xPos_cam ) < Minimap_Radius ) //l
            xrc -= LEVEL_WIDTH;
        if( abs( yPos - LEVEL_HEIGHT - yPos_cam ) < Minimap_Radius ) //t
            yrc -= LEVEL_HEIGHT;

        if( abs(distanceSquared(xrc+xPos_cam, yrc+yPos_cam, xPos_cam, yPos_cam))
                < Minimap_Radius*Minimap_Radius )
        {
            xrc *= ( ( (float)textures[MAP].getWidth()/2 ) / (Minimap_Radius) ); //scale down the coords
            yrc *= ( ( (float)textures[MAP].getHeight()/2 ) / (Minimap_Radius) ); //to fit on the minimap

            xrc += textures[MAP].getWidth()/2;  //shift the coords so that they are centered on
            yrc += textures[MAP].getHeight()/2; //the center of the minimap, not 0,0

            if( objects[i]->get_type() == T_PLAYER )
            {
                if( players[player]->get_team() == objects[i]->get_team()
                        && players[player]->get_team() >= 0 )
                    textures[ICON_SHIP_FRIENDLY].render_center(xrc, yrc, NULL, Angle);
                else
                    textures[ICON_SHIP_ENEMY].render_center(xrc, yrc, NULL, Angle);
            }
            else if( objects[i]->get_type() == T_PLANET )
                textures[ICON_PLANET].render_center(xrc, yrc, NULL, Angle);
            else if( objects[i]->get_type() == T_ALIEN )
                textures[ICON_SHIP_ENEMY].render_center(xrc, yrc, NULL, Angle);
            else if( objects[i]->get_type() == T_ASTEROID )
            {
                Asteroid* ast = (Asteroid*) objects[i];
                if( ast->get_size() == 1 ) 
                    textures[ICON_ASTEROID].render_center(xrc, yrc, NULL, Angle);
                else if( ast->get_size() == 2 )
                    textures[ICON_ASTEROIDMINI].render_center(xrc, yrc, NULL, Angle);
                else if( ast->get_size() == 3 )
                    textures[ICON_ASTEROIDTINY].render_center(xrc, yrc, NULL, Angle);
                //tiny asteroid are too small to be picked up on long range sensors?
            }
        }
    }

    //Reset render target to the window
    SDL_SetRenderTarget( gRenderer, NULL );

    gMinimap.render( 5, 5, NULL, -Angle_targ );
}

void render_overlay()
{
    render_healthbar();
    if( show_minimap )
        render_minimap();
}

void render()
{
    //set the image as the render target
    gTargetTexture.setAsRenderTarget();
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
    SDL_RenderClear( gRenderer );

    float xPos_pl, yPos_pl, Angle_pl, xVel_pl, yVel_pl, rotVel_pl; // pl -> player
    players[player]->get_values(&xPos_pl, &yPos_pl, &Angle_pl, &xVel_pl, &yVel_pl, &rotVel_pl);

    render_bg();

    render_objects();

    //Reset render target to the window
    SDL_SetRenderTarget( gRenderer, NULL );

    float diff_ang;
    if( targ_Follow_Rotation )
        diff_ang = Angle_pl - Angle_targ;
    else
        diff_ang = 0 - Angle_targ;

    if( diff_ang < -180 )
        diff_ang += 360;
    if( diff_ang >= 180 )
        diff_ang -= 360;

    if( targ_Follow_Rotation )
        rotVel_targ = rotVel_pl + diff_ang/rotDeccel_targ;
    else
        rotVel_targ = 0 + diff_ang/rotDeccel_targ;

    Angle_targ = fmod( (Angle_targ + rotVel_targ + 360), 360 );

    int x_offset_dest, y_offset_dest;
    //1.5->top or left
    //2->middle
    //3->bottom or right
    x_offset_dest = 2;

    if( targ_Ship_Centered )
        y_offset_dest = 2;
    else
        y_offset_dest = 3;

    float diff_x = x_offset_dest - xOffset_targ;
    float diff_y = y_offset_dest - yOffset_targ;

    xVel_targ = diff_x/Deccel_targ;
    yVel_targ = diff_y/Deccel_targ;
    
    xOffset_targ += xVel_targ;
    yOffset_targ += yVel_targ;

    ///--///
    gTargetTexture.render( -(Render_Radius/xOffset_targ), -(Render_Radius/yOffset_targ), NULL, -Angle_targ );
    ///--///

    diff_x = xPos_pl - xPos_cam;
    diff_y = yPos_pl - yPos_cam;

    if( diff_x < -LEVEL_WIDTH/2 )
        diff_x += LEVEL_WIDTH;
    if( diff_y < -LEVEL_HEIGHT/2 )
        diff_y += LEVEL_HEIGHT;
    if( diff_x >= LEVEL_WIDTH/2 )
        diff_x -= LEVEL_WIDTH;
    if( diff_y >= LEVEL_HEIGHT/2 )
        diff_y -= LEVEL_HEIGHT;

    xVel_cam = xVel_pl + diff_x/Deccel_cam;
    yVel_cam = yVel_pl + diff_y/Deccel_cam;
    
    xPos_cam = fmod( (xPos_cam + xVel_cam + LEVEL_WIDTH), LEVEL_WIDTH );
    yPos_cam = fmod( (yPos_cam + yVel_cam + LEVEL_HEIGHT), LEVEL_HEIGHT );

    render_overlay();
}

void close()
{
    //Free loaded images
    for( uint i=0; i<textures.size(); i++ )
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

            loadObjects();

            //While application is running
            if( MUSIC_ON )
                Mix_PlayMusic(music, -1);
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
                                //print current ship coords for debugging
                            case SDLK_TAB:
                                show_minimap = !show_minimap;
                                break;
                            case SDLK_x:
                                float xPos, yPos, Angle, xVel, yVel, rotVel; 
                                players[player]->get_values(&xPos, &yPos, &Angle, &xVel, &yVel, &rotVel);
                                std::cout << "x: " << xPos << " | y: " << yPos << std::endl;
                                std::cout << "xv: " << xVel << " | yv: " << yVel << std::endl;
                                break;
                            case SDLK_h:
                                std::cout<<players[player]->get_hitpoints()<<" HP"<<std::endl;
                                break;
                            case SDLK_c: //toggle camera mode
                                targ_Follow_Rotation = !targ_Follow_Rotation;
                                targ_Ship_Centered = !targ_Ship_Centered;
                                break;
                                //switch control between present Player ships
                            case SDLK_p:
                                player = fmod( player+1, players.size() );
                                break;
                            //test code to make sure the health bar is rendering correctly
                            //It lowers the players health if you press the K key     
                            case SDLK_k:
                                players[player]->takeDamage(10);
                                break;
                            //case SDLK_8:
                                //SOUND_ON = !SOUND_ON;
                                //break;
                            case SDLK_9:
                                Mix_PlayMusic( music, -1);
                                break;
                            case SDLK_0:    
                                Mix_PauseMusic(); 
                                break;
                            case SDLK_3:    
                                players[player]->weapons_upgrade(); 
                                break;

                        }
                    }
                }

                const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
                //handle actions based on current key state
                players[player]->handle_keystate(currentKeyStates);

                //Move the ship
                //player.update();
                for( uint i = 0; i<objects.size(); i++ )
                {
                    if( objects[i]->is_dead() )
                    {
                        //delete objects[i]; //this currently causes bugs
                        objects.erase( objects.begin()+i );
                        i--;
                    } else
                        objects[i]->update();
                }

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
