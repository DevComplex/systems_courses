#include <stdio.h>
#include <limits.h>

// https://web.stanford.edu/class/archive/cs/cs107/cs107.1226/assign1/

int to_utf8(unsigned short code_point, unsigned char utf8_bytes[]);
long signed_min(int bitwidth);
long signed_max(int bitwidth);
long sat_add(long operand1, long operand2, int bitwidth);

int main() {
    printf("%ld\n", sat_add(LONG_MIN, -20, 64));
    printf("%lx\n", signed_min(64));
    printf("%lx\n", signed_max(64));
    printf("%ld\n", sat_add(4, 4, 4));
    return 0;
}

long signed_min(int bitwidth) {
    return LONG_MAX << (bitwidth - 1);
}

long signed_max(int bitwidth) {
    return ~signed_min(bitwidth);
}

long sat_add(long operand1, long operand2, int bitwidth) {
    long min = signed_min(bitwidth);
    long max = signed_max(bitwidth);
    long sum = operand1 + operand2;
    if ((operand1 > 0 && operand2 > 0 && sum < 0) || sum > max) {
        return max;
    }
    if ((operand1 < 0 && operand2 << 0 && sum > 0) || sum < min) {
        return min;
    }
    return sum;
}
