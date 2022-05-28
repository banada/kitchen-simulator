#include <stdio.h>
#include <stdlib.h>
#include "fridge.h"

Fridge* fridge_init(int size) {

    Fridge *fridge = malloc(sizeof *fridge);
    fridge->size = size;
    fridge->contents = NULL;
    fridge->contents_size = 0;

    printf("Created a refrigerator with %d cubic meter(s) of storage.\n", size);

    return fridge;
}

int fridge_clean(Fridge *fridge) {
    free(fridge);

    return 0;
}

int fridge_add(Fridge *fridge, Food *food) {
    // Track size of fridge contents array
    size_t *size = &(fridge->contents_size);
    (*size)++;

    // Grow the array
    Food *(*temp)[] = realloc(fridge->contents,
                              (*size) * sizeof(Food*));
    if (temp == NULL) {
        free(fridge->contents);
        return -1;
    }
    if (temp != fridge->contents) {
        free(fridge->contents);
    }
    fridge->contents = temp;

    size_t idx = *size - 1;
    (*fridge->contents)[idx] = food;

    printf("Loaded %f grams of %s into fridge.\n",
           (*fridge->contents)[idx]->amt_in_grams,
           (*fridge->contents)[idx]->name);
    printf("Fridge contains %ld items\n", *size);

    return 0;
}

