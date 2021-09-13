#ifndef ENEMYCAR_H
#define ENEMYCAR_H

#include "Game.h"


class EnemyCar  // class that defines our enemy car
{
    public:
        EnemyCar();
        virtual ~EnemyCar();

        SDL_Rect destRect; // indivisual position of car on screen
        int carSpeed;  // indivisual speed of enemy car

        // static members
        static int maxSpeed,minSpeed;  // min and max speed of all class, static
        static SDL_Texture *enemyCarTextures; // image of all cars, in single image, static


        void drawEnemyCar();  // draw enemy car
        bool updateEnemyCar(); // update position of car


    protected:

    private:

        SDL_Rect srcRect;  // source clip of car to crop from image of all cars

};

#endif // ENEMYCAR_H
