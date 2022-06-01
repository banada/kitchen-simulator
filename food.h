#ifndef HEADER_FOOD_SEEN
#define HEADER_FOOD_SEEN

typedef struct Food {
    /**
     *  Unique human-readable name
     *  TODO register foods?
     */
    char *name;
    float safe_internal_temp;
    float amt_in_grams;
    int count;
    float temp;
} Food;

/**
 *  Print a single food object
 */
int food_print(Food *food);

#endif /* HEADER_FOOD_SEEN */
