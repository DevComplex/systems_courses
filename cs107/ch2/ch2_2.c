#include <stdio.h>
#include <stdlib.h>

void print_diamond(char* word);

int main() {
    print_diamond("HELLO");
    return 0;
}

void print_diamond(char* word) {
    int i = 0;

    while (word[i] != '\0') {
        char* partial_word = (char *)(malloc((i + 2)*sizeof(char)));
        for(int j = 0; j <= i; j++) {
            partial_word[j] = word[j];
        }
        partial_word[i + 1] = '\0';
        printf("%s\n", partial_word);
        free(partial_word); 
        i += 1;
    }

    int length = i - 1;
    i = length;

    while (i >= 0) {
        char* partial_word = (char *)malloc((length+1)*sizeof(char));
        partial_word[length] = '\0';

        for(int j = length; j >= 0; j--) {
            if (j >= i) {
                partial_word[j] = word[j];
            } else {
                partial_word[j] = ' ';
            }
        }

        printf("%s\n", partial_word);

        free(partial_word); 

        i -= 1;
    }
}