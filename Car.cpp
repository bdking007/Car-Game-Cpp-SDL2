#include "Car.h"

Car::Car()
{
    // ctor initialize all data members with default values,  and pointers to nullptr
    carTexture=nullptr;

    carPos={120,500,30,50};  xSpeed=ySpeed=0;   velocity=2;

    carBounds={110,Game::gameBoundry.y,175,Game::gameBoundry.h};
}

Car::~Car()
{
    //dtor deallocate memory of heap
    SDL_DestroyTexture(carTexture);  carTexture=nullptr; // deallocate car image memory
}

// function that loads ur car in texture
bool Car::loadCar(string path)
{
    carTexture=Game::loadTexture(path.c_str(),255,255,255); // load image
    if(!carTexture)  // if not loaded
        return false;
    else
        return true;
}

// move car in specified direction
void Car::moveCar(int dir)
{
    // i will not challenge your sense for this, self understoodable
    if(dir==LEFT)
    {
        xSpeed=-velocity;
    }
    else if(dir==RIGHT)
    {
        xSpeed=velocity;
    }
    else if(dir==UP)
    {
        ySpeed=-velocity;

    }
    else if(dir==DOWN)
    {
        ySpeed=+velocity;
    }

}

// draw our car
void Car::drawCar()
{
    SDL_Rect carSrcRect={350,270,410-350,405-270}; // crop our car image from source image

    carPos.x+=xSpeed; // add car speed along x-axis
    // check for condition of out of bounds
    if(carPos.x<carBounds.x)
        carPos.x=carBounds.x;
    else if(carPos.x+carPos.w>carBounds.x+carBounds.w)
        carPos.x=carBounds.x+carBounds.w-carPos.w;

    carPos.y+=ySpeed; // add car speed along y-axis
    // check for our of bounds condition
    if(carPos.y<carBounds.y)
        carPos.y=carBounds.y;
    else if(carPos.y+carPos.h>carBounds.y+carBounds.h)
        carPos.y=carBounds.y+carBounds.h-carPos.h;

    // draw car after moving
    SDL_RenderCopy(Game::gameRenderer,carTexture,&carSrcRect,&carPos);
}

// handles events related to our car
void Car::handleCarEvents(const SDL_Event& evnt)
{
    //evnt.key.repeat==0 ensures if a single key press happens, if multiple hapnens, handle them repeatedly
    if(evnt.type==SDL_KEYDOWN && evnt.key.repeat==0) // check for the key that is pressed
    {
        switch(evnt.key.keysym.sym) // move car accordingly to key pressed
        {
        case SDLK_LEFT :
            moveCar(LEFT);
            break;
        case SDLK_RIGHT :
            moveCar(RIGHT);
            break;
        case SDLK_UP:
            moveCar(UP);
            break;
        case SDLK_DOWN:
            moveCar(DOWN);
            break;
        }
    }

    // handle the events related to key released
    if(evnt.type==SDL_KEYUP && evnt.key.repeat==0)
    {
        // nullify the speed along the direction according to key released
        switch(evnt.key.keysym.sym)
        {
        case SDLK_LEFT :
            xSpeed=0;
            break;
        case SDLK_RIGHT:
            xSpeed=0;
            break;
        case SDLK_UP:
            ySpeed=0;
            break;
        case SDLK_DOWN:
            ySpeed=0;
            break;
        }
    }
}

/* this is end of Car class */
