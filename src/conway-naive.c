#include <stdbool.h>
#include <stdio.h>

void initialize_grid(int size, bool grid[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            grid[i][j] = false;
        }
    }
}

void print_grid(int size, bool grid[size][size]) {
    // drawing board
    printf("+");
    for (int i = 0; i < size; i++)
        printf("--");

    printf("+\n");

    // drawing cells
    for (int i = 0; i < size; i++) {
        printf("|");
        for (int j = 0; j < size; j++) {
            printf("%c ", grid[i][j] ? '*' : ' ');
        }

        printf("|\n");
    }

    // drawing board
    printf("+");
    for (int i = 0; i < size; i++)
        printf("--");

    printf("+\n");
}

int neighbors_number(int size, bool grid[size][size],
                     int i, int j) {
    int neighbors_nb = 0;

    // use the fact that booleans in C are represented by integers to
    // compute the number of neighbors
    for (int k = -1; k <= 1; k++) {
        for (int l = -1; l <= 1; l++) {
            if (k != 0 || l != 0) {
                neighbors_nb +=
                    (grid[(i + k) < 0 ? size - 1 : (i + k) % size]
                     [(j + l) < 0 ? size - 1 : (j + l) % size]);
            }
        }
    }

    return neighbors_nb;
}

void compute_new_grid(int size, bool grid[size][size]) {
    bool compute_grid[size][size];
    initialize_grid(size, compute_grid);

    // compute new live cells
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (grid[i][j] == false &&
                neighbors_number(size, grid, i, j) == 3) {
                compute_grid[i][j] = true;
            }

            if (grid[i][j] == true &&
                ((neighbors_number(size, grid, i, j) == 2) ||
                 (neighbors_number(size, grid, i, j) == 3))) {
                compute_grid[i][j] = true;
            }
        }
    }

    // copy computed grid in the original grid
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            grid[i][j] = compute_grid[i][j];
        }
    }
}

int main(int argc, char *argv[]) {
    bool conway_grid[20][20];
    initialize_grid(20, conway_grid);

    // create a glider
    conway_grid[0][1] = true;
    conway_grid[1][2] = true;
    conway_grid[2][0] = true;
    conway_grid[2][1] = true;
    conway_grid[2][2] = true;

    // print the grid
    print_grid(20, conway_grid);

    // make the grid evolve until the user enters "q"
    char user_input = '\0';

    scanf("%c", &user_input);

    while (user_input != 'q') {
        printf("\n");
        compute_new_grid(20, conway_grid);
        print_grid(20, conway_grid);
        scanf("%c", &user_input);
    }

    printf("\nGood bye Conway!\n");

    return 0;
}
