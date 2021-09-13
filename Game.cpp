#include "Game.h"

Car ourCar;  // instance for our Car
gameBackground background;  // background instance to manipulate and scroll background
EnemyCar* enmCars[100];  // pointers to EnemyCars fro dynamic memory allocation
int currentEnmCars;     // to manipulate no of enemycars as per current level


Game::Game()
{
    // ctor initialize all pointer to nullptr
    gameSurface=nullptr;   gameWindow=nullptr;  gameOverTexture=nullptr;
    bgm=nullptr;   gameOverEffect=nullptr;   outEffect=nullptr;

    // bools to determine state of game
    gameOn=false;   playStart=false;

    for(int i=0;i<100;i++)
        enmCars[i]=nullptr;

    // init Game status
    score=0;
    currentEnmCars=3;

    // seed value in srand() for generating random numbers
    srand(time(NULL));
}

Game::~Game()
{
    //dtor assign all pointers with nullptr at end of program
    gameSurface=nullptr;    gameRenderer=nullptr;
    gameWindow=nullptr;   font=nullptr;   gameOverTexture=nullptr;
    bgm=nullptr;   gameOverEffect=nullptr;  outEffect=nullptr;
}

// declaration of static data members
SDL_Renderer *Game::gameRenderer=nullptr;  // renderer of all game objects
TTF_Font *Game::font=nullptr;   // font used for text
SDL_Rect Game::gameBoundry={0,0,SCREEN_WIDTH,SCREEN_HEIGHT};  // boundry of game

// defination of all static member functions
void Game::fatalError(string error,bool closeProgram)  // to handle all types of program errors
{
    cout<<"Error Occured : "<<error<<endl;
    if(closeProgram)  // if closeprogram...end program
    {
        Game g;
        g.cleanSystem();  //  cleansSystem.. i.e., deallocate heap memory
        cin.get();
        exit(-1);
    }
}

bool Game::checkCollision(SDL_Rect a,SDL_Rect b)  // function to check all Box-Box collisions
{
    if(a.x+a.w<b.x)
        return false;
    else if(a.y+a.h<b.y)  /* axix line collision detection used */
        return false;
    else if(b.x+b.w<a.x)
        return false;
    else if(b.y+b.h<a.y)
        return false;
    else
        return true;
}

SDL_Texture* Game::loadTexture(string path,int r,int g,int b) // function to load textures ( images )
{
    SDL_Surface *tempImgSurface=IMG_Load(path.c_str()); // load image on surface
    SDL_Texture *retTexture=nullptr; // texture to hold return texture
    if(tempImgSurface==nullptr) // if image not loaded, prompt on Console
    {
        cout<<"Image not found : "<<path<<endl;
    }
    else
    {
        SDL_SetColorKey(tempImgSurface,SDL_TRUE,SDL_MapRGB(tempImgSurface->format,r,g,b)); // colorkey surface
        retTexture=SDL_CreateTextureFromSurface(gameRenderer,tempImgSurface); // converting surface to texture
        SDL_FreeSurface(tempImgSurface);   tempImgSurface=nullptr; // deallocate surface, none of use
    }
    return retTexture; //  return loaded image as texture
}

SDL_Texture* Game::loadText(string text,SDL_Color color) // function to load text
{
    SDL_Surface *textSurface=TTF_RenderText_Solid(Game::font,text.c_str(),color);  // surface to store text
    SDL_Texture *ret=SDL_CreateTextureFromSurface(gameRenderer,textSurface); // convert surface to texture
    SDL_FreeSurface(textSurface);   textSurface=nullptr; // deallocate surface
    return ret;  // return text as texture
}

// entry point of our real game
void Game::run()
{
    if(!initSystem()) // initialize system
    {
        cout<<"Error in INITIALIZING System "<<endl; cin.get(); return;
    }
    if(!loadFiles()) // load files
    {
        cout<<"Error in Loading Files "<<endl;  cin.get();  return;
    }
    gameOn=true; // turn the game on after System Inited

    Mix_PlayMusic(bgm,-1);  // play BGM
    while(gameOn)   // it was desinged so to add menu..but I skipped it, don't confuse
    {
        gameLoop();  // call main Game loop
    }

    // deallocate all the enemy cars dynamic memory, if exist
    for(int i=0;i<100;i++)
    {
        if(enmCars[i])
            delete enmCars[i];
        enmCars[i]=nullptr;
    }
    Mix_HaltMusic();  // stop BGM after game Over
    Mix_PlayChannel(-1,gameOverEffect,1);  // play gameOver effect
    SDL_SetRenderDrawColor(gameRenderer,255,255,255,255);  // change renderer draw color
    SDL_RenderClear(gameRenderer);  // clear screen with renderers draw color
    SDL_Rect temp={0,0,SCREEN_WIDTH,400}; // temp rectangle to denote destination area of game over image
    SDL_RenderCopy(gameRenderer,gameOverTexture,nullptr,&temp);

    stringstream ss("");  ss<<" Your Score : "<<score<<" "; // stringstream used to convert our score in a string
    SDL_Color color={0,0,0,255};  // color of text
    SDL_Texture *text=loadText(ss.str(),color);  // loading text
    SDL_Rect scoreRect={100,400,200,100};  // rect for area of score board
    SDL_RenderCopy(gameRenderer,text,nullptr,&scoreRect);  // draw scoreboard

    SDL_RenderPresent(gameRenderer);  // update screen with all changes made

    SDL_Delay(3000);  // delay gameOver screen for 3 seconds

    cleanSystem(); // deallocate all memory and shut the system down
}

