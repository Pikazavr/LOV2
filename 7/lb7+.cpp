#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "locale.h"

void generateAdjacencyMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (i == j) {
                matrix[i][j] = 0;  // Нет петель
            }
            else {
                int edge = rand() % 2;  // Случайное ребро
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

// Обход в глубину (DFS)
void DFS(int** matrix, int size, int vertex, bool* visited) {
    visited[vertex] = true;
    printf("Вершина пройдена: %d\n", vertex);

    for (int i = 0; i < size; i++) {
        if (matrix[vertex][i] == 1 && !visited[i]) {
            DFS(matrix, size, i, visited);
        }
    }
}

// Инициализация DFS
void depthFirstSearch(int** matrix, int size) {
    bool* visited = (bool*)malloc(size * sizeof(bool));
    for (int i = 0; i < size; i++) {
        visited[i] = false;
    }

    printf("\nОбход в глубину:\n");
    for (int i = 0; i < size; i++) {
        if (!visited[i]) {
            printf("Новая компонента связности:\n");
            DFS(matrix, size, i, visited);
        }
    }

    free(visited);
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(0));

    int size;
    printf("Введите количество вершин графа: ");
    scanf("%d", &size);

    // Создание матрицы смежности
    int** adjacencyMatrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        adjacencyMatrix[i] = (int*)malloc(size * sizeof(int));
    }

    // генерация + вывод матриицы
    generateAdjacencyMatrix(adjacencyMatrix, size);
    printAdjacencyMatrix(adjacencyMatrix, size);

   
    depthFirstSearch(adjacencyMatrix, size);

    
    for (int i = 0; i < size; i++) {
        free(adjacencyMatrix[i]);
    }
    free(adjacencyMatrix);

    return 0;
}
