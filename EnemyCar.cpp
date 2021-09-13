#include "EnemyCar.h"

// static members definition
int EnemyCar::maxSpeed=3;
int EnemyCar::minSpeed=1;
SDL_Texture* EnemyCar::enemyCarTextures=nullptr;

EnemyCar::EnemyCar()
{
    //ctor
    // clips for all the enemy cars
    SDL_Rect sources[7];
    sources[0]={410,270,475-410,400-270};
    sources[1]={475,270,475-410,400-270};
    sources[2]={540,270,475-410,400-270};
    sources[3]={370,0,460-370,230};
    sources[4]={470,0,530-470,160};
    sources[5]={540,0,600-540,160};
    sources[6]={610,0,680-610,160};

    enemyCarTextures=Game::loadTexture("assets/images/carSprites.png",255,255,255); // load cars image

    int t=rand()%(6+1) + 0;  // select a random enemy car
    int xpos=rand()%(3)+1;  // its x-position
    // modify its position to render them perfectly on three roads of game
    if(xpos==1)  xpos=120;
    else if(xpos==2)  xpos=180;
    else if(xpos==3)  xpos=240;
    else xpos=120;

    // select a random speed for car within min and max speed
    carSpeed=rand()%(maxSpeed-minSpeed+1)+minSpeed;

    srcRect=sources[t]; // select clip according to randomly selected car style
    destRect.x=xpos;   destRect.w=25;  // define its width and x-Pos in destination rectangle
    // vary height of car according to style of car chosen
    if(t<=2)  // for small car
        destRect.h=50;
    else if(t==3)  // for trucks
        destRect.h=80;
    else
        destRect.h=60;  // for mid-range cars
    destRect.y=Game::gameBoundry.y-destRect.h;  // print the car behind start point, and then let it come on screen,effect looks nice
}

EnemyCar::~EnemyCar()
{
    //dtor
    SDL_DestroyTexture(enemyCarTextures);  enemyCarTextures=nullptr;  // free memory allocated for enemy-car stuff

}

// update cars position
bool EnemyCar::updateEnemyCar()
{
    destRect.y+=carSpeed;
    // if it went out of screen from bottom , return false
    if(destRect.y>=Game::gameBoundry.y+Game::gameBoundry.h)
        return false;
    else // otherwise draw it
    {
        drawEnemyCar();
        return true;
    }
}

// function to draw enemy-car, on its updated position
void EnemyCar::drawEnemyCar()
{
    SDL_RenderCopy(Game::gameRenderer,enemyCarTextures,&srcRect,&destRect);
}

/* this is end of EnemyCar class */
