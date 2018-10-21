#ifndef PROCESS_H
#define PROCESS_H

#include <SDL/SDL.h>

void clear(SDL_Surface*);
void grayscale(SDL_Surface*);
void normalize(SDL_Surface*);

void rlsa_line_process(SDL_Surface*);
void rlsa_column_process(SDL_Surface*);
void rlsa_process(SDL_Surface*);

void rlsa_complete_blocs(SDL_Surface*);
void rlsa_run_blocs(SDL_Surface*);
void rlsa_complete_lines(SDL_Surface*);
void rlsa_run_lines(SDL_Surface*);

SDL_Surface* crop_surface(SDL_Surface*, SDL_Rect);
SDL_Surface* clip_text_line(SDL_Surface*, SDL_Surface*, int);
int count_text_lines(SDL_Surface*);

void delimit_chars(SDL_Surface*);

#endif //PROCESS_H
