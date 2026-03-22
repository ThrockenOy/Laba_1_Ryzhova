#ifndef TYPES
#define TYPES

enum ShotResult {
    MISS,
    HIT,
    KILL,
    WIN,
    FIRST_TURN
};

struct Point {
    int x, y;
};

const int FIELD_SIZE = 13;
const int GROUPS_NUM = 6;
const int FLEET_PATTERN[GROUPS_NUM][3] = { {1, 1, 4},
                                           {1, 2, 3},
                                           {1, 3, 2},
                                           {1, 4, 1},
                                           {2, 2, 1},
                                           {2, 3, 1} };  // x size, y size, number


#endif
