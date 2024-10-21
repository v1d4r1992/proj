#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_audio.h>
#include <stdio.h>
#include "Player.h"
#include "Map.h"




int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Nie można zainicjować SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Sesja",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          800, 600,
                                          SDL_WINDOW_FULLSCREEN);
    if (!window) {
        printf("Nie można utworzyć okna: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }


    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(renderer, 800, 600);
    if (!renderer) {
        printf("Nie można utworzyć renderera: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);



    SDL_Rect camera = { 0, 0, 1080, 600 };
    struct Player Hero;
    unsigned int lastTime = SDL_GetTicks();
    float deltaTime = 0.0f;

    SDL_Surface* tempImg = IMG_Load("hero.png");
    InitPlayer(&Hero,renderer,tempImg);
    SDL_FreeSurface(tempImg);

    SDL_Surface* paperPileSheet = IMG_Load("paperstack.png");
    SDL_Surface* holeSheet = IMG_Load("Hole.png");
    tempImg = IMG_Load("Wall.png");
    struct Map map;
    InitMap(&map,renderer,tempImg,paperPileSheet,holeSheet);
    SDL_FreeSurface(holeSheet);
    SDL_FreeSurface(tempImg);



    SDL_Event event;
    int running = 1;
    while (running) {
 
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0; 
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f; 
        lastTime = currentTime;

   
     
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
        SDL_RenderClear(renderer);

        camera.x = -Hero.Dest.x;
        camera.w = 1080 - camera.x;
        
        SDL_RenderSetViewport(renderer, &camera);
        UpdatePlayer(&Hero,deltaTime);
        UpdateMap(&map,&Hero);
        DrawMap(&map,renderer);

 
        DrawPlayer(&Hero,renderer);
   

        SDL_RenderPresent(renderer);  

        SDL_Delay(16); 


    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}