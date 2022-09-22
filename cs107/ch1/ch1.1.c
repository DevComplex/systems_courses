#include <stdio.h>
#include <stdlib.h>

char* draw_generation(unsigned long gen);
unsigned long advance(unsigned long gen, unsigned char ruleset);

int main(int argc, char *argv[]) {
    char *ptr;
    unsigned long curr_gen = 99999912323;
    char ruleset = 'Z';
    unsigned long prev_gen = curr_gen;

    do {
        draw_generation(curr_gen);
        unsigned long next_gen = advance(curr_gen, ruleset);
        prev_gen = curr_gen;
        curr_gen = next_gen;
    } while(curr_gen != prev_gen);

    return 0;
}

char* draw_generation(unsigned long gen) {
    char generation[65];

    for(int i = 0, j = 63; i < 64 && j >= 0; i++, j--) {
       int bitStatus = (gen >> i) & 1;

       if (bitStatus == 0) {
        generation[j] = ' ';
       } else {
        generation[j] = '+';
       }
    }

    generation[64] = '\0';

    printf("%s\n", generation);

    return generation;
}

unsigned long advance(unsigned long gen, unsigned char ruleset) {
    unsigned long next_gen = 0;

    for(int i = 0, j = 63; i < 64 && j >= 0; i++, j--) {
       int prev_cell_bit = i > 0 ? (gen >> (i - 1)) & 1 : 0;
       int curr_cell_bit = (gen >> i) & 1;
       int next_cell_bit = i == 63 ? 0 : (gen >> (i + 1)) & 1;
       int neighborhood = prev_cell_bit * 1 + curr_cell_bit * 2 + next_cell_bit * 4;
       int ruleset_bit = (ruleset >> neighborhood) & 1;
       
       if (ruleset_bit == 1) {
        next_gen = (1 << i) | next_gen;
       }
    }

    return next_gen;
}
