#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "locale.h"
#define N 5  // Количество вершин графа

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

// Определение типа вершин
void findVertexTypes(int matrix[N][N]) {
    int isolatedCount = 0, pendantCount = 0, dominatingCount = 0;

    for (int i = 0; i < N; i++) {
        int degree = 0;
        for (int j = 0; j < N; j++) {
            degree += matrix[i][j];
        }

        if (degree == 0) { //cтрока пуста -  изолирована 
            printf("Вершина %d является изолированной.\n", i);
            isolatedCount++;
        }
        else if (degree == 1) { // в строке есть еденица 
            printf("Вершина %d является концевой.\n", i);
            pendantCount++;
        }
        //else if (degree == N - 1) {
        else if (degree > 1) {
            printf("Вершина %d является доминирующей.\n", i);
            dominatingCount++;
        }
    }

    printf("\nВсего изолированных вершин: %d\n", isolatedCount);
    printf("Всего концевых вершин: %d\n", pendantCount);
    printf("Всего доминирующих вершин: %d\n", dominatingCount);
}

int main() {
    srand(time(0));
    setlocale(LC_ALL, "Rus");
    int adjacencyMatrix[N][N];
    generateAdjacencyMatrix(adjacencyMatrix);
    printAdjacencyMatrix(adjacencyMatrix);

    printf("\nАнализ типов вершин:\n");
    findVertexTypes(adjacencyMatrix);

    return 0;
}
