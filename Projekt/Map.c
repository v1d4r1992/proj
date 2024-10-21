
#include "Map.h"
#ifndef PLAYER_H
#include "Player.h"
#endif
#include <stdlib.h>
#include <time.h>  

void InitTilesLines(struct Map* map,int layer,int spritesheetline, int yOffset,int tileCount)
{
    srand(time(NULL)); 

    int elementCounts = sizeof(map->SpriteMap)/sizeof(map->SpriteMap[0])/3;
    printf("%d\n",elementCounts);
    int x= layer*elementCounts;
    int posXIter=0;
    for(;x<layer*elementCounts+elementCounts;x++)
    {
        map->SpriteMap[x].SpriteType =1;
        map->SpriteMap[x].SRC.x=rand() % tileCount*32; 
        map->SpriteMap[x].SRC.y=spritesheetline*32;
        map->SpriteMap[x].SRC.h=32;
        map->SpriteMap[x].SRC.w=32;
        map->SpriteMap[x].Position.x = posXIter*192;
        map->SpriteMap[x].Position.y = yOffset;
        map->SpriteMap[x].Position.w = 192;
        map->SpriteMap[x].Position.h = 192;
        posXIter++;
    }
}
void InitMap(struct Map* map,SDL_Renderer*renderer,SDL_Surface* mapSprites,SDL_Surface* paperStackSprites,SDL_Surface* holeSpriteSheet)
{
    
    map->SpriteSheet = SDL_CreateTextureFromSurface(renderer,mapSprites);
    map->Dest.x=0;
    map->Dest.y=0;
    map->Dest.w=32;
    map->Dest.h=32;

    InitTilesLines(map,2,0,600-192-100,4);
    InitTilesLines(map,1,2,120,2); 
    InitTilesLines(map,0,1,600-192-35,1); 



    InitObstacles(map,renderer,paperStackSprites,holeSpriteSheet);
}
void ResetMap(struct Map* map,SDL_Renderer*renderer)
{
    
    map->Dest.x=0;
    map->Dest.y=0;
    map->Dest.w=32;
    map->Dest.h=32;

    InitTilesLines(map,2,0,600-192-100,4);
    InitTilesLines(map,1,2,120,2); 
    InitTilesLines(map,0,1,600-192-35,1); 



    ResetObstacles(map,renderer);
}
void ResetObstacles(struct Map* map,SDL_Renderer*renderer)
{

    int i=0;
    for(i=0;i<2;i++)
    {
        map->PaperStacks[i].Position.x=450;
        map->PaperStacks[i].Position.y=360;
        map->PaperStacks[i].Position.w=128;
        map->PaperStacks[i].Position.h=128+64;
        map->PaperStacks[i].PlayAnim=false;
        map->PaperStacks[i].IsEnabled=true;
        map->PaperStacks[i].MaxFrames = 3;
        int f=0;
        for(f=0;f<3;f++)
        {
            map->PaperStacks[i].AnimFrames[f].x=f*32;
            map->PaperStacks[i].AnimFrames[f].y=0;
            map->PaperStacks[i].AnimFrames[f].w=32;
            map->PaperStacks[i].AnimFrames[f].h=32;
        }
        map->PaperStacks[i].CurrentFrameIndex=0;
        map->PaperStacks[i].CurentFrame=map->PaperStacks[i].AnimFrames[0];
    }
}

void ObstaclePaperStackUpdateFunc(struct ObstacleStruct* thisArg, struct Player* player)
{
     if(thisArg->IsEnabled==true && (thisArg->Position.x<player->Dest.x+(player->Dest.w/5)))
        {
            if(player->isAttack || player->isJumping)
            {
                thisArg->PlayAnim=true;
                thisArg->IsEnabled=false;
                
            }else{

               player->isAlive=false;
               printf("Player Dead");
            }
      
        }
}


void ObstacleHoleUpdateFunc(struct ObstacleStruct* thisArg, struct Player* player)
{
     if(thisArg->IsEnabled==true && player->Dest.x+player->Dest.w > thisArg->Position.x)
        {
            if(player->isAttack)
            {
                thisArg->PlayAnim=true;
                thisArg->IsEnabled=false;
            }else{
               printf("Player Dead");
               player->isAlive=false;
            }
      
        }
}


