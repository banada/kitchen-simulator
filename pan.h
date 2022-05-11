#include "food.h"

struct Pan {
    int size;
    int state;
    struct Food *contents;
};

enum PanSize {
    PAN_SMALL = 0,
    PAN_MEDIUM,
    PAN_LARGE
};

enum PanState {
    PAN_UP = 0,
    PAN_DOWN
};

/*
 *  Initialize a Pan of a certain size
 */
struct Pan* init_pan(enum PanSize pan_size);

/**
 *  Deinitialize a Pan
 */
int pan_clean(struct Pan *pan);

//int add_to_pan(struct Pan *pan, struct Food *contents);

//int remove_from_pan(struct Pan *pan, struct Food *contents);

//int pick_up_pan(struct Pan *pan);

//int flip(struct Pan *pan);

//int set_down_pan(struct Pan *pan);

