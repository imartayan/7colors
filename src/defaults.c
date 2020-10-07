#include "defaults.h"

const char colors[NB_COLORS] = {'R', 'V', 'B', 'J', 'G', 'M', 'C'};

point start1 = {BOARD_SIZE - 1, 0}, start2 = {0, BOARD_SIZE - 1};

const point direction[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
