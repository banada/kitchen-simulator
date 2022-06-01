#include <stdio.h>
#include <stdlib.h>
#include "food.h"

int food_print(Food *food) {

    printf("Name:               %s\n", food->name);
    printf("Safe Internal Temp: %f\n", food->safe_internal_temp);
    printf("Amount (grams):     %f\n", food->amt_in_grams);
    printf("Count:              %d\n", food->count);
    printf("Temp:               %f\n", food->temp);
    printf("================================\n");
    printf("\n");

    return 0;
}

