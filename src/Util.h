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
//#include "Constants.h"
//#include "LTexture.h"

//class LTexture;


//LTexture shipTex;
//LTexture thr_bTex;
//LTexture thr_lTex;
//LTexture thr_rTex;
//LTexture thr_fTex;

//bool init();
//bool loadMedia();
//void close();

void toggle_fullscreen(SDL_Window *win);

void logSDLError(std::ostream &os, const std::string &msg);

//---
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

#endif
