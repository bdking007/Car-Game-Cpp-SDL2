#include "gameBackground.h"

gameBackground::gameBackground()
{
    //ctor  assigns defaults
    backgroundTexture=nullptr;

    backgroundClip={0,338,332,300}; // default background clip
}

gameBackground::~gameBackground()
{
    //dtor  free memory
    SDL_DestroyTexture(backgroundTexture);   backgroundTexture=nullptr;
}

bool gameBackground::loadBackground(string path) // load backgroud image from path provided
{
    backgroundTexture=Game::loadTexture(path.c_str(),255,255,255); //load image
    // handle loading of image
    if(!backgroundTexture)  return false;
    else                    return true;
}

void gameBackground::drawBackground() // draw our background
{
    SDL_RenderCopy(Game::gameRenderer,backgroundTexture,&backgroundClip,&Game::gameBoundry);
}

void gameBackground::scrollBackground()  // scrolls our background
{
    backgroundClip.y-=scrollSpeed; //move the clip
    if(backgroundClip.y<=0)  // check for out of bounds condition
        backgroundClip.y=338;
}

/* this is end of gameBackground class */
