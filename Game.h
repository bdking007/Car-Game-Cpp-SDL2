#ifndef GAME_H
#define GAME_H

// macros for screen dimensions
#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 400

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Car.h"
#include "gameBackground.h"
#include "EnemyCar.h"

using namespace std;


class Game // class that handles our Game
{
    public:

        Game(); // ctor
        virtual ~Game(); // dtor
        void run(); // runner of game

        // static members
        static SDL_Renderer *gameRenderer;
        static TTF_Font *font;
        static  SDL_Rect gameBoundry;

        static SDL_Texture *loadTexture(string,int,int,int);
        static bool checkCollision(SDL_Rect a,SDL_Rect b);
        static SDL_Texture *loadText(string,SDL_Color);
        static void fatalError(string,bool);



    protected:

    private:

        // private member functions
        bool initSystem();
        void cleanSystem();
        bool loadFiles();
        void updateScreen();
        void renderChanges();
        void gameLoop();
        void handleGameEvents();
        void printScore();

        // private data members
        int score;
        SDL_Window *gameWindow;
        SDL_Surface *gameSurface;
        SDL_Texture *gameOverTexture;
        Mix_Music *bgm;
        Mix_Chunk *gameOverEffect;
        Mix_Chunk *outEffect;
        SDL_Event gameEvents;
        bool gameOn;
        bool playStart;
};

#endif // GAME_H
