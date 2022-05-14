#include <stdio.h>
#include "omelette.h"
#include "pan.h"
#include "stoved/stove.h"
#include "fridged/fridge.h"

#define BURNER_COUNT 4
#define FRIDGE_SIZE 1

int main(int argc, char *argv[]) {
    int ret;
    struct Pan *pan = NULL;
    struct Stove *stove = NULL;
    struct Fridge *fridge = NULL;
    
    printf("\n");
    printf("Starting to make an omelette.\n");

    stove = stove_init(STOVE_GAS, BURNER_COUNT);
    if (!stove) {
        return -1;
    }

    fridge = fridge_init(FRIDGE_SIZE);
    if (!fridge) {
        return -1;
    }

    pan = init_pan(PAN_SMALL);
    if (!pan) {
        return -1;
    }

    printf("Cleaning up.\n");
    ret = pan_clean(pan);
    ret = stove_clean(stove);

    printf("Done.\n\n");

    return ret;
}
