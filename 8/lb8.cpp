#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <queue> 
#include "locale.h"

using namespace std;

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


void printAdjacencyMatrix(int matrix[N][N]) {
    printf("Матрица смежности графа G:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void BFS(int G[N][N], int size, int* vis, int startVertex) {
    queue<int> q;  
    q.push(startVertex);
    vis[startVertex] = 1;  //стартовая вершина+пройдена

    printf("Обход в ширину (BFS), начиная с вершины %d:\n", startVertex);

    while (!q.empty()) {
        int currentVertex = q.front();
        printf("%d ", currentVertex);
        q.pop();

        // Обход соседей
        for (int i = 0; i < size; i++) {
            if (G[currentVertex][i] == 1 && vis[i] == 0) {
                q.push(i); // очередь
                vis[i] = 1;// вершина пройдена
            }
        }
    }
    printf("\n");
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(0));
    int adjacencyMatrix[N][N];

    generateAdjacencyMatrix(adjacencyMatrix);
    printAdjacencyMatrix(adjacencyMatrix);

    int startVertex = 0;

    int visited[N] = { 0 };
       
    BFS(adjacencyMatrix, N, visited, startVertex);

    return 0;
}
