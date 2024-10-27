#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 100

// Структура для хранения информации о студенте
typedef struct {
    char фамилия[MAX_STRING_LENGTH];
    char имя[MAX_STRING_LENGTH];
    char факультет[MAX_STRING_LENGTH];
    char зачетка[MAX_STRING_LENGTH];
} Student;

// Функция для создания динамического массива студентов
Student* createStudentArray(int size) {
    Student* students = (Student*)malloc(size * sizeof(Student));
    if (students == NULL) {
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }
    return students;
}

// Функция для расширения динамического массива
Student* resizeStudentArray(Student* students, int oldSize, int newSize) {
    students = (Student*)realloc(students, newSize * sizeof(Student));
    if (students == NULL) {
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }
    return students;
}

int main() {
    // Инициализация динамического массива
    Student* students = createStudentArray(10);
    int studentCount = 0;

    // Ввод фамилий
    printf("Введите фамилии студентов (введите \"*\" для завершения):\n");
    char input[MAX_STRING_LENGTH];
    while (1) {
        printf("Фамилия: ");
        scanf("%s", input);
        if (strcmp(input, "*") == 0) {
            break;
        }
        strcpy(students[studentCount].фамилия, input);
        studentCount++;

        // Расширение массива, если нужно
        if (studentCount == studentCount) {
            students = resizeStudentArray(students, studentCount, studentCount * 2);
        }
    }

    // Ввод имен
    printf("\nВведите имена студентов:\n");
    for (int i = 0; i < studentCount; i++) {
        printf("Имя для %s: ", students[i].фамилия);
        scanf("%s", students[i].имя);
    }

    // Ввод факультетов
    printf("\nВведите факультеты студентов:\n");
    for (int i = 0; i < studentCount; i++) {
        printf("Факультет для %s %s: ", students[i].фамилия, students[i].имя);
        scanf("%s", students[i].факультет);
    }

    // Ввод номеров зачетных книжек
    printf("\nВведите номера зачетных книжек студентов:\n");
    for (int i = 0; i < studentCount; i++) {
        printf("Номер зачетной книжки для %s %s: ", students[i].фамилия, students[i].имя);
        scanf("%s", students[i].зачетка);
    }

    // Поиск по выбору
    int choice;
    printf("\nВыберите критерий поиска:\n");
    printf("1 - Фамилия\n");
    printf("2 - Имя\n");
    printf("3 - Факультет\n");
    printf("Введите номер: ");
    scanf("%d", &choice);

    printf("Введите поисковый запрос: ");
    scanf("%s", input);

    printf("\nНайденные студенты:\n");
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        switch (choice) {
        case 1:
            if (strstr(students[i].фамилия, input) != NULL) {
                printf("Фамилия: %s\n", students[i].фамилия);
                printf("Имя: %s\n", students[i].имя);
                printf("Факультет: %s\n", students[i].факультет);
                printf("Номер зачетной книжки: %s\n\n", students[i].зачетка);
                found = 1;
            }
            break;
        case 2:
            if (strstr(students[i].имя, input) != NULL) {
                printf("Фамилия: %s\n", students[i].фамилия);
                printf("Имя: %s\n", students[i].имя);
                printf("Факультет: %s\n", students[i].факультет);
                printf("Номер зачетной книжки: %s\n\n", students[i].зачетка);
                found = 1;
            }
            break;
        case 3:
            if (strstr(students[i].факультет, input) != NULL) {
                printf("Фамилия: %s\n", students[i].фамилия);
                printf("Имя: %s\n", students[i].имя);
                printf("Факультет: %s\n", students[i].факультет);
                printf("Номер зачетной книжки: %s\n\n", students[i].зачетка);
                found = 1;
            }
            break;
        default:
            printf("Некорректный выбор.\n");
        }
    }

    if (!found) {
        printf("Совпадений не найдено.\n");
    }

    // Освобождение памяти
    free(students);

    return 0;
}