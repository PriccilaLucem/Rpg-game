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
#define MAX_DESCRIPTION_LENGTH 500
#define MAX_NAME_LENGTH 30

typedef enum {
    STATE_MAIN_MENU,
    STATE_OPTIONS,
    STATE_GAME,
    STATE_OBJ_VIEWER,
    STATE_EXIT
} GameState;

typedef struct {
    int width;
    int height;
    const char* label;
} ScreenResolution;

#endif