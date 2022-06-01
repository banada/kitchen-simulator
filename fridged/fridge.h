#include <stdbool.h>
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
 *  Deallocate the fridge
 */
int fridge_clean(Fridge *fridge);

/**
 *  Add food to the fridge
 */
int fridge_add(Fridge *fridge, Food *food);

/**
 *  Remove food from the fridge
 */
Food* fridge_remove(Fridge *fridge, char *food_name);

int fridge_print_contents(Fridge *fridge);

bool fridge_find(Fridge *fridge, char *food_name);
