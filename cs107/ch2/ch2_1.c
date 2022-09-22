// https://web.stanford.edu/class/archive/cs/cs107/cs107.1226/assign2/

#include <stdio.h>
#include <fcntl.h> // for open
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdbool.h>
#include <string.h>

char *get_env_value(char *envp[], char *key);
bool scan_token(const char **p_input, const char *delimiters, char buf[], size_t buflen);
char *concat(char* a, char* b, char* sep, int len_a, int len_b, int len_sep);
void my_which(char *paths, char *argv[]);
int convert_hex_char_to_decimal(char ch);

int main(int argc, char *argv[], char **envp) {
    if (argc <= 1) {
        printf("Must pass in at least 1 argument");
        return -1;
    }

    char *paths = get_env_value(envp, "PATH");
    my_which(paths, argv);
    return 0;
}

void my_which(char *paths, char *argv[]) {
    char buf[512];
    const char *remaining = paths;

    while (scan_token(&remaining, ":", buf, sizeof(buf))) {
       char* path = buf;
       int path_len = strlen(path);
       
       int i = 0;

       while(argv[i] != NULL) {
        char* arg = argv[i];
        int arg_len = strlen(arg);
        char sep = '/';
        char* path_to_check = concat(path, arg, &sep, path_len, arg_len, 1);

        if (access(path_to_check, F_OK) == 0) {
            printf("%s\n", path_to_check);
        }

        free(path_to_check);

        i += 1;
       }
    }
}


char *get_env_value(char *envp[], char *key) {
    int k = 1;

    while (envp[k] != NULL) {
        char* str = envp[k];
        int length = strspn(str, key);

        if (length > 0 && str[length] == '=' && str[length + 1] != '\0') {
            return &str[length + 1];
        }

        k += 1;
    }

    return NULL;
}

bool scan_token(const char **p_input, const char *delimiters, char buf[], size_t buflen) {
    const char*p = p_input[0];
    
    int index = strcspn(p, delimiters);

    int len = index;

    if (len >= buflen) {
        len = buflen;
        strncpy(buf, p, len);
        buf[len - 1] = '\0';
    } else {
        strncpy(buf, p, len);
        buf[len] = '\0';
    }

    *p_input = &p[index + 1];

    return p[index + 1] != '\0';
}

char *concat(char* a, char* b, char* sep, int len_a, int len_b, int len_sep) {
    char *con = malloc(len_a+len_b+2);
    
    memcpy(con,a,len_a);
    memcpy(con+len_a,sep,len_sep);
    memcpy(con+len_a+len_sep,b,len_b+1); 
    
    return con;
}

int convert_hex_char_to_decimal(char ch) {
    if (ch >= '1' && ch <= '9') {
        return ch - 48;
    }
    if (ch >= 'A' && ch <= 'F') {
        return ch - 55;
    }
    if (ch >= 'a' && ch <= 'f') {
        return ch - 87;
    }
    return 0;
}

