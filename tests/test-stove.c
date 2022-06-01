#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../stoved/stove.h"

#define BURNER_COUNT 2

int test_stove_init() {
    printf("stove_init():\n");

    Stove *stove = stove_init(STOVE_ELECTRIC, BURNER_COUNT);
    assert(stove != NULL);

    int ret = stove_clean(stove);
    assert(ret == 0);

    printf("\n");

    return 0;
}

int test_stove_ignite(void) {
    printf("stove_ignite():\n");

    int ret;
    Stove *stove = stove_init(STOVE_ELECTRIC, BURNER_COUNT);

    for (int i=0; i<BURNER_COUNT; i++) {
        Burner *burner = (*stove->burners)[i];
        ret = stove_ignite(burner);
        assert(ret == 0);
        assert(burner->state == BURNER_ON);
        assert(burner->level == 5);
    }

    stove_clean(stove);
    printf("\n");

    return 0;
}

int test_stove_off(void) {
    printf("stove_off():\n");

    int ret;
    Stove *stove = stove_init(STOVE_ELECTRIC, BURNER_COUNT);

    for (int i=0; i<BURNER_COUNT; i++) {
        Burner *burner = (*stove->burners)[i];
        // Burners on
        ret = stove_ignite(burner);

        // Burners off
        ret = stove_off(burner);
        assert(ret == 0);
        assert(burner->state == BURNER_OFF);
        assert(burner->level == 0);
    }

    stove_clean(stove);
    printf("\n");

    return 0;
}

int test_stove_adjust_heat() {
    printf("stove_adjust_heat():\n");

    // Setup
    int ret;
    Stove *stove = stove_init(STOVE_ELECTRIC, BURNER_COUNT);
    Burner *burner = (*stove->burners)[0];

    // Burner on
    stove_ignite(burner);
    // Adjust to valid level
    printf("Adjusting burner\n");
    ret = stove_adjust_heat(burner, BURNER_MAX_HEAT_LEVEL);
    assert(ret == 0);
    assert(burner->level == BURNER_MAX_HEAT_LEVEL);
    // Adjust to invalid level
    printf("Adjusting burner to invalid level\n");
    ret = stove_adjust_heat(burner, BURNER_MAX_HEAT_LEVEL + 1);
    assert(ret == -1);
    // Burner off
    ret = stove_off(burner);
    assert(ret == 0);

    stove_clean(stove);
    printf("\n");

    return 0;
}

int main(void) {
    printf("\n");
    printf("Start stove tests.\n");
    printf("\n");

    test_stove_init();
    test_stove_ignite();
    test_stove_off();
    test_stove_adjust_heat();
    
    printf("All stove tests passed.\n");

    exit(0);
}

