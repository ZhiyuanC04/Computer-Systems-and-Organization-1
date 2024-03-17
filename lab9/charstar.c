#include <stdio.h>
size_t mystrlen(const char *s) {
    size_t length = 0;
    while (*s++) {
        length++;
    }
    return length;
}

char *simple_split(char *s, char delim) {
   
    char *ptr = s;
    while (*ptr != '\0') {
        if (*ptr == delim) {
            *ptr = '\0'; 
            return ptr + 1; 
        }
        ptr++;
    }
    return NULL;
}