/*************************************************
 * CS 2130 Homework 7
 * Spring 2023 - Writing C
 *
 * Computing ID: vgs3qt
 ************************************************/
// ===============================================
// Write your functions here
// TODO: Write functions here
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

void titlecase(char *s) {
    int i = 0;
    int capitalize = 1; // Start with Uppercase letter.
    // Loop until the end of the string.
    while(s[i]) {
        // If current character is a space or is the first character.
        if (capitalize && islower(s[i])) {
            // Convert to uppercase if it is lowercase letter.
            s[i] = toupper(s[i]);
            // Reset the capitalization require.
            capitalize = 0; 
        } 
        else if (s[i] == ' ') {
            // If meet the space, the next letter should be capitalized.
            capitalize = 1;
        } 
        else {
            // Make it false if the current character is not a space.
            capitalize = 0;
        }
        i++;
    }
}


void fibarray(unsigned short *dest, unsigned num) {
    // If num = 0, do nothing.
    if (num == 0) return;  
    // First number is 1.
    if (num >= 1) dest[0] = 1; 
    // Second number is 1.
    if (num >= 2) dest[1] = 1; 
    // Calculate the rest.
    for (unsigned int i = 2; i < num; i++) { 
        // Modulo 65536 to avoid overflow.
        dest[i] = (dest[i-1] + dest[i-2]) % 65536; 
    }
}

long recpow(long x, unsigned char e) {
    // Base case: any number to the power of 0 is 1.
    if (e == 0) { 
        return 1;
    }
    // Recursion case: x^e = x * x^(e-1).
    long temp = recpow(x, e / 2); 
    // If e is even.
    if (e % 2 == 0) { 
        
        return temp * temp;
    } 
    // If e is odd.
    else { 
        return x * temp * temp; 
    }
}

bool isPrime(unsigned long x) {
    // 0 and 1 are not prime numbers
    if (x <= 1) return false; 
    // 2 and 3 are prime numbers
    if (x <= 3) return true;  
    // Exclude even numbers
    if (x % 2 == 0) return false; 
    for (unsigned long i = 3; i * i <= x; i += 2) {
        // x is prime if it is odd and is not a multiple of 
        // any odd number between 3 and √x.
        if (x % i == 0) return false;
        
    }
    return true;
}
unsigned long nextprime(unsigned long x) {
    // The first prime number, 2.
    if (x <= 1) return 2; 
    unsigned long prime = x;
    bool found = false;
    // Loop until isPrime found a prime number.
    while (!found) { 
        // Next prime number.
        prime++; 
        if (isPrime(prime)) {
            found = true;
        }
    }
    // When true, return the prime number we want.
    return prime; 
}

int nondup(int *arr, unsigned length) {
    int result = 0;
    for (unsigned i = 0; i < length; i++) {
        // XORing all elements. Order doesn't matter.
        result ^= arr[i]; 
    }
    // The result is the non-duplicated element.
    return result; 
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
    
    // char *s = strdup(" the book \"the C programming language.\"");
    // printf("before: %s\n", s);
    // titlecase(s);
    // printf("after:  %s\n", s);
    // free(s);

    // unsigned short a[64];
    // fibarray(a, 64);
    // for (int row=0; row<8; row+=1) {
    //     for (int col=0; col<8; col+=1) {
    //         printf(" %04hx", a[row*8 + col]);
    //     }
    // printf("\n");
    // }

    // long x = -21;
    // unsigned char e = 13;
    // long ans = recpow(x, e);
    // printf("%ld\n", ans);
    // printf("%ld\n", recpow(11, 0));

    // long x = 100;
    // for (int i=0; i<10; i+=1) {
    // x = nextprime(x);
    // printf("%ld\n", x);
    // }
    // printf("%ld\n", nextprime(1000000000000));

    // int x[] = {28, 12, 8, 0, 0, 28, 8};
    // printf("%d\n", nondup(x, 7));
    // printf("%d\n", nondup(x + 2, 5));
    return 0;
}
