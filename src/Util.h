#ifndef _UTIL_H
#define _UTIL_H

#include <iostream>
#include <string>
#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#endif

void toggle_fullscreen(SDL_Window *win);

double distanceSquared( int x1, int y1, int x2, int y2 );

void logSDLError(std::ostream &os, const std::string &msg);

//---
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

#endif
