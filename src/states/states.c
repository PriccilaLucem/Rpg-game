#include "./states.h"

static int num_state = 0;

int get_num_state(){
    num_state++;
    return num_state;
}