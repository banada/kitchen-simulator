#include "food.h"

struct Pan {
    PanSize size;
    Food *contents;
    PanState state;
};

enum PanSize {
    SMALL = 0,
    MEDIUM,
    LARGE
};

enum PanState {
    UP = 0,
    DOWN
};

struct Pan *pan create_pan(pan_size);

int add_to_pan(struct Pan *pan, struct Food *contents);

int remove_from_pan(struct Pan *pan, struct Food *contents);

int pick_up_pan(struct Pan *pan);

int flip(struct Pan *pan);

int set_down_pan(struct Pan *pan);

