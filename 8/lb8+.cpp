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

// Обход в ширину (BFS)
void BFS(int** G, int size, int* vis, int startVertex) {
    queue<int> q;
    q.push(startVertex);
    vis[startVertex] = 1;  // стартовая вершина отмечена как пройдённая

    printf("Обход в ширину (BFS), начиная с вершины %d:\n", startVertex);

    while (!q.empty()) {
        int currentVertex = q.front();
        printf("%d ", currentVertex);
        q.pop();

        // Обход соседей текущей вершины
        for (int i = 0; i < size; i++) {
            if (G[currentVertex][i] == 1 && vis[i] == 0) {
                q.push(i);  // Добавляем в очередь
                vis[i] = 1; // Отмечаем как посещённую
            }
        }
    }
    printf("\n");
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(0));

    int size;
    printf("Введите количество вершин графа: ");
    scanf("%d", &size);

    
    int** adjacencyMatrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        adjacencyMatrix[i] = (int*)malloc(size * sizeof(int));
    }

 
    generateAdjacencyMatrix(adjacencyMatrix, size);
    printAdjacencyMatrix(adjacencyMatrix, size);

   
    int* visited = (int*)calloc(size, sizeof(int));  // массив не пройденных вершин
    int startVertex = 0;  // первая вершина обхода 
    BFS(adjacencyMatrix, size, visited, startVertex);

    
    for (int i = 0; i < size; i++) {
        free(adjacencyMatrix[i]);
    }
    free(adjacencyMatrix);
    free(visited);

    return 0;
}
