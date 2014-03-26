#ifndef _PLAYER_H
#define _PLAYER_H
#include "Ship.h"

#ifdef __APPLE__
#include <SDL2_net/SDL_net.h>
#else
#include <SDL_net.h>
#endif

class Player : public Ship
{
    public:
        //Constructor: initializes the variables
        Player( Uint16 controllerport=0,
                int teamnumber = randBetween(1,4),
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

        Uint16 get_controller();

        Object* clone() { return new Player(*this); }

        /*
        //port number (SDL_Net IPaddress.port) of client controlling this ship
        Uint16 controller;

        //variables telling whether certain keys are pushed. Includes both wasd and updownleftright.
        bool upKey;
        bool downKey;
        bool leftKey;
        bool rightKey;
        bool strafeLeft;
        bool strafeRight;
        bool shootKey;
        */

    private:

        //How many cycles to wait after ship is destroyed before you spawn again
        int Respawn_time, respawn_time_rem;

        /*
        //port number (SDL_Net IPaddress.port) of client controlling this ship
        Uint16 controller;

        //variables telling whether certain keys are pushed. Includes both wasd and updownleftright.
        bool upKey;
        bool downKey;
        bool leftKey;
        bool rightKey;
        bool strafeLeft;
        bool strafeRight;
        bool shootKey;
        */

};

// http://stackoverflow.com/questions/589985/vectors-structs-and-stdfind
struct find_controller : std::unary_function<Player*, bool> {
    IPaddress addr;
    find_controller(IPaddress addr):addr(addr) { }
    bool operator()(Player* const& p) const {
        return (p->get_controller() == addr.port );
    }
};
#endif
