#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "locale.h"

#define N 5  // Количество вершин графа

// Генерация матрицы смежности
void generateAdjacencyMatrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
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

// Печать матрицы смежности
void printAdjacencyMatrix(int matrix[N][N]) {
    printf("Матрица смежности графа G:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Обход в глубину (DFS)
void DFS(int matrix[N][N], int vertex, bool visited[N]) {
    visited[vertex] = true;
    printf("вершина пройдена %d\n", vertex);

    for (int i = 0; i < N; i++) {
        if (matrix[vertex][i] == 1 && !visited[i]) {
            DFS(matrix, i, visited);
        }
    }
}

// Инициализация DFS
void depthFirstSearch(int matrix[N][N]) {
    bool visited[N] = { false };  // Массив посещённых вершин

    printf("\nОбход в глубину:\n");
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            printf("Новая компонента связности:\n");
            DFS(matrix, i, visited);
        }
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(0));
    int adjacencyMatrix[N][N];

    // печать матриц 
    generateAdjacencyMatrix(adjacencyMatrix);
    printAdjacencyMatrix(adjacencyMatrix);

    // обход в глубину 
    depthFirstSearch(adjacencyMatrix);

    return 0;
}
