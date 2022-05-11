#include <stdio.h>
#include "omelette.h"
#include "kitchen.h"
#include "pan.h"
#include "stove.h"

#define BURNER_COUNT 4

int main(int argc, char *argv[]) {
    int ret;
    struct Pan *pan = NULL;
    struct Stove *stove = NULL;
    
    printf("\n");
    printf("Starting to make an omelette.\n");

    stove = stove_init(STOVE_GAS, BURNER_COUNT);
    if (!stove) {
        return -1;
    }

    pan = init_pan(PAN_SMALL);
    if (!pan) {
        return -1;
    }

    ret = open_cabinet();

    printf("Cleaning up.\n");
    ret = pan_clean(pan);
    ret = stove_clean(stove);

    printf("Done.\n\n");

    return ret;
}
