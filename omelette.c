#include <stdio.h>
#include <string.h>
#include "omelette.h"
#include "pan.h"
#include "stoved/stove.h"
#include "fridged/fridge.h"
#include "food.h"

#define BURNER_COUNT 4
#define FRIDGE_SIZE 1

Food meat_table[] = {
    {"Steak",         145.0,  500.0,   0,    0.0},
    {"Pork Chop",     145.0,  500.0,   0,    0.0},
    {"Ground Pork",   160.0,  200.0,   0,    0.0},
    {"Ground Beef",   160.0,  200.0,   0,    0.0},
    {"Egg",           0.0,    0.0,     12,   0.0}
};

// TODO Dynamically add food to the fridge
// TODO allocate a Name/Food and add to fridge

// Statically add food to the fridge
int fill_fridge(Fridge *fridge) {
    int ret = 0;
    size_t meat_table_entries = sizeof(meat_table) / sizeof(Food);
    printf("Meat table has %ld entries\n", meat_table_entries);
    for (int i=0; i<meat_table_entries; i++) {
        printf("Loading %s\n", meat_table[i].name);
        ret = fridge_add(fridge, &(meat_table[i]));
        if (ret < 0) {
            printf("Failed to add %s to fridge.\n", meat_table[i].name);
        }
    }

    return ret;
}

int main(int argc, char *argv[]) {
    int ret;
    struct Pan *pan = NULL;
    struct Stove *stove = NULL;
    struct Fridge *fridge = NULL;
    
    printf("\n");
    printf("Starting to make an omelette.\n");

    stove = stove_init(STOVE_GAS, BURNER_COUNT);
    if (!stove) {
        return -1;
    }

    fridge = fridge_init(FRIDGE_SIZE);
    if (!fridge) {
        return -1;
    }

    pan = init_pan(PAN_SMALL);
    if (!pan) {
        return -1;
    }

    // Fill refrigerator
    printf("Filling fridge.\n");
    ret = fill_fridge(fridge);

    printf("Cleaning up.\n");
    ret = pan_clean(pan);
    ret = stove_clean(stove);

    printf("Done.\n\n");

    return ret;
}

