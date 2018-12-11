// [task_5.c]
// In this task, you'll learn how to use the allegro5 library to
// implement the event loop, reading the mouse input. We'll also
// make use of a timer to update and redraw our display.
// You only need to enter codes below the 'TODO' comments.

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

// If defined, logs will be shown on console and written to file.
#define LOG_ENABLED

ALLEGRO_DISPLAY* game_display;
ALLEGRO_EVENT_QUEUE* game_event_queue;
ALLEGRO_TIMER* game_update_timer;

// Frame rate (frame per second)
const int FPS = 60;
// Define screen width and height as constants.
const int SCREEN_W = 800;
const int SCREEN_H = 600;
// Mouse state, whether the key is down or not.
bool* mouse_state;
// Mouse position.
int mouse_x, mouse_y;

// Define the block's coordinates and color.
float x, y;
ALLEGRO_COLOR color;

/* Declare function prototypes. */

// Initialize variables and resources.
// Allows the game to perform any initialization it needs before
// starting to run.
void game_init(void);
// Initialize allegro5 library
void allegro5_init(void);
// Process events inside the event queue using an infinity loop.
void game_start_event_loop(void);
// Run game logic such as updating the world, checking for collision,
// switching scenes and so on.
// This is called when the game should update its logic.
void game_update(void);
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
    allegro5_init();
    game_log("Allegro5 initialized");
    game_log("Game begin");
    game_init();
    game_log("Game initialized");
    // Draw the first frame.
    game_draw();
    game_log("Game start event loop");
    // This call blocks until the game is finished.
    game_start_event_loop();
    game_log("Game end");
    game_destroy();
    return 0;
}

void allegro5_init(void) {
    // Initialize allegro5 library
    if (!al_init())
        game_abort("failed to initialize allegro");

    // Setup game display.
    game_display = al_create_display(SCREEN_W, SCREEN_H);
    if (!game_display)
        game_abort("failed to create display");

    // Setup update timer.
    game_update_timer = al_create_timer(1.0f / FPS);
    if (!game_update_timer)
        game_abort("failed to create timer");

    // Setup event queue.
    game_event_queue = al_create_event_queue();
    if (!game_event_queue)
        game_abort("failed to create event queue");

    // Initialize add-ons.
    if (!al_init_primitives_addon())
        game_abort("failed to initialize primitives add-on");
    // TODO: [Install mouse]
    // Don't forget to check the return value.
    if (!al_install_mouse())
        game_abort("failed to install mouse");

    // Malloc mouse buttons state according to button counts.
    const unsigned m_buttons = al_get_mouse_num_buttons();
    game_log("There are total %u supported mouse buttons", m_buttons);
    // mouse_state[0] will not be used.
    mouse_state = malloc((m_buttons + 1) * sizeof(bool));
    memset(mouse_state, false, (m_buttons + 1) * sizeof(bool));

    al_register_event_source(game_event_queue, al_get_display_event_source(game_display));
    // TODO: [Register mouse to event queue]
    al_register_event_source(game_event_queue, al_get_mouse_event_source());
    al_register_event_source(game_event_queue, al_get_timer_event_source(game_update_timer));

    // Start the timer to update and draw the game.
    al_start_timer(game_update_timer);
}

void game_init(void) {
    x = y = mouse_x = mouse_y = 400;
    color = al_map_rgb(0, 0, 0);
}

void game_start_event_loop(void) {
    bool done = false;
    ALLEGRO_EVENT event;
    while (!done) {
        al_wait_for_event(game_event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            // Event for clicking the window close button.
            done = true;
        // TODO: [Process events]
        // 1) If the event's type is ALLEGRO_EVENT_MOUSE_BUTTON_DOWN, set the
        //    corresponding element in 'mouse_state' to true.
        // 2) If the event's type is ALLEGRO_EVENT_MOUSE_BUTTON_UP, set the
        //    corresponding element in 'mouse_state' to false.
        // 3) If the event's type is ALLEGRO_EVENT_MOUSE_AXES, log
        //    whether it is mouse move or mouse scroll.
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            // Event for mouse key down.
            game_log("Mouse button %d down at (%d, %d)", event.mouse.button, event.mouse.x, event.mouse.y);
            mouse_state[event.mouse.button] = true;
        } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            // Event for mouse key up.
            game_log("Mouse button %d up at (%d, %d)", event.mouse.button, event.mouse.x, event.mouse.y);
            mouse_state[event.mouse.button] = false;
        } else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            if (event.mouse.dx != 0 || event.mouse.dy != 0) {
                // Event for mouse move.
                game_log("Mouse move to (%d, %d)", event.mouse.x, event.mouse.y);
                mouse_x = event.mouse.x;
                mouse_y = event.mouse.y;
            } else if (event.mouse.dz != 0) {
                // Event for mouse scroll.
                game_log("Mouse scroll at (%d, %d) with delta %d", event.mouse.x, event.mouse.y, event.mouse.dz);
            }
        } else if (event.type == ALLEGRO_EVENT_TIMER) {
            // Event for redrawing the display.
            if (event.timer.source == game_update_timer) {
                game_update();
                game_draw();
            }
        }
    }
}

void game_update(void) {
    // TODO: [Update coordinates]
    // Update 'x' and 'y' according to the current mouse position.
    // Update 'color' according to which mouse button is pressed.
    x = mouse_x;
    y = mouse_y;
    if (mouse_state[1])
        color = al_map_rgb(255, 255, 255);
    else if (mouse_state[2])
        color = al_map_rgb(255, 0, 0);
    else if (mouse_state[3])
        color = al_map_rgb(0, 0, 255);
    else
        color = al_map_rgb(0, 0, 0);
}

void game_draw(void) {
    al_clear_to_color(al_map_rgb(100, 100, 100));
    al_draw_filled_rectangle(x - 20, y - 20, x + 20, y + 20, color);
    al_flip_display();
}

void game_destroy(void) {
    al_destroy_timer(game_update_timer);
    al_destroy_event_queue(game_event_queue);
    al_destroy_display(game_display);
    free(mouse_state);
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
