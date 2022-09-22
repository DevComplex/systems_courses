// https://web.stanford.edu/class/archive/cs/cs107/cs107.1226/assign3/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct UniqueLine {
    char* line;
    int count;
} UniqueLine;

char *read_line(FILE *file_pointer);
FILE *get_input_file_ptr(int argc, char *filename);
void dealloc_unique_lines(UniqueLine* unique_lines, int size);

int get_n(char* n);
int min(int a, int b);

int main(int argc,  char *argv[]) {
    FILE* fptr = get_input_file_ptr(argc, argv[1]);
    int unique_lines_buffer_len = 32;
    UniqueLine* unique_lines_buffer = malloc(sizeof(UniqueLine) * unique_lines_buffer_len);
    char* line = NULL;
    int i = 0;
    
    do {
        line = read_line(fptr);
        if (line != NULL && strcmp(line, "") != 0) {
            bool does_line_exist = false;
            
            for(int j = 0; j < i; j++) {
                
                // check if that line already exists
                if (strcmp(unique_lines_buffer[j].line, line) == 0) {
                    unique_lines_buffer[j].count += 1;
                    does_line_exist = true;
                }
            }

            if (!does_line_exist) {
                UniqueLine unique_line;
                unique_line.count = 1;
                unique_line.line = line;
                unique_lines_buffer[i] = unique_line;
                i += 1;
            }
        }
        
        if (i == unique_lines_buffer_len) {
            unique_lines_buffer_len *= 2;
            unique_lines_buffer = realloc(unique_lines_buffer, unique_lines_buffer_len);
        }
    } while(line != NULL);

    // print result to stdout
    for(int j = 0; j < i; j++) {
        printf("%s %d\n", unique_lines_buffer[j].line, unique_lines_buffer[j].count);
    }

    // clean up
    dealloc_unique_lines(unique_lines_buffer, i);
    fclose(fptr);

    return 0;
}

int get_n(char* n) {
    if (n == NULL) {
        return 10;
    }
    int converted_n = atoi(n);
    return converted_n == 0 ? 10 : converted_n;
}

char* read_line(FILE *file_pointer) {
    int line_buffer_len = 32;
    char *line_buffer = (char *)(malloc(sizeof(char) * line_buffer_len));
    char *curr_buffer = line_buffer;
    char *r = NULL;
    int prev_index = 0;

    do {
        r = fgets(curr_buffer, line_buffer_len - prev_index, file_pointer);
        
        if (r != NULL) {
            int length_read = strlen(r);
            if (r[length_read - 1] == '\n') {
                r[length_read - 1] = '\0';
                return line_buffer;
            }
            prev_index += length_read;
            if (line_buffer_len - 1 <= prev_index) {
                line_buffer_len *= 2;
                line_buffer = realloc(line_buffer, line_buffer_len);
                curr_buffer = &line_buffer[prev_index];
            }
        }
    } while(r != NULL);

    return NULL;
}

void dealloc_unique_lines(UniqueLine* unique_lines, int size) {
    for(int i = 0; i < size; i++) {
        free(unique_lines[i].line);
    }
    free(unique_lines);
}


int min(int a, int b) {
    return a < b ? a : b;
}

FILE* get_input_file_ptr(int argc, char *filename) {
    if (filename == NULL) {
        return stdin;
    }
    
    FILE* fptr = fopen(filename, "r");

    if (fptr == NULL) {
        printf("Error opening file %s, reverting to STDIN\n", filename);
        return stdin;
    }

    return fptr;
}


