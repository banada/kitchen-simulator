#include <stdio.h>
#include <stdlib.h>
#include "stove.h"

const char *StoveTypeStr[] = {
    "electric",
    "gas"
};

const char *BurnerStateStr[] = {
    "off",
    "on"
};

struct Stove* stove_init(int type, int burner_count) {

    struct Stove *stove = malloc(sizeof *stove);

    stove->type = type;
    stove->burner_count = burner_count;

    // Initialize Burners
    // Create an array to hold Burner pointers
    struct Burner *burners[stove->burner_count];
    // Allocate each burner
    for (int i=0; i<stove->burner_count; i++) {
        burners[i] = malloc(sizeof(struct Burner));
        burners[i]->state = BURNER_OFF;
    }
    // Point to the array we created
    stove->burners = &burners;

    printf("Created a %d burner %s stove\n",
           stove->burner_count,
           StoveTypeStr[stove->type]);

    for (int i=0; i<stove->burner_count; i++) {
        int state = (*stove->burners)[i]->state;
        printf("Burner %d is %s\n",
               i,
               BurnerStateStr[state]);
    }

    return stove;
}

int stove_clean(struct Stove *stove) {
    free(stove);

    return 0;
}

/**
 *  Start the burner and set to mid
 */
int stove_ignite(Burner *burner) {
    burner->state = BURNER_ON;
    burner->level = 5;

    return 0;
}

int stove_off(Burner *burner) {
    burner->level = 0;
    burner->state = BURNER_OFF;

    return 0;
}

int stove_adjust_heat(Burner *burner, size_t heat_level) {
    if (heat_level > BURNER_MAX_HEAT_LEVEL) {
        printf("Invalid heat level\n");

        return -1;
    }

    burner->level = heat_level;

    return 0;
}

