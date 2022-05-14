#ifndef HEADER_FOOD_SEEN
#define HEADER_FOOD_SEEN

struct Food {
    struct Name *name;
    int amt_in_grams;
};

struct Name {
    char *name;
    int count;
};

#endif /* HEADER_FOOD_SEEN */
