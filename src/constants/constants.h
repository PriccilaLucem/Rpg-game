#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MENU_FONT_PATH "src/assets/fonts/Luckiest_Guy,Playfair_Display/Luckiest_Guy/LuckiestGuy-Regular.ttf"
#define MAX_BUTTON_LENGTH 50
#define NUM_RESOLUTIONS 6
#define NUM_RESOLUTIONS 6
#define ARROW_LEFT 0
#define ARROW_RIGHT 1
#define ARROW_UP 2
#define ARROW_DOWN 3
#define SCREEN_W 800
#define SCREEN_H 600


typedef enum {
    STATE_MAIN_MENU,
    STATE_OPTIONS,
    STATE_GAME,
    STATE_EXIT
} GameState;

typedef struct {
    int width;
    int height;
    const char* label;
} ScreenResolution;

#endif