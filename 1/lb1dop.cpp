#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int ntzero(int **arr, int stroki, int stolb, int** eqzero)
{
    int count = 0;
    int half = stolb / 2; //определение левой части 
    for (int i = 0; i < stroki; i++)
    {
        for (int j = 0; j < half; j++)
        {
            if (arr[i][j] != 0)
            {
                *eqzero = (int*)realloc(*eqzero, (count + 1) * sizeof(int));
                (*eqzero)[count] = arr[i][j];
                count++;
            }
        }
    }
    return count;
}

int main() {
    int stroki, stolb;

    printf("Enter stroki: \n ");
    scanf("%d", &stroki);
    printf("Enter stolb: \n ");
    scanf("%d", &stolb);

    //выделение памяти 
    // malloc размер; sizeof возврат памяти
    int** arr = (int**)malloc(stroki * sizeof(int*));
    for (int i = 0; i < stroki; i++) {
        arr[i] = (int*)malloc(stolb * sizeof(int));
    }

    //ввод с клавы
    printf("Enter massiv:\n");
    for (int i = 0; i < stroki; i++) {
        for (int j = 0; j < stolb; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    //вывод массива
    printf("Mass is :\n");
    for (int i = 0; i < stroki; i++) {
        for (int j = 0; j < stolb; j++) {
            printf("|%d| ", arr[i][j]);
        }
        printf("\n");
    }

    //подсчет суммы строк
    for (int i = 0; i < stroki; i++) {
        int sumStrok = 0;
        for (int j = 0; j < stolb; j++) {
            sumStrok += arr[i][j];
        }
        printf("Summa strok %d: %d\n", i + 1, sumStrok);
    }

    //подсчет суммы столбцов
    for (int j = 0; j < stolb; j++) {
        int sumStolb = 0;
        for (int i = 0; i < stroki; i++) {
            sumStolb += arr[i][j];
        }
        printf("Summa stolbov %d: %d\n", j + 1, sumStolb);
    }
    //массив для хранения ненулевых элементов
    int* ntzeroarr = NULL;

    //подсчет ненулевых элементов в левой половине массива
    int nonzeroct = ntzero(arr, stroki, stolb, &ntzeroarr);
    printf("kolvo elements != 0 in left: %d\n", nonzeroct);
        
    // Чистка памяти
    for (int i = 0; i < stroki; i++) {
        free(arr[i]);
    }
    free(arr);
    //очистка дин масива
    free(ntzeroarr);

    getchar();
    getchar();
    return 0;
}
