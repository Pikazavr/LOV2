#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <locale.h>

// Генерация матрицы смежности для взвешенного графа
void generateWeightedAdjacencyMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                matrix[i][j] = 0; // Отсутствие петли
            }
            else {
                matrix[i][j] = rand() % 10 + 1; // Генерация веса ребра (1-10)
            }
        }
    }
}

// Печать матрицы
void printMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] == INT_MAX) {
                printf("INF ");
            }
            else {
                printf("%d ", matrix[i][j]);
            }
        }
        printf("\n");
    }
}

// Алгоритм Флойда-Уоршелла для поиска кратчайших путей
void floydWarshall(int** graph, int size, int** distances) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                distances[i][j] = 0;
            }
            else if (graph[i][j] > 0) {
                distances[i][j] = graph[i][j];
            }
            else {
                distances[i][j] = INT_MAX;
            }
        }
    }

    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (distances[i][k] != INT_MAX && distances[k][j] != INT_MAX &&
                    distances[i][j] > distances[i][k] + distances[k][j]) {
                    distances[i][j] = distances[i][k] + distances[k][j];
                }
            }
        }
    }
}

// Построение матрицы достижимости
void buildReachabilityMatrix(int** distances, int size, int** reachability) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            reachability[i][j] = (distances[i][j] != INT_MAX) ? 1 : 0;
        }
    }
}

// Вычисление эксцентриситетов, радиуса и диаметра графа
void calculateEccentricities(int** distances, int size) {
    int* eccentricities = (int*)malloc(size * sizeof(int));
    int radius = INT_MAX;
    int diameter = 0;

    for (int i = 0; i < size; i++) {
        int maxDistance = 0;
        for (int j = 0; j < size; j++) {
            if (distances[i][j] != INT_MAX && distances[i][j] > maxDistance) {
                maxDistance = distances[i][j];
            }
        }
        eccentricities[i] = maxDistance;
        if (maxDistance < radius) {
            radius = maxDistance;
        }
        if (maxDistance > diameter) {
            diameter = maxDistance;
        }
    }

    printf("\nЭксцентриситеты вершин:\n");
    for (int i = 0; i < size; i++) {
        printf("Вершина %d: %d\n", i, eccentricities[i]);
    }

    printf("\nРадиус графа: %d\n", radius);
    printf("Диаметр графа: %d\n", diameter);

    free(eccentricities);
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(0));

    int size;
    printf("Введите количество вершин графа: ");
    scanf("%d", &size);

    // Выделение памяти для матрицы смежности
    int** adjacencyMatrix = (int**)malloc(size * sizeof(int*));
    int** distances = (int**)malloc(size * sizeof(int*));
    int** reachabilityMatrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        adjacencyMatrix[i] = (int*)malloc(size * sizeof(int));
        distances[i] = (int*)malloc(size * sizeof(int));
        reachabilityMatrix[i] = (int*)malloc(size * sizeof(int));
    }

    // Генерация и печать матрицы смежности
    generateWeightedAdjacencyMatrix(adjacencyMatrix, size);
    printf("Матрица смежности:\n");
    printMatrix(adjacencyMatrix, size);

    // Поиск кратчайших путей
    floydWarshall(adjacencyMatrix, size, distances);
    printf("\nМатрица кратчайших расстояний:\n");
    printMatrix(distances, size);

    // Построение матрицы достижимости
    buildReachabilityMatrix(distances, size, reachabilityMatrix);
    printf("\nМатрица достижимости:\n");
    printMatrix(reachabilityMatrix, size);

    // Вычисление эксцентриситетов, радиуса и диаметра
    calculateEccentricities(distances, size);

    // Освобождение памяти
    for (int i = 0; i < size; i++) {
        free(adjacencyMatrix[i]);
        free(distances[i]);
        free(reachabilityMatrix[i]);
    }
    free(adjacencyMatrix);
    free(distances);
    free(reachabilityMatrix);

    return 0;
}