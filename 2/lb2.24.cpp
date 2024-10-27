#include <stdio.h>
#include <stdlib.h>
#include <time.h>  

// Реализация сортировки Шелла
void shell(int* items, int count)
{
    int i, j, gap, k;
    int x;
    int a[5] = { 9, 5, 3, 2, 1 };  // Шаги для сортировки Шелла

    // Основной цикл по шагам
    for (k = 0; k < 5; k++) {
        gap = a[k];        
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

// Функция для генерации случайного массива
void generate_random_array(int* items, int count, int max_value)
{
    for (int i = 0; i < count; i++) {
        items[i] = rand() % max_value;  // Случайные числа от 0 до max_value-1
    }
}

int main() {
    srand(time(NULL));  // Инициализация генератора случайных чисел

    // Количество элементов массива
    int count = 10;
    int max_value = 100;  // Максимальное значение элементов

    // Динамическое выделение памяти для массива данных
    int* items = (int*)malloc(count * sizeof(int));
    if (items == NULL) {
        printf("Memory error\n");
        return 1;  // Завершение программы, если не удалось выделить память
    }

    // Генерация случайного массива
    generate_random_array(items, count, max_value);

    // Вывод исходного массива
    printf("random mass:\n");
    for (int i = 0; i < count; i++) {
        printf("%d ", items[i]);
    }
    printf("\n");

    // Оценка времени для сортировки Шелла
    clock_t start_time = clock();  // Начало отсчета времени
    shell(items, count);
    clock_t end_time = clock();    // Конец отсчета времени
    float shell_time = (float)(end_time - start_time) / CLOCKS_PER_SEC;

    // Вывод результата сортировки Шелла
    printf("\nmass after shella:\n");
    for (int i = 0; i < count; i++) {
        printf("%d ", items[i]);
    }
    printf("\navg time shella : %.6f sec\n", shell_time);

    // Снова генерируем случайный массив для быстрой сортировки
    generate_random_array(items, count, max_value);

    // Оценка времени для быстрой сортировки
    start_time = clock();  // Начало отсчета времени
    qs(items, 0, count - 1);
    end_time = clock();    // Конец отсчета времени
    float quicksort_time = (float)(end_time - start_time) / CLOCKS_PER_SEC;

    // Вывод результата быстрой сортировки
    printf("\nmass after qs:\n");
    for (int i = 0; i < count; i++) {
        printf("%d ", items[i]);
    }
    printf("\navg time qs: %.6f sec\n", quicksort_time);

    // Освобождение выделенной памяти
    free(items);

    return 0;
}
