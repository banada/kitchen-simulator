#include <stdio.h>
#include <stdlib.h>
#include "fridge.h"

Fridge* fridge_init(int size) {

    Fridge *fridge = malloc(sizeof *fridge);
    fridge->size = size;
    fridge->food_node = NULL;
    fridge->food_count = 0;

    printf("Created a refrigerator with %d cubic meter(s) of storage.\n", size);

    return fridge;
}

int fridge_clean(Fridge *fridge) {
    free(fridge);

    return 0;
}

int fridge_add(Fridge *fridge, Food *food) {

    // Add food to beginning of the list
    FoodNode *new = malloc(sizeof *new);
    new->food = food;
    new->next = fridge->food_node;
    fridge->food_node = new;

    (fridge->food_count)++;

    printf("Loaded %f grams of %s into fridge.\n",
           fridge->food_node->food->amt_in_grams,
           fridge->food_node->food->name);
    printf("Fridge contains %ld items\n", fridge->food_count);

    return 0;
}

int fridge_remove(Fridge *fridge, Food *food) {

}
