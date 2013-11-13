/*This source code was extracted from a tutorial source file from lazyfoo.net which had the following 
 * copyright notice at the top:*/
/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
 * and may not be redistributed without written permission.*/

#ifndef _COLLISION_H
#define _COLLISION_H

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#endif
#include <string>

#include "Constants.h"
#include "Util.h"

//Circle/Circle collision detector
bool checkCollision( Circle& a, Circle& b );

//Circle/Box collision detector
bool checkCollision( Circle& a, SDL_Rect& b );

//Box/Box collision detector
bool checkCollision( SDL_Rect a, SDL_Rect b );

//Calculates distance squared between two points
double distanceSquared( int x1, int y1, int x2, int y2 );

#endif
