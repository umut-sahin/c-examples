#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("- Could you enter an integer, please?\n");
    printf("+ ");

    fflush(stdout);

    int entered_integer;
    if (scanf("%d", &entered_integer) != 1) {
        fprintf(stderr, "- You did not enter an integer. That was not nice.\n");
        exit(EXIT_FAILURE);
    }

    printf("- You entered %d. Thank you for your cooperation.\n", entered_integer);

    return EXIT_SUCCESS;
}
