#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


struct PaperStack
{
    SDL_Rect Position;
    SDL_Rect AnimFrames[3];
    SDL_Texture* SpriteSheet;
};



void DrawPaperStack(struct PaperStack* paper, SDL_Renderer* SDL_Renderer);



