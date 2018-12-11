// [task_2.c]
// In this task, you'll learn how to use the allegro5 library to
// draw primitives, images and render strings using custom fonts.
// You should put the files: 'pirulen.ttf', '32largebugs.jpg' inside your project folder.
// You only need to enter codes below the 'TODO' comments.

#include <stdio.h>
#include <allegro5/allegro.h>
// TODO: [Include headers]
// Include the header files that enables us to
// 1) draw primitives.
// 2) load and draw images.
// 3) load fonts and render strings.
// 4) load true-type fonts.
// There are total 4 headers to include.

// If defined, logs will be shown on console and written to file.
#define LOG_ENABLED

ALLEGRO_DISPLAY* game_display;
// TODO: [Declare variables]
// Declare the variables that store the font and the image we need.

// Define screen width and height as constants.
const int SCREEN_W = 800;
const int SCREEN_H = 600;

// Define image width and height for later calculation.
const int IMG_W = 640;
const int IMG_H = 479;

/* Declare function prototypes. */

// Initialize variables and resources.
// Allows the game to perform any initialization it needs before
// starting to run.
void game_init(void);
// Draw to display.
// This is called when the game should draw itself.
void game_draw(void);
// Release resources.
// Free the pointers we allocated.
void game_destroy(void);

/* Declare function prototypes for debugging. */

// Display error message and exit the program, used like 'printf'.
// Write formatted output to stdout and file from the format string.
// If the program crashes unexpectedly, you can inspect "log.txt" for
// further information.
void game_abort(const char* format, ...);
// Log events for later debugging, used like 'printf'.
// Write formatted output to stdout and file from the format string.
// You can inspect "log.txt" for logs in the last run.
void game_log(const char* format, ...);
// Called by 'game_abort', 'game_log' to deal with va_lists.
void game_vlog(const char* format, va_list arg);

// Program entry point.
// Returns program exit code.
int main(void) {
    // Initialize allegro5 library
    if (!al_init())
        game_abort("failed to initialize allegro");
    game_display = al_create_display(SCREEN_W, SCREEN_H);
    if (!game_display)
        game_abort("failed to create display");

    // TODO: [Initialize add-ons]
    // 1) Initialize primitives add-on.
    // 2) Initialize font add-on.
    // 3) Initialize ttf (True Type Font) add-on.
    // 4) Initialize image add-on.
    // Don't forget to check the return value.

    game_log("Allegro5 initialized");
    game_log("Game begin");
    game_init();
    game_log("Game initialized");
    game_draw();
    // Wait 20 secs before exiting.
    al_rest(20);
    game_log("Game end");
    game_destroy();
    return 0;
}

void game_init(void) {
    // TODO: [Load resources]
    // Load font from file: 'pirulen.ttf' with font size 12.
    // Load image from file: '32largebugs.jpg'.
    // Don't forget to check the return values.
}

void game_draw(void) {
    al_clear_to_color(al_map_rgb(100, 100, 100));
    // TODO: [Draw to display]
    // 1) Draw a rectangle that wraps the title text.
    //    with (x1, y1) = ((SCREEN_W - 437) / 2, 24),
    //         (x2, y2) = ((SCREEN_W + 437) / 2, 50).
    //         color with rgb: (255, 255, 255).
    // 2) Render the title using the font we just loaded.
    //    with (x, y) = (SCREEN_W / 2, 30),
    //         color with rgb: (255, 255, 255),
    //         flags: ALLEGRO_ALIGN_CENTER,
    //         text: "How to deal with bugs in your final project".
    // 3) Draw the image we just loaded.
    //    with (x, y) = ((SCREEN_W - IMG_W) / 2, (SCREEN_H - IMG_H) / 2).
    // 4) Render the source url using the font we just loaded.
    //    with (x, y) = (SCREEN_W / 2, 550),
    //         color with rgb: (255, 255, 255),
    //         flags: ALLEGRO_ALIGN_CENTER,
    //         text: "Source: http://cartoontester.blogspot.com/2010/01/big-bugs.html".

    al_flip_display();
}

void game_destroy(void) {
    // TODO: [Release resources]
    // Destroy everything you have created.
    // Free the memories allocated by malloc or allegro functions.
    // We should destroy the bitmap and font we loaded.
    al_destroy_display(game_display);
}

// +=================================================================+
// | Code below is for debugging purpose, it's fine to remove it.    |
// | Deleting the code below and removing all calls to the functions |
// | doesn't affect the game.                                        |
// +=================================================================+

void game_abort(const char* format, ...) {
    va_list arg;
    va_start(arg, format);
    game_vlog(format, arg);
    va_end(arg);
    fprintf(stderr, "error occured, exiting after 2 secs");
    // Wait 2 secs before exiting.
    al_rest(2);
    // Force exit program.
    exit(1);
}

void game_log(const char* format, ...) {
#ifdef LOG_ENABLED
    va_list arg;
    va_start(arg, format);
    game_vlog(format, arg);
    va_end(arg);
#endif
}

void game_vlog(const char* format, va_list arg) {
#ifdef LOG_ENABLED
    static bool clear_file = true;
    vprintf(format, arg);
    printf("\n");
    // Write log to file for later debugging.
    FILE* pFile = fopen("log.txt", clear_file ? "w" : "a");
    if (pFile) {
        vfprintf(pFile, format, arg);
        fprintf(pFile, "\n");
        fclose(pFile);
    }
    clear_file = false;
#endif
}