bool Game::initSystem() // System initializing function
{
    SDL_Init(SDL_INIT_EVERYTHING); // init SDL
    IMG_Init(IMG_INIT_PNG);  // init SDL_image
    TTF_Init();  // init True type Font
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048); // init audio

    // create game widow
    gameWindow=SDL_CreateWindow("Bit my Car",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    // attach a surface to it
    gameSurface=SDL_GetWindowSurface(gameWindow);
    // attach our game renderer to window, and init it
    gameRenderer=SDL_CreateRenderer(gameWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // set render draw color, default one
    SDL_SetRenderDrawColor(gameRenderer,255,255,255,255);

    return true; // I have written all boundry cases code and returning false, bt once I succesfully run it,
     // i removed it and simply returning true for succesful initialization
}

// this function avoid memory leaks by deallocating all DAM of heap
void Game::cleanSystem()
{
    // deallocate memory
    SDL_FreeSurface(gameSurface);
    SDL_DestroyRenderer(gameRenderer);
    Mix_FreeChunk(gameOverEffect);
    Mix_FreeChunk(outEffect);
    Mix_FreeMusic(bgm);
    TTF_CloseFont(font);
    SDL_DestroyWindow(gameWindow);
    SDL_DestroyTexture(gameOverTexture);

    Mix_Quit();  TTF_Quit();  IMG_Quit();  SDL_Quit(); //  close all SDL and its extension
}

// function to load all images , audio and font files
bool Game::loadFiles()
{
    font=TTF_OpenFont("assets/fonts/neuropol.ttf",28);
    bgm=Mix_LoadMUS("assets/music/bgm.mp3");
    gameOverEffect=Mix_LoadWAV("assets/music/gameOverEffect.wav");
    outEffect=Mix_LoadWAV("assets/music/outEffect.wav");
    gameOverTexture=loadTexture("assets/images/gameOver.png",255,255,255);
    // if any of initialization failed
    if(!font || !ourCar.loadCar("assets/images/carSprites.png") || !background.loadBackground("assets/images/raceRoad.png")
       || !gameOverTexture || !bgm)
        return false;
    return true;
}

// event handler of game
void Game::handleGameEvents()
{
    while(SDL_PollEvent(&gameEvents)) // while Event Queue is not empty, handle events in queue
    {
        switch(gameEvents.type)  // perform action according to event type
        {
            case SDL_QUIT :  // if X button of window pressed, close program
                gameOn=false;
                break;
        }
        ourCar.handleCarEvents(gameEvents); // handle events of our car
    }
}

// function to update screen in each frame
void Game::updateScreen()
{
    // clear screen
    SDL_SetRenderDrawColor(gameRenderer,255,255,255,255);
    SDL_RenderClear(gameRenderer);

    // scroll and draw background
    background.scrollBackground();
    background.drawBackground();


    // this loop handles all our Enemy cars
    for(int i=0;i<currentEnmCars;i++)
    {
        // check for if any of preset car is not allocated memory, allocate it memory
        if(enmCars[i]==nullptr)
        {
            enmCars[i]=new EnemyCar();
        }
        // if the car went out of screen downside,updateEnemyCar return false, then delete that car,  and increase score
        else if(!enmCars[i]->updateEnemyCar())
        {
            delete enmCars[i];   enmCars[i]=nullptr;
            score+=5;
            continue;
        }
        // if collision happened with any of cars present on screen
        else if(checkCollision(ourCar.carPos,enmCars[i]->destRect))
        {
            gameOn=false;  Mix_PlayChannel(-1,outEffect,0); // turn game of, and play lifeloss effect
            SDL_Delay(2000); // delay 2 sec
            break;
        }
    }

    if(score%100==0 && score/100>0) // if score is in multiple of hundred
    {
        score+=5;// give bonus score
        currentEnmCars++; // increase no of enemy cars on screen by 1
        EnemyCar::maxSpeed++; // increase max speed of enemy cars
    }

    ourCar.drawCar(); // draw our car, updated

    printScore(); // print score
}

// this render all the changes of screen
void Game::renderChanges()
{
    SDL_RenderPresent(gameRenderer);
}

// our game loop
void Game::gameLoop()
{
    playStart=true; // start the play
    while(playStart && gameOn) // while playing and program is running
    {
        handleGameEvents(); // handles game events
        updateScreen();  // update all changes to screen
        renderChanges(); // render all changes to screen
    }
    playStart=false; // turn the play off
}

// function to print score
void Game::printScore()
{
    // used stringstream
    stringstream ss("");  ss<<" Score : "<<score<<" ";
    SDL_Color color={255,255,255,255}; // color of score text
    SDL_Texture *text=loadText(ss.str(),color); // load text
    SDL_Rect scoreRect={0,0,80,40}; // area of score
    SDL_SetRenderDrawColor(gameRenderer,0,0,0,255); // set drawing color for scoreboard to black
    SDL_RenderFillRect(gameRenderer,&scoreRect); // draw a bar
    SDL_RenderCopy(gameRenderer,text,nullptr,&scoreRect); // print score
}

/* this is end of Game class */
