#include "../food.h"

typedef struct Fridge {
    // m^3
    float size;
    struct Food *(*contents)[];
    size_t contents_size;
} Fridge;

Fridge* fridge_init(int size);

/**
 * Deallocate the fridge
 */
int fridge_clean(Fridge *fridge);

int fridge_add(Fridge *fridge, Food *food);
//int fridge_remove(struct Food *food);

