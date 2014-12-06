
#ifndef _SETTINGS_H
#define _SETTINGS_H

// set to true or false
#define FULLSCREEN_ENABLED		false

// resolution
#define SCREEN_WIDTH			1024
#define SCREEN_HEIGHT			768

// defines the xml-file from where the menu structure will be loaded
#define MENU_STRUCTURE_FILE		"menu_structure.xml"

// defines where the fonts and images of the theme are
#define THEME_FOLDER			"themes/test"

// defines from where the thumbnails will be loaded
#define THUMBNAILS_FOLDER		"thumbnails"

// Key bindings
#define INPUT_KEY_UP			SDL_SCANCODE_UP
#define INPUT_KEY_DOWN			SDL_SCANCODE_DOWN
#define INPUT_KEY_LEFT			SDL_SCANCODE_LEFT
#define INPUT_KEY_RIGHT			SDL_SCANCODE_RIGHT

#define INPUT_KEY_FIRE			SDL_SCANCODE_SPACE
#define INPUT_KEY_BACK			SDL_SCANCODE_ESCAPE
#define INPUT_KEY_QUIT			SDL_SCANCODE_F1

#endif
