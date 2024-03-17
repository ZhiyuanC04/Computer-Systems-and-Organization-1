/*************************************************
 * CS 2130 Homework 7
 * Spring 2023 - Writing C
 *
 * Computing ID: bhb9ba
 ************************************************/

// ===============================================
// Write your functions here: Titlecase, Fibonacci Array, Recursive Power, Pull Zeros,

// TODO: Write functions here

// Function to convert the first character after a space to uppercase
#include <stdio.h>
#include <math.h>
#include <ctype.h>
void titlecase(char *s) {
    if (s[0] != '\0' ) {
        s[0] = toupper((unsigned char)s[0]);
    }
    for (int i = 1; s[i] != '\0'; ++i) {
        if (s[i-1] == ' ') {
            s[i] = toupper((unsigned char)s[i]);
        }
}}

long recpow(long x, unsigned char e){
    if (e == 0) {
        return 1;
    }
    if (e == 1) {
        return x;
    }
    return x * recpow(x, e - 1);}


void fibarray(unsigned short *dest, unsigned num) {
    if (dest == NULL || num == 0) 
        return;
    unsigned short a = 0, b = 1;
    for (unsigned i = 0; i < num; ++i) {
        if (i == 1) {
            dest[i] = b;
        } else {
            unsigned short next = (a + b) % 65536;
            dest[i] = next;
            a = b;
            b = next;
        }
    }
}

int nondup(int *arr, unsigned length) {
    for (unsigned i = 0; i < length; i++) {
        int a = 0;
        for (unsigned j = 0; j < length; j++) {
            if (arr[i] == arr[j]) {
                a++;
            }
        }
        if (a == 1) {
            return arr[i];
        }
    }
    return -1;
}

void pull0(int *arr, unsigned length) {
    unsigned Count = 0;
    for (unsigned i = 0; i < length; ++i) {
        if (arr[i] == 0) {
            Count++;
        }
    }
    if (Count == 0) return;
    unsigned nonZero = length - 1;
    for (int i = length - 1; i >= 0; i--) {
        if (arr[i] != 0) {
            arr[nonZero--] = arr[i];
        }
    }
    for (unsigned i = 0; i < Count; i++) {
        arr[i] = 0;
    }
}
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Update the followng main function to test your
// code.  You should test normal input values as
// well as edge cases.  Do NOT rely only on the
// Gradescope submission site, as submissions are
// limited.
// Note: You must leave this comment block to ensure
// proper grading of your submission.


int main() {
    // TODO: Add tests here
    int x[] = {1, 7, 3, 2, 0, 5, 0, 8, 0, 7, 5, 6, 8, 8, 7, 7, 2, 9};
    for (int i=0; i<18; i+=1) printf("%d ", x[i]); printf("\n");
    pull0(x, 15);
    for (int i=0; i<18; i+=1) printf("%d ", x[i]); printf("\n");
    }

