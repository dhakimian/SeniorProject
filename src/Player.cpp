#include "Player.h"

//the textures that will be used
LTexture shipTex;
LTexture thr_bTex;
LTexture thr_lTex;
LTexture thr_rTex;
LTexture thr_fTex;

Player::Player()
{
    xPos = (float) SCREEN_WIDTH / 2;
    yPos = (float) SCREEN_HEIGHT / 2;

    xVel = 0.0;
    yVel = 0.0;

    Angle = 0.0;

    rotVel = 0.0;
}

/*
   Player::~Player()
   {

   }
   */

void Player::handleEvent( SDL_Event& e )
{
    double ang = M_PI * Angle;
    ang = ang / 180;

    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    if( currentKeyStates[ SDL_SCANCODE_UP ] )
    {
        xVel += SHIP_ACCEL * sin(ang);
        yVel -= SHIP_ACCEL * cos(ang);
    }
    if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
    {
        xVel -= SHIP_REV_ACCEL * sin(ang);
        yVel += SHIP_REV_ACCEL * cos(ang);
    }
    if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
    {
        rotVel -= SHIP_ROT_ACCEL;
    }
    if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
    {
        rotVel += SHIP_ROT_ACCEL;
    }
}

void Player::move()
{
    //Move the ship left or right
    xPos += xVel;

    //If the ship went too far to the left
    if( xPos < 0 )
    {
        xPos = 0.0;
        xVel = 0.0;
    }
    //If the ship went too far to the right
    if ( xPos + SHIP_WIDTH > SCREEN_WIDTH )
    {
        xPos = (float) SCREEN_WIDTH - SHIP_WIDTH;
        xVel = 0.0;
    }

    //Move the ship up or down
    yPos += yVel;

    //If the ship went too far up
    if( yPos < 0 )
    {
        yPos = 0.0;
        yVel = 0.0;
    }
    //If the ship went too far down
    if( yPos + SHIP_HEIGHT > SCREEN_HEIGHT )
    {
        yPos = (float) SCREEN_HEIGHT - SHIP_HEIGHT;
        yVel = 0.0;
    }

    Angle += rotVel;
}

void Player::render(SDL_Renderer* ren)
{
    //Render the the ship
    shipTex.render( ren, (int)xPos, (int)yPos, NULL, Angle );

    SDL_Point center;
    center.x = (shipTex.getWidth() / 2);
    center.y = (shipTex.getHeight() / 2);

    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    if( currentKeyStates[ SDL_SCANCODE_UP ] )
        thr_bTex.render( ren, (int)xPos, (int)yPos, NULL, Angle, &center );
    if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
        thr_lTex.render( ren, (int)xPos, (int)yPos, NULL, Angle, &center );
    if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
        thr_rTex.render( ren, (int)xPos, (int)yPos, NULL, Angle, &center );
    //if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
    //thr_fTex.render( ren, (int)xPos, (int)yPos, NULL, Angle, &center );
}

bool Player::loadMedia(SDL_Renderer* ren)
{
    //Loading success flag
    bool success = true;

    //Load ship texture
    if( !shipTex.loadFromFile( ren, "media/ship.png" ) ) {
        printf( "Failed to load ship texture!\n" );
        success = false;
    }
    //Load thrust textures
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
    /*
       if( !thr_fTex.loadFromFile( ren, "media/ship_thr_f.png" ) ) {
       printf( "Failed to load front thrust texture!\n" );
       success = false;
       }
       */

    return success;
}

void Player::freeMedia()
{
    shipTex.free();
    thr_bTex.free();
    thr_lTex.free();
    thr_rTex.free();
    //thr_fTex.free();
}
