#include <stdio.h>
#include "omelette.h"
#include "kitchen.h"

int main(int argc, char *argv[]) {
    int is_cabinet_open;
    
    printf("%d\n", START_MSG);
    printf("Starting to make an omelette.\n");
    is_cabinet_open = open_cabinet();
    printf("%d\n", is_cabinet_open);
    return 0;
}
