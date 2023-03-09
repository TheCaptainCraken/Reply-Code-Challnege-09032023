#include <stdio.h>
#include <stdlib.h>

#define WORMHOLE -10001

typedef struct point_s {
    int x, y, value;
} Point;

void print_state(int**, int, int, int*, int);
Point* find_best_starting_points(int**, int, int);
void swap(Point*, Point*);
int partition(Point*, int, int);
void quick_sort(Point*, int, int);

int main(int argc, char** argv) {

    //Allocation of stuff
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

    //creating a Point array that contains every point ordered in descending order by its value in the map.
    Point* ordered_starting_points = find_best_starting_points(map, rows, columns);
    int number_of_points = rows * columns;
    for (int i = 0; i < number_of_points; i++) {
        printf("%d @ (%d, %d)\n", ordered_starting_points[i].value, ordered_starting_points[i].x, ordered_starting_points[i].y);
    }

    // free the memory? nah.
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

Point* find_best_starting_points(int** map, int rows, int columns) {
    int length = rows * columns;
    Point* best_points = (Point*)malloc(sizeof(Point) * length);
    if (best_points == NULL) {
        printf("Malloc for the best points failed!\n");
        return NULL;
    }

    for (int point = 0; point < length; point++) {
        best_points[point].value = WORMHOLE;
        best_points[point].x = -1;
        best_points[point].y = -1;
    }

    int i = 0;
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            best_points[i].value = map[row][column];
            best_points[i].x = row;
            best_points[i].y = column;
            i++;
        }
    }

    quick_sort(best_points, 0, length - 1);

    return best_points;

}

void swap(Point* a, Point* b) {
    Point temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Point arr[], int low, int high) {
    int pivot = arr[high].value;
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j].value > pivot) {  // modified condition
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quick_sort(Point arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}