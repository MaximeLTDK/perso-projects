#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "pixel.h"
#include "process.h"
#include "output.h"

void pause()
{
	int _continue = 1;
	SDL_Event event;

	while (_continue)
	{
		SDL_WaitEvent(&event);

		switch (event.type)
		{
			case SDL_QUIT:
			case SDL_KEYDOWN:
				_continue = 0;
				break;
		}
	}
}

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		fprintf(stderr, "SDL INIT ERROR : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Surface *window = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	SDL_Surface *img1 = IMG_Load(argv[1]);

	SDL_Surface *img2 = IMG_Load(argv[1]);

	SDL_Surface *img3 = IMG_Load(argv[1]);

	segment_blocks(img1);

	SDL_Rect pos;
	pos.x = 0;
	pos.y = 0;
	SDL_BlitSurface(img1, NULL, window, &pos);
	SDL_Flip(window);

	pause();

	SDL_FreeSurface(img1);

	segment_lines(img2);

	SDL_BlitSurface(img2, NULL, window, &pos);
	SDL_Flip(window);

	pause();

	SDL_FreeSurface(img2);

	detect_chars(img3);

	SDL_BlitSurface(img3, NULL, window, &pos);
	SDL_Flip(window);

	pause();

	SDL_FreeSurface(img3);

	SDL_Quit();

	return EXIT_SUCCESS;
}
