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
