#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define MAX_SIZE 10

void generate_adjacency_matrix(int n, int matrix[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int edge = rand() % 2;
            matrix[i][j] = edge;
            matrix[j][i] = edge;
        }
    }
}

void print_matrix(int n, int matrix[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void merge_vertices(int n, int matrix[MAX_SIZE][MAX_SIZE], int v1, int v2) {
    for (int i = 0; i < n; i++) {
        if (i != v1 && i != v2) {
            matrix[v1][i] += matrix[v2][i];
            matrix[i][v1] = matrix[v1][i];
        }
    }
    for (int i = v2; i < n - 1; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = matrix[i + 1][j];
            matrix[j][i] = matrix[j][i + 1];
        }
    }
}

void contract_edge(int* n, int matrix[MAX_SIZE][MAX_SIZE], int v1, int v2) {
    merge_vertices(*n, matrix, v1, v2);
    (*n)--;
}

void split_vertex(int* n, int matrix[MAX_SIZE][MAX_SIZE], int v) {
    for (int i = 0; i < *n; i++) {
        matrix[*n][i] = matrix[v][i];
        matrix[i][*n] = matrix[i][v];
    }
    matrix[*n][v] = 0;
    matrix[v][*n] = 0;
    (*n)++;
}

void union_graphs(int n1, int n2, int matrix1[MAX_SIZE][MAX_SIZE], int matrix2[MAX_SIZE][MAX_SIZE], int result[MAX_SIZE][MAX_SIZE]) {
    int size = n1 > n2 ? n1 : n2;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int val1 = (i < n1 && j < n1) ? matrix1[i][j] : 0;
            int val2 = (i < n2 && j < n2) ? matrix2[i][j] : 0;
            result[i][j] = val1 || val2;
        }
    }
}

void intersection_graphs(int n1, int n2, int matrix1[MAX_SIZE][MAX_SIZE], int matrix2[MAX_SIZE][MAX_SIZE], int result[MAX_SIZE][MAX_SIZE]) {
    int size = n1 > n2 ? n1 : n2;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int val1 = (i < n1 && j < n1) ? matrix1[i][j] : 0;
            int val2 = (i < n2 && j < n2) ? matrix2[i][j] : 0;
            result[i][j] = val1 && val2;
        }
    }
}

void symmetric_difference_graphs(int n1, int n2, int matrix1[MAX_SIZE][MAX_SIZE], int matrix2[MAX_SIZE][MAX_SIZE], int result[MAX_SIZE][MAX_SIZE]) {
    int size = n1 > n2 ? n1 : n2;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int val1 = (i < n1 && j < n1) ? matrix1[i][j] : 0;
            int val2 = (i < n2 && j < n2) ? matrix2[i][j] : 0;
            result[i][j] = val1 ^ val2;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));

    int n1, n2;
    printf("Введите размер первой матрицы: ");
    scanf("%d", &n1);
    printf("Введите размер второй матрицы: ");
    scanf("%d", &n2);

    if (n1 > MAX_SIZE || n2 > MAX_SIZE) {
        printf("Размер матрицы не должен превышать %d\n", MAX_SIZE);
        return 1;
    }

    int matrix1[MAX_SIZE][MAX_SIZE] = { 0 };
    int matrix2[MAX_SIZE][MAX_SIZE] = { 0 };
    int result[MAX_SIZE][MAX_SIZE] = { 0 };

    generate_adjacency_matrix(n1, matrix1);
    generate_adjacency_matrix(n2, matrix2);

    printf("Матрица M1:\n");
    print_matrix(n1, matrix1);

    printf("\nМатрица M2:\n");
    print_matrix(n2, matrix2);

    int choice, v1, v2;

    printf("\nВыберите операцию:\n1. Отождествление вершин\n2. Стягивание ребра\n3. Расщепление вершины\nВаш выбор: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        printf("Введите номера вершин для отождествления: ");
        scanf("%d %d", &v1, &v2);
        merge_vertices(n1, matrix1, v1, v2);
        n1--;
        printf("\nМатрица после отождествления вершин:\n");
        print_matrix(n1, matrix1);
        break;

    case 2:
        printf("Введите номера вершин для стягивания ребра: ");
        scanf("%d %d", &v1, &v2);
        contract_edge(&n1, matrix1, v1, v2);
        printf("\nМатрица после стягивания ребра:\n");
        print_matrix(n1, matrix1);
        break;

    case 3:
        printf("Введите номер вершины для расщепления: ");
        scanf("%d", &v1);
        split_vertex(&n1, matrix1, v1);
        printf("\nМатрица после расщепления вершины:\n");
        print_matrix(n1, matrix1);
        break;

    default:
        printf("Неверный выбор операции.\n");
    }

    getchar();
    getchar();
    return 0;
}
