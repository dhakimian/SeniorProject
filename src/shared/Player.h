#ifndef _PLAYER_H
#define _PLAYER_H

#include "Ship.h"

class Player : public Ship
{
    public:
        //Constructor: initializes the variables
        //Player(int teamnumber=1, float xp = (float) SCREEN_WIDTH / 2, float yp = (float) SCREEN_HEIGHT / 2, float ang=0.0 );
        Player(int teamnumber = randBetween(1,4),
                float xp = frandBetween(0,LEVEL_WIDTH),
                float yp = frandBetween(0,LEVEL_HEIGHT),
                float ang = frandBetween(0,360) );

        //handle actions based on current key state
        void handle_keystate( const Uint8* currentKeyStates );
        void handle_keystate( Keystate keystate );

        //client code: render the ship
        void render( int x, int y, float ang, bool centered=true );

        void update();

        void respawn();

        Object* clone() { return new Player(*this); }

    private:

        int Respawn_time, respawn_time_rem;

        //variables telling whether certain keys are pushed. Includes both wasd and updownleftright.
        bool upKey;
        bool downKey;
        bool leftKey;
        bool rightKey;
        bool strafeLeft;
        bool strafeRight;
        bool shootKey;
        int TEX_TEAM_INDEX_BODY;
        int TEX_TEAM_INDEX_L;
        int TEX_TEAM_INDEX_R;

};
#endif
