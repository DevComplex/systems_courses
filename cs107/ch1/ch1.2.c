#include <stdio.h>

// https://web.stanford.edu/class/archive/cs/cs107/cs107.1226/assign1/

// ASCII only allows 256 options b/c represented as 1 byte
// C char is 1 byte -> 2^8 = 256
// UTF-8 is backwards compatible with ASCII
// Unicode maps each character to a code point
// U+NNNN => 0xNNNN
// UTF-8 is a type of Unicode encoding
// UTF-8 encoding represents a code point using 1-4 bytes

int to_utf8(unsigned short code_point, unsigned char utf8_bytes[]);

int main() {
    unsigned short code_point = 0x20AC;
    unsigned char utf8_bytes[3];
    int bytes = to_utf8(code_point, utf8_bytes);
    printf("BYTES: [%d]\n", bytes);
    for(int i = bytes - 1; i >= 0; i--) {
        printf("HEX: %x\n", utf8_bytes[i]);
    }
    return 0;
}

int to_utf8(unsigned short code_point, unsigned char utf8_bytes[]) {
    if (code_point <= 0x007F) {
        utf8_bytes[0] = code_point & 0x007F;
        return 1;
    } else if (code_point <= 0x07FF) {
        utf8_bytes[1] = 0xC0 | ((code_point & 0x07C0) >> 6);
        utf8_bytes[0] = 0x80 | (code_point & 0x003F);
        return 2;
    }
    utf8_bytes[2] = 0xE0 | ((code_point & 0xF000) >> 12);
    utf8_bytes[1] = 0x80 | ((code_point & 0x0FC0) >> 6);
    utf8_bytes[0] = 0x80 | (code_point & 0x003F);
    return 3;
}

