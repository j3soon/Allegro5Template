// [game.h]
// declare shared variables and allegro5 related routines.

// Extern variables are "declare without defining". When
// a variable is defined, the compiler allocates memory for that
// variable and possibly also initializes its contents to some value.
// The declaration informs the compiler that a variable by that name
// and type exists, but the compiler does not need to allocate memory
// for it since it is allocated elsewhere.

// Variables and functions with 'static' prefix at the top level of a
// source file is only accessible in that file ("file scope", also
// known as "internal linkage"). If other files has the same variable
// name, they'll be different variables.

#ifndef GAME_H
#define GAME_H
#include <allegro5/allegro.h>

// If defined, logs will be shown on console and written to file.
// If commented out, logs will not be shown nor be saved.
#define LOG_ENABLED

// Types of function pointers.
typedef void(*func_ptr)(void);
typedef void(*func_ptr_keyboard)(int keycode);
typedef void(*func_ptr_mouse)(int btn, int x, int y, int dz);
// TODO: More function pointer typedefs for other events.

// Structure containing all scene functions / event callbacks.
typedef struct {
	char* name;
	func_ptr initialize;
	func_ptr update;
	func_ptr draw;
	func_ptr destroy;
	func_ptr_keyboard on_key_down;
	func_ptr_keyboard on_key_up;
	func_ptr_mouse on_mouse_down;
	func_ptr_mouse on_mouse_move;
	func_ptr_mouse on_mouse_up;
	func_ptr_mouse on_mouse_scroll;
	// TODO: More event callbacks such as timer tick, video finished, ...
} Scene;

// Frame rate (frame per second)
extern const int FPS;
// Display (screen) width.
extern const int SCREEN_W;
// Display (screen) height.
extern const int SCREEN_H;
// At most 4 audios can be played at a time.
extern const int RESERVE_SAMPLES;

/* Input states */

// The active scene. Events will be triggered through function pointers.
extern Scene active_scene;
// Keyboard state, whether the key is down or not.
extern bool key_state[ALLEGRO_KEY_MAX];
// Mouse state, whether the key is down or not.
// 1 is for left, 2 is for right, 3 is for middle.
extern bool* mouse_state;
// Mouse position.
extern int mouse_x, mouse_y;
// TODO: More variables to store input states such as joysticks, ...

/* Function prototypes */

// Create and start running the game.
void game_create(void);
// Function to change from one scene to another.
void game_change_scene(Scene next_scene);

// Display error message and exit the program, used like 'printf'.
// Write formatted output to stdout and file from the format string.
// If the program crashes unexpectedly, you can inspect "log.txt" for
// further information.
void game_abort(const char* format, ...);
// Log events for later debugging, used like 'printf'.
// Write formatted output to stdout and file from the format string.
// You can inspect "log.txt" for logs in the last run.
void game_log(const char* format, ...);

/* Functions and variables that should be implemented in other files. */

// Initialize shared variables and resources.
// Allows the game to perform any initialization it needs before
// starting to run.
extern void shared_init(void);
// Free shared variables and resources.
extern void shared_destroy(void);
#endif