#include "backpack.h"
#include "./inventory.h"


static void addItem(playerInventory* inventory, Itens* item) {
    inventory->itens = realloc(inventory->itens, sizeof(Itens*) * (inventory->item_count + 1));
    inventory->itens[inventory->item_count] = item;
    inventory->item_count++;
}

static void removeItem(playerInventory* inventory, int item_id) {
    for (size_t i = 0; i < inventory->item_count; i++) {
        if (inventory->itens[i]->id == item_id) {
            for (size_t j = i; j < inventory->item_count - 1; j++) {
                inventory->itens[j] = inventory->itens[j + 1];
            }
            inventory->item_count--;
            inventory->itens = realloc(inventory->itens, sizeof(Itens*) * inventory->item_count);
            return;
        }
    }
}


playerInventory* init_player_inventory(size_t max_weight, size_t button_size) {
    playerInventory* inv = malloc(sizeof(playerInventory) + button_size);
    inv->id = get_num_state();

    memset(inv->button, 0, button_size);
    
    inv->max_weight = max_weight;
    inv->weight = 0;
    inv->itens = NULL;
    inv->item_count = 0;

    inv->addItem = addItem;
    inv->removeItem = removeItem;
    inv->listItems = NULL;

    return inv;
}
