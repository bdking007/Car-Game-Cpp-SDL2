#ifndef CAR_H
#define CAR_H

// macros for direction
#define UP 1
#define LEFT 2
#define RIGHT 3
#define DOWN 4

#include "Game.h"

class Car // class that handles the player car
{
    public:
        Car(); // ctro
        virtual ~Car(); // dtor
        bool loadCar(std::string);  // function to load car

        void moveCar(int);  // function to move car
        void drawCar();  // car drawing function
        void handleCarEvents(const SDL_Event& evnt); // function to handle car events

        int xSpeed; // speed along x-axis
        int ySpeed;  // speed along y-axis
        int velocity;  // velocity of car in any direction
        SDL_Rect carPos;  // position of car on screen

    protected:

    private:

        SDL_Rect carBounds; // bounds of car, to avoid going out of boundry
        SDL_Texture *carTexture; // texture to store car image
};

#endif // CAR_H
