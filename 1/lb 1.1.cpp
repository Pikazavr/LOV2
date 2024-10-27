﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
    int stroki, stolb;

    printf("Enter number of rows: ");
    scanf("%d", &stroki);
    printf("Enter number of columns: ");
    scanf("%d", &stolb);

    //выделение памяти 
    // malloc размер; sizeof возврат памяти
    int** arr = (int**)malloc(stroki * sizeof(int*));
    for (int i = 0; i < stroki; i++) {
        arr[i] = (int*)malloc(stolb * sizeof(int));
    }

    //ввод с клавы
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < stroki; i++) {
        for (int j = 0; j < stolb; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    //вывод массива
    printf("The array is:\n");
    for (int i = 0; i < stroki; i++) {
        for (int j = 0; j < stolb; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    //подсчет суммы строк
    for (int i = 0; i < stroki; i++) {
        int sumStrok = 0;
        for (int j = 0; j < stolb; j++) {
            sumStrok += arr[i][j];
        }
        printf("Sum of row %d: %d\n", i + 1, sumStrok);
    }

    //подсчет суммы столбцов
    for (int j = 0; j < stolb; j++) {
        int sumStolb = 0;
        for (int i = 0; i < stroki; i++) {
            sumStolb += arr[i][j];
        }
        printf("Sum of column %d: %d\n", j + 1, sumStolb);
    }

    //чистка памяти
    for (int i = 0; i < stroki; i++) {
        free(arr[i]);
    }
    free(arr);

    getchar();
    getchar();
    return 0;
}