#include "../food.h"

struct Fridge {
    // m^3
    int size;
    struct Food *(*contents)[];
};

struct Fridge* fridge_init(int size);

/**
 * Deallocate the fridge
 */
int fridge_clean(struct Fridge *fridge);

//int fridge_add(struct Food *food);
//int fridge_remove(struct Food *food);

