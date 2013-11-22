#ifndef _LEVEL_H
#define _LEVEL_H

//#include
#include "Planet.h"
#include "Asteroid.h"
#include "Alien.h"
#include <iostream>
#include <string>
#include <vector> 

class Level
{
    public:
        //Initializes variables
        Level();

        std::vector<Object*> world;

        //Deallocates memory
        ~Level();

    private:
    	//this is located in the constants.
        int width, height;

};

#endif
