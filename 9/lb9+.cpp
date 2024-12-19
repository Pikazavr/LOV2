#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <queue>
#include "locale.h"

using namespace std;

void generateAdjacencyMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (i == j) {
                matrix[i][j] = 0;  
            }
            else {
                int edge = rand() % 2;  
                matrix[i][j] = edge;
                matrix[j][i] = edge;
            }
        }
    }
}
void printAdjacencyMatrix(int** matrix, int size) {
    printf("Матрица смежности графа G:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
void findDistances(int** matrix, int size, int startVertex) {
    queue<int> q;

    int* distances = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        distances[i] = -1; 
    }

    // очередь
    q.push(startVertex);
    distances[startVertex] = 0;  // расстояние до 0
    printf("Поиск расстояний от вершины %d:\n", startVertex);
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        // проверка соседей
        for (int i = 0; i < size; i++) {
            if (matrix[current][i] == 1 && distances[i] == -1) {
                distances[i] = distances[current] + 1;
                q.push(i);
            }
        }
    }
    for (int i = 0; i < size; i++) {
        printf("Расстояние до вершины %d: ", i);
        if (distances[i] == -1) {
            printf("недостижима\n");
        }
        else {
            printf("%d\n", distances[i]);
        }
    }

    free(distances);
}
int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(0));

    int size;
    printf("Введите количество вершин графа: ");
    scanf("%d", &size);
    // матриица(выделение памятии)
    int** adjacencyMatrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        adjacencyMatrix[i] = (int*)malloc(size * sizeof(int));
    }
    generateAdjacencyMatrix(adjacencyMatrix, size);
    printAdjacencyMatrix(adjacencyMatrix, size);
    // ввод начальной вершины проверки
    int startVertex;
    printf("Введите начальную вершину для поиска расстояний (0 - %d): ", size - 1);
    scanf("%d", &startVertex);
    if (startVertex >= 0 && startVertex < size) {
        findDistances(adjacencyMatrix, size, startVertex);
    }
    else {
        printf("Неверная начальная вершина!\n");
    }
    for (int i = 0; i < size; i++) {
        free(adjacencyMatrix[i]);
    }
    free(adjacencyMatrix);

    return 0;
}
