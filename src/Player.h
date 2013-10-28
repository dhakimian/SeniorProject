#ifndef _PLAYER_H
#define _PLAYER_H

#include "Ship.h"

class Player : public Ship
{
    public:
        //Constructor: initializes the variables
        Player(float xp = (float) SCREEN_WIDTH / 2, float yp = (float) SCREEN_HEIGHT / 2, float ang=0.0 );

        //client code: render the ship
        void render( int x, int y, float ang, const Uint8* currentKeyStates );

};
#endif
