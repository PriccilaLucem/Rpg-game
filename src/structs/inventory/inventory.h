#ifndef INVENTORY_H
#define INVENTORY_H

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../itens/itens.h"

typedef struct playerInventory {
    int id;
    size_t max_weight;
    size_t weight;
    char button[];
    Itens** itens;      
    size_t item_count;

    void (*addItem)(struct playerInventory* inventory, Itens* item);
    void (*removeItem)(struct playerInventory* inventory, int item_id);
    void (*listItems)(struct playerInventory* inventory);

} playerInventory;

playerInventory* init_player_inventory(size_t max_weight, size_t button_size);

#endif