void InitObstacles(struct Map* map,SDL_Renderer*renderer,SDL_Surface* paperStackSprites,SDL_Surface* holeSpriteSheet)
{
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer,holeSpriteSheet);
    int i=0;
    for(i=0;i<3;i++)
    {
        map->PaperStacks[i].SpriteSheet = tex;
        map->PaperStacks[i].Position.x=450;
        map->PaperStacks[i].Position.y=600-192-35;
        map->PaperStacks[i].Position.w=128;
        map->PaperStacks[i].Position.h=128+64;
        map->PaperStacks[i].PlayAnim=true;
        map->PaperStacks[i].IsEnabled=true;
        map->PaperStacks[i].MaxFrames = 11;
       // map->PaperStacks[i].func_ptr = ObstacleHoleUpdateFunc;

        int f=0;
        for(f=0;f<map->PaperStacks[i].MaxFrames;f++)
        {
            map->PaperStacks[i].AnimFrames[f].x=f*32;
            map->PaperStacks[i].AnimFrames[f].y=0;
            map->PaperStacks[i].AnimFrames[f].w=32;
            map->PaperStacks[i].AnimFrames[f].h=32;
        }
        map->PaperStacks[i].CurrentFrameIndex=0;
        map->PaperStacks[i].CurentFrame=map->PaperStacks[i].AnimFrames[0];
    }

    tex = SDL_CreateTextureFromSurface(renderer,paperStackSprites);
    for(i=0;i<2;i++)
    {
        map->PaperStacks[i].SpriteSheet = tex;
        map->PaperStacks[i].Position.x=450;
        map->PaperStacks[i].Position.y=360;
        map->PaperStacks[i].Position.w=128;
        map->PaperStacks[i].Position.h=128+64;
        map->PaperStacks[i].PlayAnim=false;
        map->PaperStacks[i].IsEnabled=true;
        map->PaperStacks[i].MaxFrames = 3;

        //map->PaperStacks[i].func_ptr = ObstaclePaperStackUpdateFunc;

        int f=0;
        for(f=0;f<3;f++)
        {
            map->PaperStacks[i].AnimFrames[f].x=f*32;
            map->PaperStacks[i].AnimFrames[f].y=0;
            map->PaperStacks[i].AnimFrames[f].w=32;
            map->PaperStacks[i].AnimFrames[f].h=32;
        }
        map->PaperStacks[i].CurrentFrameIndex=0;
        map->PaperStacks[i].CurentFrame=map->PaperStacks[i].AnimFrames[0];
    }
}
void DrawObstacles(struct ObstacleStruct* paper, SDL_Renderer* SDL_Renderer)
{
        SDL_RenderCopyEx(SDL_Renderer,
            paper->SpriteSheet,
            &paper->CurentFrame,
            &paper->Position,
            0,
            NULL,
            SDL_FLIP_NONE);
}



void UpdateMap(struct Map* map,struct Player* player)
{
   
    int paper=0;
    for(paper=0;paper<5;paper++)
    {
        struct ObstacleStruct* paperStack =  &map->PaperStacks[paper];
       

        ObstaclePaperStackUpdateFunc(paperStack,player);
 //       if(paperStack->func_ptr!=NULL)
         //   paperStack->func_ptr(paperStack,player);

        if(!paperStack->PlayAnim) continue;

        paperStack->animTimer+=60;
        if(paperStack->animTimer>400)
        {
            paperStack->CurrentFrameIndex++;

            if(paperStack->CurrentFrameIndex >paperStack->MaxFrames-1) paperStack->CurrentFrameIndex=0;

            paperStack->animTimer =0;
            paperStack->CurentFrame = paperStack->AnimFrames[paperStack->CurrentFrameIndex];
        }
    }
}
void DrawMap(struct Map* map, SDL_Renderer* SDL_Renderer)
{
        int x= 0;
        for(x=0;x<sizeof(map->SpriteMap)/sizeof(map->SpriteMap[0]);x++)
        {

            SDL_RenderCopyEx(SDL_Renderer,
                            map->SpriteSheet,
                            &map->SpriteMap[x].SRC,
                            &map->SpriteMap[x].Position,
                            0,
                            NULL,
                            SDL_FLIP_NONE);
        }
      
        for(x=0;x<5;x++)
        {
            DrawObstacles(&map->PaperStacks[x],SDL_Renderer);
        }
}
void SetResetMap(struct Map* map,SDL_Renderer*renderer)
{
    ResetMap(map,renderer);
}