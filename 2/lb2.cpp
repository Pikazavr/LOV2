#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

	clock_t start, end; // переменные для времени выполнения

	int i, j, r;
	int N = 1000; // размер массива, увеличен для примера
	int** a, ** b, ** c, elem_c;

	// Выделение памяти для массивов
	a = (int**)malloc(N * sizeof(int*));
	b = (int**)malloc(N * sizeof(int*));
	c = (int**)malloc(N * sizeof(int*));
	for (i = 0; i < N; i++) {
		a[i] = (int*)malloc(N * sizeof(int));
		b[i] = (int*)malloc(N * sizeof(int));
		c[i] = (int*)malloc(N * sizeof(int));
	}

	srand(time(NULL)); // инициализация генератора случайных чисел

	// Заполняем массив a случайными числами
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			a[i][j] = rand() % 100 + 1;
		}
	}

	// Заполняем массив b случайными числами
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			b[i][j] = rand() % 100 + 1;
		}
	}

	// Начало измерения времени
	clock_t starttime = clock();

	// Умножение матриц
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			elem_c = 0;
			for (r = 0; r < N; r++) {
				elem_c += a[i][r] * b[r][j];
			}
			c[i][j] = elem_c;
		}
	}

	// Конец измерения времени
	clock_t stop = clock();
	float t = (float)(stop - starttime) / CLOCKS_PER_SEC;
	printf("Время выполнения: %f секунд\n", t);

	// Освобождение памяти
	for (i = 0; i < N; i++) {
		free(a[i]);
		free(b[i]);
		free(c[i]);
	}
	free(a);
	free(b);
	free(c);

	return 0;
}
