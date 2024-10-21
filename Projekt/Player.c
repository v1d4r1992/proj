
#include "Player.h"
#include <stdio.h>
#include <string.h>

const float gravity = 0.15f;      
const float groundLevel = 400.0f;  

void InitPlayer(struct Player* player,SDL_Renderer*renderer,SDL_Surface* image)
{
    player->playerSprite = SDL_CreateTextureFromSurface(renderer,image);
    player->Dest.w=64+64;
    player->Dest.h = 64+64;
    player->Dest.x=0;
    player->Dest.y=0;
    player->frame=0;
    player->onGround = false;
    player->isJumping = false;
    player->isSlide = false;
    player->isAlive = true;
    player->Speed =5;
    player->VelocityX=0;
    player->VelocityY=0;


    SetUpAnimations(player);

    SetAnimationWithName(player,"Idle");
}

void UpdatePlayer(struct Player* Hero,float deltaTime)
{
        int mx=0,my=0;
        int numkeys;  
        const Uint8 *state = SDL_GetKeyboardState(&numkeys);

        if (state[SDL_SCANCODE_W]) {
           // Hero.VelocityY=-1; 
        }     
        if (state[SDL_SCANCODE_S]) {
          Hero->isSlide = true;
          Hero->ActionTimer=0.15f;
        }
        if (state[SDL_SCANCODE_A]) {
          Hero->isAttack = true;
          Hero->ActionTimer=0.15f;
        }     
        if (state[SDL_SCANCODE_D]) {
            Hero->VelocityX =1;
        }
        if (Hero->VelocityX != 0 && Hero->onGround && !Hero->isJumping &&  state[SDL_SCANCODE_SPACE]) {
            Hero->VelocityY = -3;  
            Hero->onGround = false;         
            Hero->isJumping = true;          
        }

        if(Hero->VelocityX!=0)
        {
            if(Hero->isJumping==false){
                if (Hero->isSlide && Hero->ActionTimer>0)
                {
                    SetAnimationWithName(Hero,"Slide");
                    Hero->ActionTimer-=deltaTime;
                }else if (Hero->isAttack && Hero->ActionTimer>0)
                {
                    SetAnimationWithName(Hero,"Hit");
                    Hero->ActionTimer-=deltaTime;
                }else{
                    Hero->isSlide=false;
                    Hero->isAttack = false;
                    SetAnimationWithName(Hero,"Walk");
                }
            }
            else{
                     SetAnimationWithName(Hero,"Jump");
            }
        }else
        {
            SetAnimationWithName(Hero,"Idle");
        }


  

       if (Hero->Dest.y >= groundLevel) {
            if(Hero->isAlive==true)
             Hero->Dest.y  = groundLevel;  
            Hero->onGround = true;      
            Hero->isJumping = false;      
        }

        

        if (!Hero->onGround) {
            Hero->VelocityY += gravity;
        }

        if(Hero->isAlive)
        Hero->Dest.x+=Hero->VelocityX *Hero->Speed;
        Hero->Dest.y+=Hero->VelocityY*Hero->Speed;

}

int  porownaj (char tekst[],char tekst1[])
{
    return strcmp(tekst,tekst1);
}

void SetAnimationWithName(struct Player* player,char* name)
{


    if(strcmp(name,player->CurrentFrameInfo->Name)==0) return;

    int i;


    for(i = 0;i<sizeof(player->FrameAnimInfos)/sizeof(player->FrameAnimInfos[0]);i++)
    {
        if(strcmp(name,player->FrameAnimInfos[i].Name)==0)
        {
            player->CurrentFrameInfo = &player->FrameAnimInfos[i];
            player->frame=player->CurrentFrameInfo->Start;
            return;
        }

    }

    printf("Nie ma takiej animacji\n");
    return;
}

void SetFrameInfos(int index, struct Player* player, char* name, int start, int end)
{
    player->animTimer=400;
    if(index > (sizeof(player->FrameAnimInfos)/sizeof(player->FrameAnimInfos[0]))) return;

    player->FrameAnimInfos[index].Start = start;
    player->FrameAnimInfos[index].End = end;
    player->FrameAnimInfos[index].Name = strdup(name);


}

void SetHeroAnimation(struct Player* player)
{
    player->animTimer+=60;
    if(player->animTimer>400)
    {
        player->frame++;

        if(player->frame > player->CurrentFrameInfo->End)
        {
            player->frame=player->CurrentFrameInfo->Start;
        }

        player->animTimer =0;

        player->CurrentFrame = &(player->AnimFrames[player->frame]);
    }
}

void DrawPlayer(struct Player* player, SDL_Renderer* SDL_Renderer)
{
    SetHeroAnimation(player);

    int orientation = SDL_FLIP_NONE;
    if(player->VelocityX<0)
        orientation=SDL_FLIP_HORIZONTAL;

    SDL_Rect src = player->CurrentFrame->AnimFrame;
    SDL_Rect dest = player->Dest;
    SDL_RenderCopyEx(SDL_Renderer,player->playerSprite ,&src, &dest ,0.0,NULL,orientation);

}

void SetUpAnimations(struct Player* player)
{
    int x=0,y=0;
    for(x=0;x<4;x++)
    {
        for(y=0;y<4;y++)
        {
            int index = 4*x+y;
            player->AnimFrames[index].AnimFrame.x= y*32;
            player->AnimFrames[index].AnimFrame.y= x*32;
            player->AnimFrames[index].AnimFrame.w= 32;
            player->AnimFrames[index].AnimFrame.h= 32;
        }
    }
    SetFrameInfos(0,player,"Idle",0,1);
    SetFrameInfos(1,player,"Walk",2,3);
    SetFrameInfos(2,player,"Jump",4,5);
    SetFrameInfos(3,player,"Slide",6,7);
    SetFrameInfos(4,player,"Hit",8,9);

     player->CurrentFrameInfo = &player->FrameAnimInfos[0];
}

void ResetPlayer(struct Player* player,SDL_Renderer*renderer)
{
        player->Dest.w=64+64;
    player->Dest.h = 64+64;
    player->Dest.x=0;
    player->Dest.y=0;
    player->frame=0;
    player->onGround = false;
    player->isJumping = false;
    player->isSlide = false;

    player->Speed =5;
    player->VelocityX=0;
    player->VelocityY=0;

 
  
    SetUpAnimations(player);

    SetAnimationWithName(player,"Idle");
}