#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "locale.h"

#define N 5  

void generateAdjacencyMatrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
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

// матрица смежности
void printAdjacencyMatrix(int matrix[N][N]) {
    printf("Матрица смежности графа G:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Обход в ширину (BFS)
void BFS(int matrix[N][N], int startVertex) {
    bool visited[N] = { false };
    int queue[N];
    int front = 0, rear = 0;

    //добавляем стартовую вершину и отмечаем её как посещённую
    queue[rear++] = startVertex;
    visited[startVertex] = true;

    printf("Обход в ширину (BFS), начиная с вершины %d:\n", startVertex);

    while (front < rear) {
        int currentVertex = queue[front++];
        printf("Посетили вершину %d\n", currentVertex);

        // Проверяем всех соседей текущей вершины
        for (int i = 0; i < N; i++) {
            if (matrix[currentVertex][i] == 1 && !visited[i]) {
                queue[rear++] = i;  // очередь
                visited[i] = true; // пройдена
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(0));
    int adjacencyMatrix[N][N];

    // печать матрицы+ ген 
    generateAdjacencyMatrix(adjacencyMatrix);
    printAdjacencyMatrix(adjacencyMatrix);

    // Выполнение обхода в ширину
    int startVertex = 0;  // первая вершина(начало обхода)
    BFS(adjacencyMatrix, startVertex);

    return 0;
}
