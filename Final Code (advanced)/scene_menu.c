#include "scene_menu.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_acodec.h>
#include "game.h"
#include "utility.h"
#include "shared.h"
#include "scene_start.h"
#include "scene_settings.h"

// Variables and functions with 'static' prefix at the top level of a
// source file is only accessible in that file ("file scope", also
// known as "internal linkage"). If other files has the same variable
// name, they'll be different variables.

/* Define your static vars / function prototypes below. */

// TODO: More variables and functions that will only be accessed
// inside this scene. They should all have the 'static' prefix.

static const char* txt_title = "Space Shooter";
static const char* txt_info = "Press enter key to start";
static ALLEGRO_BITMAP* img_background;
// [HACKATHON 3-1]
// TODO: Declare 2 variables for storing settings images.
// Uncomment and fill in the code below.
//static ??? img_settings;
//static ??? img_settings2;
static ALLEGRO_SAMPLE* bgm;
static ALLEGRO_SAMPLE_ID bgm_id;

static void init(void);
static void draw(void);
static void destroy(void);
static void on_key_down(int keycode);

static void init(void) {
    img_background = load_bitmap_resized("main-bg.jpg", SCREEN_W, SCREEN_H);
    // [HACKATHON 3-4]
    // TODO: Load settings images.
    // Uncomment and fill in the code below.
    //img_settings = ???("settings.png");
    //img_settings2 = ???("settings2.png");
    // Can be moved to shared_init to decrease loading time.
    bgm = load_audio("S31-Night Prowler.ogg");
    bgm_id = play_bgm(bgm, 1);
    game_log("Menu scene initialized");
}

static void draw(void) {
    al_draw_bitmap(img_background, 0, 0, 0);
    // [HACKATHON 3-5]
    // TODO: Draw settings images.
    // The settings icon should be located at (x, y, w, h) =
    // (SCREEN_W - 48, 10, 38, 38).
    // Change its image according to your mouse position.
    // Uncomment and fill in the code below.
    //if (pnt_in_rect(mouse_x, mouse_y, ???, ???, ???, ???))
    //    ???(img_settings2, ???, ???, 0);
    //else
    //    ???(img_settings, ???, ???, 0);
    al_draw_text(font_pirulen_32, al_map_rgb(255, 255, 255), SCREEN_W / 2, 30, ALLEGRO_ALIGN_CENTER, txt_title);
    al_draw_text(font_pirulen_24, al_map_rgb(255, 255, 255), 20, SCREEN_H - 50, 0, txt_info);
}

static void destroy(void) {
    al_destroy_sample(bgm);
    al_destroy_bitmap(img_background);
    // [HACKATHON 3-6]
    // TODO: Destroy the 2 settings images.
    // Uncomment and fill in the code below.
    //???(img_settings);
    //???(img_settings2);
    stop_bgm(bgm_id);
    game_log("Menu scene destroyed");
}

static void on_key_down(int keycode) {
    if (keycode == ALLEGRO_KEY_ENTER)
        game_change_scene(scene_start_create());
}

// [HACKATHON 3-7]
// TODO: When settings clicked, switch to settings scene.
// Uncomment and fill in the code below.
//static void on_mouse_down(int btn, int x, int y, int dz) {
//    if (btn == ???) {
//        if (pnt_in_rect(x, y, ???, ???, ???, ???))
//            game_change_scene(???);
//    }
//}

// TODO: Add more event callback functions such as update, ...

// Functions without 'static', 'extern' prefixes is just a normal
// function, they can be accessed by other files using 'extern'.
// Define your normal function prototypes below.

// The only function that is shared across files.
Scene scene_menu_create(void) {
    Scene scene;
    memset(&scene, 0, sizeof(Scene));
    scene.name = "Menu";
    scene.initialize = &init;
    scene.draw = &draw;
    scene.destroy = &destroy;
    scene.on_key_down = &on_key_down;
    // [HACKATHON 3-8]
    // TODO: Register on_mouse_down.
    // Uncomment the code below.
    //scene.on_mouse_down = &on_mouse_down;
    // TODO: Register more event callback functions such as update, mouse, ...
    game_log("Menu scene created");
    return scene;
}
