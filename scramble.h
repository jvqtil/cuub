#ifndef SCRAMBLE_H
#define SCRAMBLE_H

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/random.h>

#define DEFAULT_LENGTH 25

static const char* pmoves[3][6] = {
  {"U", "D", "L", "R", "F", "B"},
  {"U'", "D'", "L'", "R'", "F'", "B'"},
  {"U2", "D2", "L2", "R2", "F2", "B2"}
};

char scramble[DEFAULT_LENGTH * 3 + 1];

static int typo_scramble(const char** moves, uint8_t length) {

    uint8_t last_side = 0;

    uint8_t counter = 0;
    // TODO deal with RAND_MAX
    while (counter < length) {
        uint8_t rval = (uint8_t) rand();
        // 3 possible values for set, so 2 bits
        uint8_t set = rval & 3;
        // 6 possible values for side, so 3 bits
        uint8_t side = (rval >> 2) & 7;

        // prevent biasing of results that would occur if
        // we just took the modulus of the values
        if (set == 3 || side > 5) continue;

        // if the side is the same as before, choose another side
        if (counter != 0 && side == last_side) continue;

        moves[counter++] = pmoves[set][side];
        last_side = side;
    }

    return 0;
}

void scramble_gen(void) {
    const char* moves[DEFAULT_LENGTH];
    typo_scramble(moves, DEFAULT_LENGTH);

    int n = 0;
    for (int i = 0; i < DEFAULT_LENGTH; i++)
    n += sprintf(scramble + n, "%s ", moves[i]);
}

#endif
