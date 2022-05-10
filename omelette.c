#include <stdio.h>
#include "omelette.h"
#include "kitchen.h"
#include "pan.h"

int main(int argc, char *argv[]) {
    int ret;
    struct Pan *pan = NULL;
    
    printf("Starting to make an omelette.\n");

    pan = init_pan(PAN_SMALL);
    if (!pan) {
        return -1;
    }

    ret = open_cabinet();

    printf("Cleaning up.\n");
    ret = clean_pan(pan);

    printf("Done.\n");

    return ret;
}
