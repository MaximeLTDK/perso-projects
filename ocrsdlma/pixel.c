#include "pixel.h"
#include <SDL/SDL.h>

Uint32 get_pixel_surface(SDL_Surface *surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;

	Uint8 *p = (Uint8*)surface->pixels + y*surface->pitch + x*bpp;

	switch (bpp)
	{
	case 1:
		return *p;
		break;
	
	case 2:
		return *(Uint16 *)p;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 |p[2] << 16;
		break;

	case 4:
		return *(Uint32 *)p;
		break;
	
	default:
		return 0;
	}
}

void put_pixel_surface(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	int bpp = surface->format->BytesPerPixel;

	Uint8 *p = (Uint8*)surface->pixels + y*surface->pitch + x*bpp;

	switch (bpp)
	{
	case 1:
		*p = pixel;
		break;

	case 2:
		*(Uint16 *)p = pixel;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		}
		else
		{
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
		break;

	case 4:
		*(Uint32 *)p = pixel;
		break;
	}
}

struct pixel Uint32_to_spixel(Uint32 pixel, SDL_PixelFormat *format)
{
	struct pixel spixel;

	spixel.format = format;
	SDL_GetRGBA(pixel, format, &spixel.r, &spixel.g, &spixel.b, &spixel.a);

	return spixel;
}

Uint32 spixel_to_Uint32(struct pixel spixel)
{
	return SDL_MapRGBA(spixel.format, spixel.r, spixel.g, spixel.b, spixel.a);
}

struct pixel get_pixel(SDL_Surface *surface, int x, int y)
{
	Uint32 pixel = get_pixel_surface(surface, x, y);

	return Uint32_to_spixel(pixel, surface->format);
}

void put_pixel(SDL_Surface *surface, int x, int y, struct pixel spixel)
{
	Uint32 pixel = spixel_to_Uint32(spixel);

	put_pixel_surface(surface, x, y, pixel);
}

Uint32* get_range(SDL_Surface *surface, int a, int b)
{
	return NULL;
}

void put_range(SDL_Surface *surface, int a, int b, int c, int orient, struct pixel sp)
{
	for (int n = a; n <= b; n++)
	{
		if (orient)
			put_pixel(surface, n, c, sp);
		else
			put_pixel(surface, c, n, sp);
	}
}

int check_pixel(SDL_Surface *surface, int i, int j, struct pixel cp)
{
	struct pixel sp = get_pixel(surface, i, j);

	return sp.r == cp.r && sp.g == cp.g && sp.b == cp.b;
}

int check_line_range(SDL_Surface *surface, int a, int b, int line, struct pixel cp)
{
	for (int n = a; n <= b; n++)
	{
		if (check_pixel(surface, n, line, cp))
			return 1;
	}

	return 0;
}

int check_col_range(SDL_Surface *surface, int a, int b, int col, struct pixel cp)
{
	for (int n = a; n <= b; n++)
	{
		if (check_pixel(surface, col, n, cp))
			return 1;
	}

	return 0;
}

int check_line(SDL_Surface *surface, int line, struct pixel cp)
{
	return check_line_range(surface, 0, surface->w, line, cp);
}

int check_column(SDL_Surface *surface, int col, struct pixel cp)
{
	return check_col_range(surface, 0, surface->h, col, cp);
}
