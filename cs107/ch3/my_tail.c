// https://web.stanford.edu/class/archive/cs/cs107/cs107.1226/assign3/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct MyTailResult {
    char** lines;
    int lines_count;
} MyTailResult;

char *read_line(FILE *file_pointer);
FILE *get_input_file_ptr(int argc, char *filename);
MyTailResult get_my_tail_result(FILE* fptr, int n);
void write_my_tail_result_to_stdout(MyTailResult my_tail_result);
MyTailResult new_my_tail_result(char** lines, int lines_count);
void dealloc_my_tail_result(MyTailResult my_tail_result);

int get_n(char* n);
int min(int a, int b);

int main(int argc,  char *argv[]) {
    FILE* fptr = get_input_file_ptr(argc, argv[1]);
    int n = get_n(argv[2]);

    MyTailResult my_tail_result = get_my_tail_result(fptr, n);

    write_my_tail_result_to_stdout(my_tail_result);

    // clean up
    dealloc_my_tail_result(my_tail_result);
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

void write_my_tail_result_to_stdout(MyTailResult my_tail_result) {
    for(int i = 0; i < my_tail_result.lines_count; i++) {
        printf("%s\n", my_tail_result.lines[i]);
    }
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

MyTailResult get_my_tail_result(FILE* fptr, int n) {
    int lines_buffer_len = 32;
    char** lines_buffer = (char **)(malloc(sizeof(char*) * lines_buffer_len));
    int i = 0;
    char* line = NULL;

    do {
        line = read_line(fptr);
        if (line != NULL && strcmp(line, "") != 0) {
            lines_buffer[i] = line;
            i += 1;
        }
        if (i == lines_buffer_len) {
            lines_buffer_len *= 2;
            lines_buffer = realloc(lines_buffer, lines_buffer_len);
        }
    } while(line != NULL);

    int lines_count = min(i, n);
    char** lines = (char **)(malloc(sizeof(char*) * lines_count));

    int count = 0;
    int curr_lines_buffer_index = i - 1;
    int curr_lines_index = lines_count - 1;

    while(curr_lines_buffer_index >= 0 && curr_lines_index >= 0) {
        if (count == lines_count) {
            free(lines_buffer[curr_lines_buffer_index]);
        } else {
            lines[curr_lines_index] = lines_buffer[curr_lines_buffer_index];
            count += 1;
            curr_lines_index -= 1;
        }

        curr_lines_buffer_index -= 1;
    }

    free(lines_buffer);

    return new_my_tail_result(lines, lines_count);
}

MyTailResult new_my_tail_result(char** lines, int lines_count) {
    MyTailResult my_tail_result;
    my_tail_result.lines = lines;
    my_tail_result.lines_count = lines_count;
    return my_tail_result;
}

void dealloc_my_tail_result(MyTailResult my_tail_result) {
    free(my_tail_result.lines);
}
