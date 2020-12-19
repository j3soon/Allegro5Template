// [shared.c]
// you should define the shared variable declared in the header here.

#include "shared.h"
#include "utility.h"
#include "game.h"
#include "scene_menu.h"

ALLEGRO_FONT* font_pirulen_32;
ALLEGRO_FONT* font_pirulen_24;

void shared_init(void) {
    font_pirulen_32 = load_font("pirulen.ttf", 32);
    font_pirulen_24 = load_font("pirulen.ttf", 24);
    game_change_scene(scene_menu_create());
}

void shared_destroy(void) {
    al_destroy_font(font_pirulen_32);
    al_destroy_font(font_pirulen_24);
}