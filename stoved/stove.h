enum StoveType {
    STOVE_ELECTRIC = 0,
    STOVE_GAS
}; typedef enum StoveType StoveType;

enum BurnerState {
    BURNER_OFF = 0,
    BURNER_ON
}; typedef enum BurnerState BurnerState;

typedef struct Stove {
    StoveType type;
    int burner_count;
    struct Burner *(*burners)[];
} Stove;

typedef struct Burner {
    BurnerState state;
    size_t level;
} Burner;

#define BURNER_MAX_HEAT_LEVEL 10

Stove* stove_init(int type, int burner_count);

/**
 * Deallocate the stove
 */
int stove_clean(Stove *stove);

int stove_ignite(Burner *burner);

int stove_off(Burner *burner);

int stove_adjust_heat(Burner *burner, size_t heat_level);

