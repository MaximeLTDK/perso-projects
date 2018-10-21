#include "process.h"
#include "pixel.h"
#include <SDL/SDL.h>

void clear(SDL_Surface *surface)
{
	struct pixel sp = get_pixel(surface, 0, 0);
	sp.r = 0xff;
	sp.g = 0xff;
	sp.b = 0xff;

	for (int i = 0; i < surface->w; i++)
	{
		for (int j = 0; j < surface->h; j++)
		{
			put_pixel(surface, i, j, sp);
		}
	}
}

void grayscale(SDL_Surface *surface)
{
	struct pixel sp;

	for (int i = 0; i < surface->w; i++)
	{
		for (int j = 0; j < surface->h; j++)
		{
			sp = get_pixel(surface, i, j);

			int gray = 0.3*sp.r + 0.59*sp.g + 0.11*sp.b;
			sp.r = gray;
			sp.g = gray;
			sp.b = gray;

			put_pixel(surface, i, j, sp);
		}
	}
}

void normalize(SDL_Surface *surface)
{
	struct pixel sp;

	for (int i = 0; i < surface->w; i++)
	{
		for (int j = 0; j < surface->h; j++)
		{
			
		}
	}
}

void rlsa_line_process(SDL_Surface *surface)
{
	int white_count, c = 48;

	for (int j = 0; j < surface->h; j++)
	{
		for (int i = 0; i < surface->w; i++)
		{
			struct pixel sp = get_pixel(surface, i, j);

			if (sp.r > 0x80 && sp.g > 0x80 && sp.b > 0x80)
				white_count += 1;
			else if (white_count < c)
			{
				for (int k = i - white_count; k < i; k++)
				{
					sp.r = 0x00;
					sp.g = 0x00;
					sp.b = 0x00;

					put_pixel(surface, k, j, sp);
				}

				white_count = 0;
			}
			else
			{
				white_count = 0;
			}
		}
	}
}

void rlsa_column_process(SDL_Surface *surface)
{
	int white_count, c = 102;

	for (int i = 0; i < surface->w; i++)
	{
		for (int j = 0; j < surface->h; j++)
		{
			struct pixel sp = get_pixel(surface, i, j);

			if (sp.r > 0xf0 && sp.g > 0xf0 && sp.b > 0xf0)
				white_count += 1;
			else if (white_count < c)
			{
				for (int k = j - white_count; k < j; k++)
				{
					sp.r = 0x00;
					sp.g = 0x00;
					sp.b = 0x00;

					put_pixel(surface, i, k, sp);
				}

				white_count = 0;
			}
			else
			{
				white_count = 0;
			}
		}
	}

}

void rlsa_process(SDL_Surface *surface)
{
	rlsa_line_process(surface);
	rlsa_column_process(surface);
}

void rlsa_complete_blocs(SDL_Surface *srlsa)
{
	struct pixel cp = get_pixel(srlsa, 0, 0);
	cp.r = 0x00;
	cp.g = 0x00;
	cp.b = 0x00;

	for (int c = 0, l = 0; c < srlsa->w; c++)
	{
		if (check_column(srlsa, c, cp))
		{
			for (int i = 0; i < srlsa->w; i++)
			{
				
			}
		}
	}
}

void rlsa_run_blocs(SDL_Surface *surface)
{
	rlsa_process(surface);
	rlsa_complete_blocs(surface);
}

void rlsa_complete_lines(SDL_Surface *srlsa)
{
	struct pixel cp = get_pixel(srlsa, 0, 0);
	cp.r = 0x00;
	cp.g = 0x00;
	cp.b = 0x00;

	int l = 0;
	while (l < srlsa->h)
	{
		if (check_line(srlsa, l, cp))
		{
			int hmax;

			for (int j = l; j < srlsa->h; j++)
			{
				if (!check_line(srlsa, j+1, cp))
				{
					hmax = j;
					break;
				}
			}

			for (int i = 0; i < srlsa->w; i++)
			{
				if (check_col_range(srlsa, l, hmax, i, cp))
				{
					put_range(srlsa, l, hmax, i, 0, cp);
				}
			}

			l++;
		}
		else
			l++;
	}
}

