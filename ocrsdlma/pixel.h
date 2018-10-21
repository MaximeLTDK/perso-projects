#ifndef PIXEL_H
#define PIXEL_H

#include <SDL/SDL.h>

struct pixel
{
	SDL_PixelFormat *format;

	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
};

Uint32 get_pixel_surface(SDL_Surface*, int, int);
void put_pixel_surface(SDL_Surface*, int, int, Uint32);
struct pixel Uint32_to_spixel(Uint32, SDL_PixelFormat*);
Uint32 spixel_to_Uint32(struct pixel);

struct pixel get_pixel(SDL_Surface*, int, int);
void put_pixel(SDL_Surface*, int, int, struct pixel);

Uint32* get_range(SDL_Surface*, int, int);
void put_range(SDL_Surface*, int, int, int, int, struct pixel);

int check_pixel(SDL_Surface*, int, int, struct pixel);
int check_line_range(SDL_Surface*, int, int, int, struct pixel);
int check_col_range(SDL_Surface*, int, int, int, struct pixel);
int check_line(SDL_Surface*, int, struct pixel);
int check_column(SDL_Surface*, int, struct pixel);

#endif //PIXEL_H
