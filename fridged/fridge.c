#include <stdio.h>
#include <stdlib.h>
#include "fridge.h"

struct Fridge* fridge_init(int size) {

    struct Fridge *fridge = malloc(sizeof *fridge);
    fridge->size = size;
    fridge->contents = NULL;

    printf("Created a refrigerator with %d cubic meter(s) of storage.\n", size);

    return fridge;
}

int fridge_clean(struct Fridge *fridge) {
    free(fridge);

    return 0;
}

