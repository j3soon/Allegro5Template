// [task_3.c]
// In this task, you'll learn how to use the allegro5 library to
// implement the event loop, making the window's close button work.
// You only need to enter codes below the 'TODO' comments.

#include <stdio.h>
#include <allegro5/allegro.h>

// If defined, logs will be shown on console and written to file.
#define LOG_ENABLED

ALLEGRO_DISPLAY* game_display;
// TODO: [Declare variables]
// Declare the variables that stores the event queue.
ALLEGRO_EVENT_QUEUE* game_event_queue;

// Define screen width and height as constants.
const int SCREEN_W = 800;
const int SCREEN_H = 600;

/* Declare function prototypes. */

// Process events inside the event queue using an infinity loop.
void game_start_event_loop(void);
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
    // TODO: [Create event queue]
    // 1) Create event queue and store the pointer in the variable you just declared.
    // 2) Check the pointer, call game_abort if the function failed.
    game_event_queue = al_create_event_queue();
    if (!game_event_queue)
        game_abort("failed to create event queue");
    // TODO: [Register display to event queue]
    al_register_event_source(game_event_queue, al_get_display_event_source(game_display));

    game_log("Allegro5 initialized");
    game_log("Game begin");
    game_log("Game start event loop");
    // This call blocks until the game is finished.
    game_start_event_loop();
    game_log("Game end");
    game_destroy();
    return 0;
}

void game_start_event_loop(void) {
    bool done = false;
    ALLEGRO_EVENT event;
    while (!done) {
        // TODO: [Process events]
        // 1) Wait for event and store it in the 'event' variable.
        // 2) If the event's type is ALLEGRO_EVENT_DISPLAY_CLOSE, set
        //    'done' to true.
        al_wait_for_event(game_event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            // Event for clicking the window close button.
            game_log("Window close button clicked");
            done = true;
        }
    }
}

void game_destroy(void) {
    // TODO: [Release resources]
    // Destroy everything you have created.
    // Free the memories allocated by malloc or allegro functions.
    // We should destroy the event queue we created.
    al_destroy_event_queue(game_event_queue);
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
