#include "../food.h"

// Linked list node containing Food
typedef struct FoodNode {
    Food *food;
    struct FoodNode *next;
} FoodNode;

typedef struct Fridge {
    // m^3
    float size;
    // Linked list of fridge contents
    FoodNode *food_node;
    // Number of unique food items
    size_t food_count;
} Fridge;

Fridge* fridge_init(int size);

/**
 * Deallocate the fridge
 */
int fridge_clean(Fridge *fridge);

int fridge_add(Fridge *fridge, Food *food);

int fridge_print_contents(Fridge *fridge);

int fridge_remove(Fridge *fridge, Food *food);

