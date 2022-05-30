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

// Traverse the linked list and remove a food by name
int fridge_remove(Fridge *fridge, char *food_name) {

    FoodNode *prev = NULL;
    FoodNode *current = fridge->food_node;

    // End of list
    while (current != NULL) {
        printf("%s\n", current->food->name);
        // Found
        if (current->food->name == food_name) {
            printf("Found %s in the fridge, removing\n", food_name);
            prev->next = current->next;
            free(current);
            return 0;
        }

        prev = current;
        current = current->next;
    }

    // Failed to find
    return -1;
}

int fridge_list(Fridge *fridge) {
    FoodNode *tmp = fridge->food_node;

    printf("\n");
    while (tmp != NULL) {
        printf("Name:               %s\n", tmp->food->name);
        printf("Safe Internal Temp: %f\n", tmp->food->safe_internal_temp);
        printf("Amount (grams):     %f\n", tmp->food->amt_in_grams);
        printf("Count:              %d\n", tmp->food->count);
        printf("Temp:               %f\n", tmp->food->temp);
        printf("================================\n");
        printf("\n");

        tmp = tmp->next;
    }

    return 0;
}
