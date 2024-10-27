#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "locale.h"

// Функция для печати массива
void printArray(int* items, int count) {
    for (int i = 0; i < count; i++) {
        printf("%d ", items[i]);
    }
    printf("\n");
}

// Сортировка Шелла
void shell(int* items, int count) {
    int i, j, gap, k;
    int x, a[5] = { 9, 5, 3, 2, 1 };

    printf("Начальное состояние массива (Shell sort):\n");
    printArray(items, count);

    for (k = 0; k < 5; k++) {
        gap = a[k];
        printf("\nШаг сортировки Шелла с шагом %d:\n", gap);
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (j >= 0) && (x < items[j]); j -= gap) {
                items[j + gap] = items[j];
            }
            items[j + gap] = x;

            // Печать массива после каждого изменения
            printArray(items, count);
        }
    }
}

// Быстрая сортировка
void qs(int* items, int left, int right) {
    int i = left, j = right;
    int x = items[(left + right) / 2];
    int y;

    printf("\nБыстрая сортировка, разделение с компарандом %d:\n", x);

    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;

        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;

            // Печать текущего состояния массива после обмена
            printArray(items, right + 1);
        }
    } while (i <= j);

    // Рекурсивная сортировка левой и правой частей
    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}

int main() {
    setlocale(LC_ALL, "Rus");
    int items1[] = { 34, 7, 23, 32, 5, 62 };
    int count1 = sizeof(items1) / sizeof(items1[0]);

    printf("Массив перед сортировкой (Shell):\n");
    printArray(items1, count1);

    // Измерение времени для сортировки Шелла
    clock_t start = clock();
    shell(items1, count1);
    clock_t end = clock();
    double shell_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения Shell sort: %.6f секунд\n", shell_time);

    int items2[] = { 34, 7, 23, 32, 5, 62 };
    int count2 = sizeof(items2) / sizeof(items2[0]);

    printf("\nМассив перед сортировкой (Quick Sort):\n");
    printArray(items2, count2);

    // Измерение времени для быстрой сортировки
    start = clock();
    qs(items2, 0, count2 - 1);
    end = clock();
    double quicksort_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения Quick sort: %.6f секунд\n", quicksort_time);

    printf("Массив после сортировки (Shell):\n");
    printArray(items1, count1);
    printf("\nМассив после сортировки (Quick Sort):\n");
    printArray(items2, count2);

    return 0;
}
