#ifndef _UTIL_H
#define _UTIL_H

#include <iostream>
#include <string>
#include <vector>
#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_net/SDL_net.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_net.h>
#endif

void toggle_fullscreen(SDL_Window *win);

//Calculates distance squared between two points
double distanceSquared( int x1, int y1, int x2, int y2 );

//return a random number between n1 and n2 inclusively
int randBetween(int n1, int n2);
//return the int as a float so you don't have put (float) before randBetween (7->1 characters)
float frandBetween(int n1, int n2);

//overload of <algorithm>'s find to handle IPaddress struct which doesn't have comparison operators
std::vector<IPaddress>::iterator find(
        std::vector<IPaddress>::iterator first,
        std::vector<IPaddress>::iterator last,
        const IPaddress& val
        );

void logSDLError(std::ostream &os, const std::string &msg);

#endif
