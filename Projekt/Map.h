
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#ifndef PLAYER_H
#include "Player.h"
#endif


#define true 1
#define false 0
typedef _Bool bool;
enum ObstacleType{
    Hole=0,PaperStack=1
};

struct ObstacleStruct
{
    SDL_Rect Position;
    SDL_Rect AnimFrames[20];
    SDL_Texture* SpriteSheet;
    int AnimFrame;
    int CurrentFrameIndex;
    int MaxFrames;
    bool PlayAnim;
    SDL_Rect CurentFrame;
    float animTimer;
    bool IsEnabled;
};

struct MapElement
{
    int SpriteType;
    SDL_Rect Position;
    SDL_Rect SRC;
};

struct Map
{
    struct MapElement SpriteMap[120];
    SDL_Rect Dest;
    SDL_Texture* SpriteSheet;
    struct ObstacleStruct PaperStacks[5];
};


void InitObstacles();
void UpdateMap(struct Map* map,struct Player* player);
void InitMap(struct Map* map,SDL_Renderer*renderer,SDL_Surface* mapSprites,SDL_Surface* paperStackSprites,SDL_Surface* holeSpriteSheet);
void DrawMap(struct Map* map, SDL_Renderer* SDL_Renderer);
void DrawObstacles(struct ObstacleStruct* paper, SDL_Renderer* SDL_Renderer);

void SetResetMap(struct Map* map,SDL_Renderer*renderer);
void ResetObstacles(struct Map* map,SDL_Renderer*renderer);