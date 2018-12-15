// [task_1.c]
// In this task, you'll learn how to use the allegro5 library to
// display an empty window.
// You only need to enter codes below the 'TODO' comments.

#include <stdio.h>
#include <allegro5/allegro.h>

// If defined, logs will be shown on console and written to file.
#define LOG_ENABLED

// TODO: [Declare variables]
// Declare the variable that stores the window display pointer.

// Define screen width and height as constants.
const int SCREEN_W = 800;
const int SCREEN_H = 600;

/* Declare function prototypes. */

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
    // Wait 5 secs before execution.
    al_rest(5);

    // Initialize allegro5 library.
    if (!al_init())
        game_abort("failed to initialize allegro");
    // TODO: [Create display]
    // 1) Create display with size SCREEN_W * SCREEN_H and store the
    //    pointer in the variable you just declared.
    // 2) Check the pointer, call game_abort if the function failed.

    game_log("Allegro5 initialized");
    game_log("Game begin");
    game_draw();
    // Wait 5 secs before exiting.
    al_rest(5);
    game_log("Game end");
    game_destroy();
    return 0;
}

void game_draw(void) {
    // TODO: [Draw to display]
    // 1) Fill the whole window with a color with rgb: (100, 100, 100).
    // 2) Update display.
}

void game_destroy(void) {
    // TODO: [Release resources]
    // Destroy everything you have created.
    // Free the memories allocated by malloc or allegro functions.
    // We should destroy the display we created.
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
