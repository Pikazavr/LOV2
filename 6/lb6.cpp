// lab6.cpp: Программа для работы с графами

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstdlib>
#include <locale.h>

// Функция для создания графа
int** createG(int size) {
    int** G = (int**)malloc(size * sizeof(int*)); // Выделяем память для массива указателей
    if (G == NULL) {
        printf("Ошибка выделения памяти для массива указателей.\n");
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        G[i] = (int*)malloc(size * sizeof(int)); // Выделяем память для каждой строки
        if (G[i] == NULL) {
            printf("Ошибка выделения памяти для строки %d.\n", i);
            exit(1);
        }
    }

    // Инициализация графа
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            G[i][j] = rand() % 2;
            if (i == j) G[i][j] = 0; // Диагональные элементы = 0
            G[j][i] = G[i][j]; // Симметричность
        }
    }

    return G;
}

// Функция для печати графа
void printG(int** G, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }
}

// Функция для удаления вершины из графа
int** delV(int** G, int size, int v) {
    int** Gtemp = (int**)malloc((size - 1) * sizeof(int*)); // Создание временного графа на одну вершину меньше
    if (Gtemp == NULL) {
        printf("Ошибка выделения памяти для временного графа.\n");
        exit(1);
    }

    for (int i = 0; i < size - 1; i++) {
        Gtemp[i] = (int*)malloc((size - 1) * sizeof(int)); // Выделяем память для каждой строки
        if (Gtemp[i] == NULL) {
            printf("Ошибка выделения памяти для строки %d.\n", i);
            exit(1);
        }
    }

    // Копируем данные графа в новый граф, исключая вершину v
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i < v && j < v) Gtemp[i][j] = G[i][j];
            if (i > v && j > v) Gtemp[i - 1][j - 1] = G[i][j];
            if (i > v && j < v) Gtemp[i - 1][j] = G[i][j];
            if (i < v && j > v) Gtemp[i][j - 1] = G[i][j];
        }
    }

    // Освобождение памяти для старого графа
    for (int i = 0; i < size; i++) {
        free(G[i]);
    }
    free(G);

    return Gtemp;
}

// Функция для объединения двух вершин в графе
void unionV(int** G, int size, int v1, int v2) {
    for (int i = 0; i < size; i++) {
        if (G[v2][i] == 1) {
            G[v1][i] = G[v2][i];
            G[i][v1] = G[i][v2];
        }
    }

    // Удаляем вершину v2 из графа
    G = delV(G, size, v2);
    printG(G, size);
}

// Функция для объединения двух графов
int** unionG(int** G1, int** G2, int size1, int size2) {
    int sizemax = (size1 > size2) ? size1 : size2;
    int sizemin = (size1 < size2) ? size1 : size2;
    int** Gtemp = (int**)malloc(sizemax * sizeof(int*));

    if (Gtemp == NULL) {
        printf("Ошибка выделения памяти для объединённого графа.\n");
        exit(1);
    }

    for (int i = 0; i < sizemax; i++) {
        Gtemp[i] = (int*)malloc(sizemax * sizeof(int));
        if (Gtemp[i] == NULL) {
            printf("Ошибка выделения памяти для строки %d объединённого графа.\n", i);
            exit(1);
        }
    }

    // Объединяем графы
    for (int i = 0; i < sizemin; i++) {
        for (int j = 0; j < sizemin; j++) {
            Gtemp[i][j] = G1[i][j] | G2[i][j];
        }
    }

    // Добавляем элементы из большего графа в объединённый
    for (int i = 0; i < sizemax; i++) {
        for (int j = sizemin; j < sizemax; j++) {
            Gtemp[i][j] = G1[i][j];
            Gtemp[j][i] = Gtemp[i][j];
        }
    }

    return Gtemp;
}

// Главная функция
int main() {
    setlocale(LC_ALL, "Russian");
    int nG1 = 3, nG2 = 5;
    printf("Введите размерность графа G1: ");
    scanf("%d", &nG1);
    printf("Введите размерность графа G2: ");
    scanf("%d", &nG2);

    int** G1 = createG(nG1);
    int** G2 = createG(nG2);

    printf("\nГраф G1:\n");
    printG(G1, nG1);

    printf("\nГраф G2:\n");
    printG(G2, nG2);

    G1 = delV(G1, nG1, 1); // Пример удаления вершины 1 из G1
    nG1--; // Уменьшаем размерность графа

    printf("\nГраф G1 после удаления вершины 1:\n");
    printG(G1, nG1);

    // Освобождение памяти после использования
    for (int i = 0; i < nG1; i++) {
        free(G1[i]);
    }
    free(G1);

    for (int i = 0; i < nG2; i++) {
        free(G2[i]);
    }
    free(G2);

    return 0;
}
