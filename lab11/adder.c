#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char* argv[]) {
    int len = 11;
    char type;
    float f1, f2;
    int i1, i2;
    char str1[len], str2[len];

    if (argc == 2) {
        if (strcmp(argv[1], "-i") == 0) {
            type = 'I';
        } else if (strcmp(argv[1], "-f") == 0) {
            type = 'F';
        } else if (strcmp(argv[1], "-s") == 0) {
            type = 'S';
        } else {
            printf("Invalid flag supplied\n");
            return 1;
        }
    } else {
        printf("What types of values do you want to add (I/F/S): ");
        scanf(" %c", &type);
    }

    switch (type) {
        case 'I':
            printf("Enter two integers: ");
            scanf("%d %d", &i1, &i2);
            printf("The result is: %d\n", i1 + i2);
            break;
        case 'F':
            printf("Enter two floats: ");
            scanf("%f %f", &f1, &f2);
            printf("The result is: %.8g\n", f1 + f2);
            break;
        case 'S':
            printf("Enter two strings (up to 10 characters each): ");
            scanf("%10s %10s", str1, str2);
            strcat(str1, str2);
            printf("The result is: %s\n", str1);
            break;
        default:
            printf("Invalid type. Please enter I, F, or S.\n");
            return 1;
    }

    return 0;
}
