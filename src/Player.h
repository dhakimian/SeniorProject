#ifndef _PLAYER_H
#define _PLAYER_H

#include "Ship.h"

class Player : public Ship
{
    public:
        //Constructor: initializes the variables
        Player(float xp = (float) SCREEN_WIDTH / 2, float yp = (float) SCREEN_HEIGHT / 2, float ang=0.0 );

        //handle actions based on current key state
        void handle_keystate( const Uint8* currentKeyStates );

        //client code: render the ship
        void render( int x, int y, float ang );

    private:
        //variables telling whether certain keys are pushed. Includes both wasd and updownleftright.
        bool upKey;
        bool downKey;
        bool leftKey;
        bool rightKey;
        bool strafeLeft;
        bool strafeRight;

};
#endif