void rlsa_run_lines(SDL_Surface *surface)
{
	rlsa_line_process(surface);
	rlsa_complete_lines(surface);
}

SDL_Surface* crop_surface(SDL_Surface *s, SDL_Rect crop)
{
	SDL_Surface *cropped = SDL_CreateRGBSurface(s->flags, crop.w, crop.h, s->format->BitsPerPixel, s->format->Rmask, s->format->Gmask, s->format->Bmask, s->format->Amask);

	struct pixel sp;

	for (int i = 0; i < crop.w; i++)
	{
		for (int j = 0; j < crop.h; j++)
		{
			sp = get_pixel(s, crop.x + i, crop.y + j);

			put_pixel(cropped, i, j, sp);
		}
	}

	return cropped;
}

SDL_Surface* clip_text_line(SDL_Surface *surface, SDL_Surface *srlsa, int n)
{
	struct pixel cp = get_pixel(srlsa, 0, 0);
	cp.r = 0x00;
	cp.g = 0x00;
	cp.b = 0x00;

	int line = -1;
	SDL_Rect clip;

	for (int j = 1; j < srlsa->h; j++)
	{
		if (check_line(srlsa, j, cp) && !check_line(srlsa, j-1, cp))
		{
			line++;

			if (line == n)
			{
				clip.y = j;

				for (int h = j; h < srlsa->h; h++)
				{
					if (check_line(srlsa, h, cp) && !check_line(srlsa, h+1, cp))
					{
						clip.h = h - clip.y - 1;
						break;
					}
				}
				break;
			}
		}
	}

	clip.x = 0;
	clip.w = surface->w;

	SDL_Surface *trlsa = crop_surface(srlsa, clip);

	for (int i = 1; i < trlsa->w; i++)
	{
		if (check_col_range(trlsa, 0, trlsa->h-1, i, cp) && !check_col_range(trlsa, 0, trlsa->h-1, i-1, cp))
		{
			clip.x = i;

			for (int l = i; l < trlsa->w; l++)
			{
				if (check_col_range(trlsa, 0, trlsa->h-1, l, cp) && !check_col_range(trlsa, 0, trlsa->h-1, l+1, cp))
				{
					clip.w = l - clip.x;
					break;
				}
			}
			break;
		}
	}

	SDL_FreeSurface(trlsa);

	return crop_surface(surface, clip);
}

int count_text_lines(SDL_Surface *srlsa)
{
	struct pixel cp = get_pixel(srlsa, 0, 0);
	cp.r = 0x00;
	cp.g = 0x00;
	cp.b = 0x00;

	int count = 0;

	for (int j = 1; j < srlsa->h; j++)
	{
		if (check_line(srlsa, j, cp) && !check_line(srlsa, j-1, cp))
			count++;
	}

	return count - 1;
}

void delimit_chars(SDL_Surface *sline)
{
	struct pixel cp = get_pixel(sline, 0, 0);
	cp.r = 0x00;
	cp.g = 0x00;
	cp.b = 0x00;

	struct pixel dp = get_pixel(sline, 0, 0);
	dp.r = 0xff;
	dp.g = 0x00;
	dp.b = 0x00;

	for (int i = 1; i < sline->w; i++)
	{
		if ((check_col_range(sline, 0, sline->h-1, i, cp) && !(check_col_range(sline, 0, sline->h-1, i-1, cp) || check_col_range(sline, 0, sline->h-1, i-1, dp))) || (check_col_range(sline, 0, sline->h-1, i, cp) && !check_col_range(sline, 0, sline->h-1, i+1, cp)))
		{
			put_range(sline, 0, sline->h-1, i, 0, dp);
		}
	}
}
