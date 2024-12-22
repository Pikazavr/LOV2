#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "locale.h"

void swap(char* a, char* b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void generatePermutations(char* array, int start, int end, FILE* file) {
    if (start == end) {
        printf("%s\n", array); // Вывод на экран
        fprintf(file, "%s\n", array); // Сохранение в файл
        return;
    }

    for (int i = start; i <= end; i++) {
        swap(&array[start], &array[i]);
        generatePermutations(array, start + 1, end, file);
        swap(&array[start], &array[i]);
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(0)); // Инициализация генератора случайных чисел

    printf("Выберите режим задания множества:\n");
    printf("1. Ручной ввод\n");
    printf("2. Автоматическая генерация\n");

    int mode;
    scanf("%d", &mode);

    if (mode < 1 || mode > 2) {
        printf("Неверный выбор. Завершение программы.\n");
        return 1;
    }

    char array[100];
    int length;

    if (mode == 1) {
        printf("Введите элементы множества (без пробелов): ");
        scanf("%s", array);
        length = strlen(array);
    }
    else {
        printf("Введите количество элементов множества: ");
        scanf("%d", &length);

        if (length <= 0 || length > 100) {
            printf("Некорректное количество элементов. Завершение программы.\n");
            return 1;
        }

        printf("Выберите тип элементов:\n");
        printf("1. Только буквы\n");
        printf("2. Только цифры\n");
        printf("3. Буквы и цифры\n");

        int type;
        scanf("%d", &type);

        if (type < 1 || type > 3) {
            printf("Неверный выбор. Завершение программы.\n");
            return 1;
        }

        for (int i = 0; i < length; i++) {
            if (type == 1) {
                array[i] = 'A' + rand() % 26;
            }
            else if (type == 2) {
                array[i] = '0' + rand() % 10;
            }
            else {
                if (rand() % 2 == 0) {
                    array[i] = 'A' + rand() % 26;
                }
                else {
                    array[i] = '0' + rand() % 10;
                }
            }
        }
        array[length] = '\0';

        printf("Сгенерированное множество: %s\n", array);
    }

    FILE* file = fopen("results.txt", "w");
    if (!file) {
        printf("Ошибка при открытии файла для записи.\n");
        return 1;
    }

    clock_t start_time = clock(); // Запуск таймера

    generatePermutations(array, 0, length - 1, file);

    clock_t end_time = clock(); // Остановка таймера
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    fclose(file);

    printf("Все перестановки сохранены в файл results.txt\n");
    printf("Время выполнения операции: %.6f секунд\n", time_taken);

    return 0;
}
