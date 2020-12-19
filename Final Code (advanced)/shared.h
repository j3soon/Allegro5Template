// [shared.h]
// you should put shared variables between files in this header.

#ifndef SCENE_SHARED_H
#define SCENE_SHARED_H
#include <allegro5/allegro_font.h>

// TODO: Shared constant variable (without initializing value).

// TODO: More shared resources or data that needed to be accessed
// across different scenes. initialize the value in 'shared.c'.
extern ALLEGRO_FONT* font_pirulen_32;
extern ALLEGRO_FONT* font_pirulen_24;

// Initialize shared variables and resources.
// Allows the game to perform any initialization it needs before
// starting to run.
void shared_init(void);
// Free shared variables and resources.
void shared_destroy(void);

#endif