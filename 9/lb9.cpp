#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <queue>
#include "locale.h"
using namespace std;

#define N 5  // Количество вершин графа

void generateAdjacencyMatrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            if (i == j) {
                matrix[i][j] = 0;//отсутсвие петель  
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

void findDistances(int matrix[N][N], int startVertex) {
    queue<int> q;  

    int distances[N];
    for (int i = 0; i < N; i++) {
        distances[i] = -1;  // инициализация вершин -1(недостичь)
    }

    // начало очереди
    q.push(startVertex);
    distances[startVertex] = 0;  // расстояние до начало 0

    printf("Поиск расстояний от вершины %d:\n", startVertex);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // проверка соседних вершин
        for (int i = 0; i < N; i++) {
            if (matrix[current][i] == 1 && distances[i] == -1) {
                distances[i] = distances[current] + 1;
                q.push(i);
            }
        }
    }
    
    for (int i = 0; i < N; i++) {
        printf("Расстояние до вершины %d: ", i);
        if (distances[i] == -1) {
            printf("недостижима\n");
        }
        else {
            printf("%d\n", distances[i]);
        }
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(0));
    int adjacencyMatrix[N][N];

    generateAdjacencyMatrix(adjacencyMatrix);
    printAdjacencyMatrix(adjacencyMatrix);

    int startVertex = 0;  // начало
    findDistances(adjacencyMatrix, startVertex);

    return 0;
}
