#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
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

static void handle_sigterm() {
    printf("\nReceived SIGTERM, terminating.\n");
    exit(0);
}

static void handle_sigint() {
    printf("\nReceived SIGINT, exiting.\n");
    exit(0);
}

int main(void) {
    stove_init(STOVE_GAS, 5);
    // stoved starts with no stoves, you need to configure
    // your own kitchen. A kitchen can have many stoves.
    // TODO register stoves with stoved

    // System signal handlers
    struct sigaction sigterm, sigint;
    // SIGTERM
    sigterm.sa_flags = 0;
    // Signals to be blocked during handler exec
    sigemptyset(&sigterm.sa_mask);
    sigterm.sa_handler = handle_sigterm;
    sigaction(SIGTERM, &sigterm, NULL);
    // SIGINT
    sigint.sa_flags = 0;
    sigemptyset(&sigint.sa_mask);
    sigint.sa_handler = handle_sigint;
    sigaction(SIGINT, &sigint, NULL);

    while(1) {

    }
}

