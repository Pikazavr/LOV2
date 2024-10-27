#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main() {
    int stroki, stolb;
    printf("enter num strok\n");
    scanf("%d", &stroki);
    printf("enter num stolb\n");
    scanf("%d", &stolb);
    //выделение памяти  
    // malloc размер; sizeof возврат памяти
    int **arr = (int**)malloc(stroki * sizeof(int*));
    for (int i = 0; i < stroki; i++)
    {
        arr[i] = (int*)malloc(stolb * sizeof(int));
    }
    //ввод с клавы
    printf("enter num mas\n");
    for (int i = 0; i < stroki; i++) 
    {
        for (int j = 0; j < stolb; j++) 
        {
            scanf("%d", &arr[i][j]);
        }
    }
    //вывод массива 
    printf("Mass is:\n");
    for (int i = 0; i < stroki; i++)
    {
        for (int j = 0; j < stolb; j++) 
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < stroki; i++) {
        free(arr[i]); 
    }
    free(arr);  
    getchar();
    return 0;

}
