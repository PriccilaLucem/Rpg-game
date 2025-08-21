#ifndef MENU_TEST_H
#define MENU_TEST_H
#include <stdbool.h>


typedef struct {
    Button startButton;
    Button loadingButton;
    Button optionsButton;
    Button exitButton;
} Buttons;


bool test_render_text(void);

#endif