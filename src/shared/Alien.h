#ifndef _ALIEN_H
#define _ALIEN_H

#include "Ship.h"

class Alien : public Ship
{
    public:
        //Initializes variables
        Alien(float xp = 0.0, float yp = 0.0, float ang = 0.0 );

        Object* clone() { return new Alien(*this); }

        //Deallocates memory
        //~Alien();

    private:

};

#endif
