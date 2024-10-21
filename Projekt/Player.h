
#define true 1
#define false 0
typedef _Bool bool;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>


#define PLAYER_H



struct Frame
{
       SDL_Rect AnimFrame;
};


struct AnimationData
{
   char* Name;
   int Start;
   int End;
};


struct Player
{
    int frame;
    SDL_Texture* playerSprite;
    struct Frame* CurrentFrame;
    struct AnimationData* CurrentFrameInfo;
    int Speed;
    SDL_Rect Dest;
    float animTimer;
    float VelocityX;    
    float VelocityY; 
    struct Frame AnimFrames[12];
    struct AnimationData FrameAnimInfos[5];
    int jumpStrength;
    bool isJumping;   
    bool onGround; 
    bool isSlide;
    bool isAttack;
    float ActionTimer;
    bool isAlive;
};

void InitPlayer(struct Player* player,SDL_Renderer*renderer,SDL_Surface* image);
void SetAnimationWithName(struct Player* player,char* name);
void SetFrameInfos(int index, struct Player* player, char* name, int startFrame, int endFrame);
void SetHeroAnimation(struct Player* player);
void UpdatePlayer(struct Player* player,float deltaTime);
void DrawPlayer(struct Player* player, SDL_Renderer* SDL_Renderer);
void SetUpAnimations(struct Player* player);

void ResetPlayer(struct Player* player,SDL_Renderer*renderer);