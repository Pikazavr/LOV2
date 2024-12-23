#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "locale.h"


#define MAX_VERTICES 100

// Генерация случайной матрицы смежности для графа
void define_random_adjacency_matrix(int matrix[MAX_VERTICES][MAX_VERTICES], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (i == j) {
                matrix[i][j] = 0; // Отсутствие петель
            }
            else {
                int random_value = rand() % 2;
                matrix[i][j] = random_value;
                matrix[j][i] = random_value; // Неориентированный граф
            }
        }
    }
}

// Вывод матрицы на экран
void print_matrix(int matrix[MAX_VERTICES][MAX_VERTICES], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Отождествление двух вершин
void identify_vertices(int matrix[MAX_VERTICES][MAX_VERTICES], int size, int v1, int v2) {
    for (int i = 0; i < size; i++) {
        if (i != v1 && i != v2) {
            matrix[v1][i] |= matrix[v2][i];
            matrix[i][v1] = matrix[v1][i];
        }
    }

    for (int i = 0; i < size; i++) {
        matrix[v2][i] = 0;
        matrix[i][v2] = 0;
    }
}

// Стягивание ребра
void contract_edge(int matrix[MAX_VERTICES][MAX_VERTICES], int size, int v1, int v2) {
    identify_vertices(matrix, size, v1, v2);
}

// Расщепление вершины
void split_vertex(int matrix[MAX_VERTICES][MAX_VERTICES], int* size, int v) {
    if (*size >= MAX_VERTICES) {
        printf("\nОшибка: превышен лимит вершин.\n");
        return;
    }

    int new_vertex = (*size)++;

    for (int i = 0; i < *size; i++) {
        matrix[new_vertex][i] = 0;
        matrix[i][new_vertex] = 0;
    }

    for (int i = 0; i < *size; i++) {
        if (matrix[v][i] == 1 && rand() % 2 == 0) {
            matrix[v][i] = 0;
            matrix[i][v] = 0;

            matrix[new_vertex][i] = 1;
            matrix[i][new_vertex] = 1;
        }
    }
}

// Операция объединения графов
void union_graphs(int matrix1[MAX_VERTICES][MAX_VERTICES], int matrix2[MAX_VERTICES][MAX_VERTICES], int size1, int size2, int result[MAX_VERTICES][MAX_VERTICES]) {
    int new_size = size1 + size2;

    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            if (i < size1 && j < size1) {
                result[i][j] = matrix1[i][j];
            }
            else if (i >= size1 && j >= size1) {
                result[i][j] = matrix2[i - size1][j - size1];
            }
            else {
                result[i][j] = 0;
            }
        }
    }
}

// Операция пересечения графов
void intersect_graphs(int matrix1[MAX_VERTICES][MAX_VERTICES], int matrix2[MAX_VERTICES][MAX_VERTICES], int size, int result[MAX_VERTICES][MAX_VERTICES]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = matrix1[i][j] & matrix2[i][j];
        }
    }
}

// Операция кольцевой суммы графов
void symmetric_difference_graphs(int matrix1[MAX_VERTICES][MAX_VERTICES], int matrix2[MAX_VERTICES][MAX_VERTICES], int size, int result[MAX_VERTICES][MAX_VERTICES]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = matrix1[i][j] ^ matrix2[i][j];
        }
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(0));

    int size1, size2;
    int graph1[MAX_VERTICES][MAX_VERTICES];
    int graph2[MAX_VERTICES][MAX_VERTICES];

    printf("Введите количество вершин графа G1: ");
    scanf("%d", &size1);
    define_random_adjacency_matrix(graph1, size1);

    printf("Введите количество вершин графа G2: ");
    scanf("%d", &size2);
    define_random_adjacency_matrix(graph2, size2);

    printf("\nМатрица смежности G1:\n");
    print_matrix(graph1, size1);

    printf("\nМатрица смежности G2:\n");
    print_matrix(graph2, size2);

    int v1, v2;

    // Операции с вершинами
    printf("\nВыберите вершины для отождествления в G1 (v1 v2): ");
    scanf("%d %d", &v1, &v2);
    identify_vertices(graph1, size1, v1, v2);
    printf("\nМатрица после отождествления:\n");
    print_matrix(graph1, size1);

    printf("\nВыберите вершины для стягивания ребра в G1 (v1 v2): ");
    scanf("%d %d", &v1, &v2);
    contract_edge(graph1, size1, v1, v2);
    printf("\nМатрица после стягивания:\n");
    print_matrix(graph1, size1);

    printf("\nВыберите вершину для расщепления в G1 (v): ");
    scanf("%d", &v1);
    split_vertex(graph1, &size1, v1);
    printf("\nМатрица после расщепления:\n");
    print_matrix(graph1, size1);

    // Операции с графами
    int union_result[MAX_VERTICES][MAX_VERTICES];
    int intersection_result[MAX_VERTICES][MAX_VERTICES];
    int sym_diff_result[MAX_VERTICES][MAX_VERTICES];

    union_graphs(graph1, graph2, size1, size2, union_result);
    printf("\nМатрица объединения G = G1 ∪ G2:\n");
    print_matrix(union_result, size1 + size2);

    intersect_graphs(graph1, graph2, size1, intersection_result);
    printf("\nМатрица пересечения G = G1 ∩ G2:\n");
    print_matrix(intersection_result, size1);

    symmetric_difference_graphs(graph1, graph2, size1, sym_diff_result);
    printf("\nМатрица кольцевой суммы G = G1 ∆ G2:\n");
    print_matrix(sym_diff_result, size1);

    return 0;
}
