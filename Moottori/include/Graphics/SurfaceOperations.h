#pragma once
#include <SDL.h>

Uint8 GetAlpha(int x, int y, SDL_Surface *surface);
Uint8 GetRed(int x, int y, SDL_Surface *surface);
Uint8 GetGreen(int x, int y, SDL_Surface *surface);
Uint8 GetBlue(int x, int y, SDL_Surface *surface);

void SetAlpha(int x, int y, Uint32 color, SDL_Surface *surface);
void SetRed(int x, int y, Uint32 color, SDL_Surface *surface);
void SetGreen(int x, int y, Uint32 color, SDL_Surface *surface);
void SetBlue(int x, int y, Uint32 color, SDL_Surface *surface);
