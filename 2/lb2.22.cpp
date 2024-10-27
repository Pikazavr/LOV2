#include <stdio.h>
#include <stdlib.h>
#include <time.h>  // Для оценки времени

// Реализация сортировки Шелла
void shell(int* items, int count)
{
    int i, j, gap, k;
    int x;
    int a[5] = { 9, 5, 3, 2, 1 };  // Шаги для сортировки Шелла

    // Основной цикл по шагам
    for (k = 0; k < 5; k++) {
        gap = a[k];
        // Выполняем сортировку для текущего шага (gap)
        for (i = gap; i < count; ++i) {
            x = items[i];
            // Сдвигаем элементы в отсортированную часть
            for (j = i - gap; (j >= 0) && (x < items[j]); j = j - gap) {
                items[j + gap] = items[j];
            }
            items[j + gap] = x;
        }
    }
}

// Реализация быстрой сортировки
void qs(int* items, int left, int right)
{
    int i, j;
    int x, y;

    i = left;
    j = right;

    // Выбор центрального элемента
    x = items[(left + right) / 2];

    // Основной цикл сортировки
    do {
        // Ищем элементы, которые нужно поменять местами
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;

        // Если найдено, меняем местами
        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++;
            j--;
        }
    } while (i <= j);

    // Рекурсивная сортировка для левой и правой части
    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}

int main() {
    // Массив данных для сортировки
    int items[] = { 9, 5, 2, 7, 3, 8, 1, 6, 4, 0 };
    int count = sizeof(items) / sizeof(items[0]);

    // Вывод исходного массива
    printf("Base mass:\n");
    for (int i = 0; i < count; i++) {
        printf("%d ", items[i]);
    }
    printf("\n");

    // Оценка времени для сортировки Шелла
    clock_t start_time = clock();  // Начало отсчета времени
    shell(items, count);
    clock_t end_time = clock();    // Конец отсчета времени
    double shell_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Вывод результата сортировки Шелла
    printf("\nMass shella:\n");
    for (int i = 0; i < count; i++) {
        printf("%d ", items[i]);
    }
    printf("\nTime shella: %f sec\n", shell_time);

    // Массив данных для быстрой сортировки
    int items2[] = { 9, 5, 2, 7, 3, 8, 1, 6, 4, 0 };
    count = sizeof(items2) / sizeof(items2[0]);

    // Оценка времени для быстрой сортировки
    start_time = clock();  // Начало отсчета времени
    qs(items2, 0, count - 1);
    end_time = clock();    // Конец отсчета времени
    double quicksort_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Вывод результата быстрой сортировки
    printf("\nQuick sort:\n");
    for (int i = 0; i < count; i++) {
        printf("%d ", items2[i]);
    }
    printf("\nTime quick sort: %f sec\n", quicksort_time);

    return 0;
}
