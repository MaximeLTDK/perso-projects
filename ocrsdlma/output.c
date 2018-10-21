#include "output.h"
#include "pixel.h"
#include "process.h"
#include <SDL/SDL.h>

void clean(SDL_Surface *surface)
{
	grayscale(surface);
	normalize(surface);
}

void segment_blocks(SDL_Surface *surface)
{
	clean(surface);

	rlsa_run_blocs(surface);
}

void segment_lines(SDL_Surface *surface)
{
	rlsa_run_lines(surface);
}

void detect_chars(SDL_Surface *surface)
{
	clean(surface);

	SDL_Rect rstd;
	rstd.w = surface->w;
	rstd.h = surface->h;
	SDL_Surface *sslines = crop_surface(surface, rstd);
	segment_lines(sslines);
	SDL_Surface *sd = crop_surface(surface, rstd);
	clear(surface);

	SDL_Rect pos;
	pos.x = 1;
	pos.y = 0;

	struct pixel sp = get_pixel(surface, 0, 0);
	sp.r = 0x00;
	sp.g = 0x00;
	sp.b = 0x00;

	struct pixel dp = get_pixel(surface, 0, 0);
	dp.r = 0xff;
	dp.g = 0x00;
	dp.b = 0x00;

	for (int n = 0; n < 1; n++)//count_text_lines(sslines); n++)
	{
		SDL_Surface *sline = clip_text_line(sd, sslines, n);	
		
		put_range(surface, 0, sline->w-1, pos.y, 1, dp);
		pos.y++;

		put_range(surface, pos.y, sline->h + pos.y, 0, 0, dp);
		put_range(surface, pos.y, sline->h + pos.y, sline->w, 0, dp);

		delimit_chars(sline);

		SDL_BlitSurface(sline, NULL, surface, &pos);

		/*pos.y += sline->h;

		put_range(surface, 0, sline->w, pos.y, 1, dp);*/

		SDL_FreeSurface(sline);
	}

	SDL_FreeSurface(sslines);
	SDL_FreeSurface(sd);
}
