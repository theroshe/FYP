
#include <stdio.h>

int main(int argc, char** argv)
{
    unsigned int number = 2;
    unsigned int exponent = 2;
    unsigned int i;

    for(i = 1; i < exponent; i++) {
        number = number * number;
    }

    printf("Result: %d\n", number);

    return 0;
}
