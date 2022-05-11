#include <stdio.h>
#include <stdlib.h>
#include "pan.h"

const char *PanSizeStr[] = {
    "small",
    "medium",
    "large"
};

/**
 *  Create a pan
 *  Returns a pointer to a Pan
 */
struct Pan* init_pan(enum PanSize pan_size) {
    // Allocate memory for the pan
    struct Pan *pan = malloc(sizeof *pan);

    pan->size = pan_size;
    pan->state = PAN_DOWN;
    printf("Created a %s pan\n", PanSizeStr[pan->size]);

    return pan;
}

int clean_pan(struct Pan *pan) {
    // Deallocate the pan
    free(pan);

    return 0;
}
