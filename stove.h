struct Stove {
    int type;
    int burner_count;
    struct Burner *(*burners)[];
};

struct Burner {
    int state;
};

enum StoveType {
    STOVE_ELECTRIC = 0,
    STOVE_GAS
};

enum BurnerState {
    BURNER_OFF = 0,
    BURNER_ON
};

struct Stove* stove_init(int type, int burner_count);

//int stove_ignite(int burner);

//int stove_turn_off(int burner);

// TODO set MAX_HEAT_LEVEL
//int stove_adjust_heat(int burner, int heat_level);

