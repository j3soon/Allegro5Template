// [utility.c]
// you should implement the utility functions defined in the header.

#include "utility.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include "game.h"

ALLEGRO_SAMPLE* load_audio(const char* filename) {
    ALLEGRO_SAMPLE* sample = al_load_sample(filename);
    if (!sample)
        game_abort("failed to load audio: %s", filename);
    else
        game_log("loaded audio: %s", filename);
    return sample;
}

ALLEGRO_SAMPLE_ID play_audio(ALLEGRO_SAMPLE* sample, float volume) {
    ALLEGRO_SAMPLE_ID id;
    if (!al_play_sample(sample, volume, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &id))
        game_abort("failed to play audio (once)");
    else
        game_log("played audio (once)");
    return id;
}

ALLEGRO_SAMPLE_ID play_bgm(ALLEGRO_SAMPLE* sample, float volume) {
    ALLEGRO_SAMPLE_ID id;
    if (!al_play_sample(sample, volume, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &id))
        game_abort("failed to play audio (bgm)");
    else
        game_log("played audio (bgm)");
    return id;
}

void stop_bgm(ALLEGRO_SAMPLE_ID sample) {
    al_stop_sample(&sample);
    game_log("stop audio (bgm)");
}

ALLEGRO_FONT* load_font(const char* filename, int size) {
    ALLEGRO_FONT* font = al_load_font(filename, size, 0);
    if (!font)
        game_abort("failed to load font: %s with size %d", filename, size);
    else
        game_log("loaded font: %s with size %d", filename, size);
    return font;
}

ALLEGRO_BITMAP* load_bitmap(const char* filename) {
    ALLEGRO_BITMAP* bmp = al_load_bitmap(filename);
    if (!bmp)
        game_abort("failed to load image: %s", filename);
    else
        game_log("loaded image: %s", filename);
    return bmp;
}

ALLEGRO_BITMAP *load_bitmap_resized(const char *filename, int w, int h) {
    ALLEGRO_BITMAP* loaded_bmp = load_bitmap(filename);
    ALLEGRO_BITMAP *resized_bmp = al_create_bitmap(w, h);
    ALLEGRO_BITMAP *prev_target = al_get_target_bitmap();

    if (!resized_bmp)
        game_abort("failed to create bitmap when creating resized image: %s", filename);
    al_set_target_bitmap(resized_bmp);
    al_draw_scaled_bitmap(loaded_bmp, 0, 0,
        al_get_bitmap_width(loaded_bmp),
        al_get_bitmap_height(loaded_bmp),
        0, 0, w, h, 0);
    al_set_target_bitmap(prev_target);
    al_destroy_bitmap(loaded_bmp);

    game_log("resized image: %s", filename);

    return resized_bmp;
}

// [HACKATHON 3-3]
// TODO: Define bool pnt_in_rect(int px, int py, int x, int y, int w, int h)
// Uncomment and fill in the code below.
//bool pnt_in_rect(int px, int py, int x, int y, int w, int h) {
//    return ???;
//}
