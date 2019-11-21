#include <error.h>
#include <stdio.h>

int main(void) {
    FILE *p_file = NULL;

    p_file = fopen("fact.txt", "w");

    if (p_file == NULL) {
        error(1, 0, "Cannot write to file fact.txt!\n");
    }

    int fact = 1;

    for (int i = 0; i < 10; i++) {
        fprintf(p_file, "%d! = %d\n", i, fact);

        fact = fact * (i + 1);
    }

    fclose(p_file);

    p_file = NULL;

    return 0;
}
