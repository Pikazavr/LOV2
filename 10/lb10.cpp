#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <queue>
#include "locale.h"

using namespace std;

// Генерация матрицы смежности для взвешенного графа
void generateWeightedAdjacencyMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (i == j) {
                matrix[i][j] = 0; // Отсутствие петли
            }
            else {
                int weight = rand() % 10 + 1; // Генерация веса ребра (1-10)
                matrix[i][j] = weight;
                matrix[j][i] = weight;
            }
        }
    }
}

// Печать матрицы смежности
void printAdjacencyMatrix(int** matrix, int size) {
    printf("Матрица смежности графа G:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Алгоритм поиска расстояний (ПОШ)
void findDistances(int** matrix, int size, int startVertex) {
    queue<int> q; // Очередь для BFS
    int* distances = (int*)malloc(size * sizeof(int));

    // Инициализация расстояний
    for (int i = 0; i < size; i++) {
        distances[i] = -1; // Все вершины помечены как "не посещённые"
    }

    q.push(startVertex);         // Помещаем начальную вершину в очередь
    distances[startVertex] = 0;  // Расстояние до начальной вершины = 0

    printf("Поиск расстояний от вершины %d:\n", startVertex);

    // Алгоритм BFSD
    while (!q.empty()) {
        int current = q.front(); // Текущая вершина
        q.pop();                 // Удаляем вершину из очереди
        printf("Посещена вершина: %d\n", current);

        // Проверка соседей
        for (int i = 0; i < size; i++) {
            if (matrix[current][i] > 0 && distances[i] == -1) { // Если есть связь и вершина не посещена
                distances[i] = distances[current] + matrix[current][i]; // Обновляем расстояние
                q.push(i); // Добавляем вершину в очередь
            }
        }
    }

    // Вывод расстояний
    printf("\nРезультаты поиска расстояний:\n");
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

    // Выделение памяти для матрицы смежности
    int** adjacencyMatrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        adjacencyMatrix[i] = (int*)malloc(size * sizeof(int));
    }

    // Генерация и печать матрицы смежности
    generateWeightedAdjacencyMatrix(adjacencyMatrix, size);
    printAdjacencyMatrix(adjacencyMatrix, size);

    // Ввод начальной вершины
    int startVertex;
    printf("Введите начальную вершину для поиска расстояний (0 - %d): ", size - 1);
    scanf("%d", &startVertex);

    // Проверка корректности ввода и вызов алгоритма
    if (startVertex >= 0 && startVertex < size) {
        findDistances(adjacencyMatrix, size, startVertex);
    }
    else {
        printf("Неверная начальная вершина!\n");
    }

    // Освобождение памяти
    for (int i = 0; i < size; i++) {
        free(adjacencyMatrix[i]);
    }
    free(adjacencyMatrix);

    return 0;
}
