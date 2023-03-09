#include <stdio.h>
#include <stdlib.h>

#define WORMHOLE -10001

typedef struct point_s {
    int x, y;
} Point;

void print_state(int**, int, int, int*, int);

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: run <input_file_path>");
        return -1;
    }
    FILE* input_file = fopen(argv[1], "r");

    int columns = -1;
    int rows = -1;
    int number_of_snakes = -1;
    int* snake_lentghs = NULL;
    int** map = NULL;

    fscanf(input_file, "%d %d %d", &rows, &columns, &number_of_snakes);


    snake_lentghs = (int*)malloc(sizeof(int) * number_of_snakes);
    if (snake_lentghs == NULL) {
        printf("Malloc for snake lenghts failed.\n");
        return -1;
    }

    for (int snake = 0; snake < number_of_snakes; snake++) {
        fscanf(input_file, "%d", &snake_lentghs[snake]);
    }

    map = (int**)malloc(sizeof(int*) * rows);
    if (map == NULL) {
        printf("Malloc for map rows failed.\n");
        return -1;
    }
    for (int i = 0; i < rows; i++) {
        map[i] = (int*)malloc(sizeof(int) * columns);
        if (map[i] == NULL) {
            printf("Malloc for map column number %d failed.\n", i);
            return -1;
        }
    }

    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            fscanf(input_file, "%d", &map[row][column]);
        }
    }

    print_state(map, rows, columns, snake_lentghs, number_of_snakes);
    return 0;
}

void print_state(int** map, int rows, int columns, int* snake_lenghts, int number_of_snakes) {
    printf("There are %d snakes. Below are their lenghts:\n", number_of_snakes);
    printf("[");
    for (int i = 0; i < number_of_snakes; i++) {
        printf("%d, ", snake_lenghts[i]);
    }
    printf("]\n");

    printf("The map has %d rows and %d columns. Below there's a representation of it. WHORMHOLES are represented with the '#' character:\n", rows, columns);
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            if (map[row][column] == WORMHOLE) {
                printf("# ");
            } else {
                printf("%d ", map[row][column]);
            }
        }
        printf("\n");
    }
}