#include "Util.h"

void toggle_fullscreen(SDL_Window *win) {
        if (SDL_GetWindowFlags(win) & SDL_WINDOW_FULLSCREEN)
                    SDL_SetWindowFullscreen(win, SDL_FALSE);
            else
                        SDL_SetWindowFullscreen(win, SDL_TRUE);
}

double distanceSquared( int x1, int y1, int x2, int y2 )
{
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    return deltaX*deltaX + deltaY*deltaY;
}

int randBetween( int n1, int n2 )
{
    if( n1 == n2 )
        return n1;
    else if( n1 < n2 )
        return ( rand() % (n2-n1+1) ) + n1 ;
    else {
        std::cerr<<"randBetween: first arg must be less then second arg"<<std::endl;
        return 0;
    }

}

float frandBetween( int n1, int n2 )
{
    return (float)randBetween( n1, n2 );
}

std::vector<IPaddress>::iterator find(
        std::vector<IPaddress>::iterator first,
        std::vector<IPaddress>::iterator last,
        const IPaddress& val
        )
{
  while (first!=last) {
    if ((*first).host==val.host && (*first).port==val.port) return first;
    ++first;
  }
  return last;
}

/**
 * Log an SDL error with some error message to the output stream of our choice
 * @param os The output stream to write the message too
 * @param msg The error message to write, format will be msg error: SDL_GetError()
 */
void logSDLError(std::ostream &os, const std::string &msg){
    os << msg << " error: " << SDL_GetError() << std::endl;
}

/**
 * Loads an image into a texture on the rendering device
 * @param file The image file to load
 * @param ren The renderer to load the texture onto
 * @return the loaded texture, or nullptr if something went wrong.
 */
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
    SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
    if (texture == nullptr)
        logSDLError(std::cout, "LoadTexture");
    return texture;
}

/**
 * Draw an SDL_Texture to an SDL_Renderer at position x, y, with some desired
 * width and height
 * @param tex The source texture we want to draw
 * @param rend The renderer we want to draw too
 * @param x The x coordinate to draw too
 * @param y The y coordinate to draw too
 * @param w The width of the texture to draw
 * @param h The height of the texture to draw
 */
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
    //Setup the destination rectangle to be at the position we want
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(ren, tex, NULL, &dst);
}

/**
 * Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
 * the texture's width and height
 * @param tex The source texture we want to draw
 * @param rend The renderer we want to draw too
 * @param x The x coordinate to draw too
 * @param y The y coordinate to draw too
 */
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
    int w, h;
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    renderTexture(tex, ren, x, y, w, h);
}

