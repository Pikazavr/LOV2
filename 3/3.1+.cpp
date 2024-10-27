#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Структура узла обычной очереди
struct Node {
    char data[256];
    struct Node* next;
};

// Структура обычной очереди
struct Queue {
    struct Node* front;
    struct Node* rear;
};

// Создание новой обычной очереди
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Проверка, пуста ли обычная очередь
int isEmptyQueue(struct Queue* queue) {
    return queue->front == NULL;
}

// Добавление элемента в обычную очередь
void enqueueQueue(struct Queue* queue, const char* data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->data, data);
    newNode->next = NULL;

    if (isEmptyQueue(queue)) {
        queue->front = queue->rear = newNode;
    }
    else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// Извлечение элемента из обычной очереди
char* dequeueQueue(struct Queue* queue) {
    if (isEmptyQueue(queue)) {
        printf("Очередь пуста!\n");
        return NULL;
    }

    struct Node* temp = queue->front;
    char* data = (char*)malloc(strlen(temp->data) + 1);
    strcpy(data, temp->data);

    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    return data;
}

// Вывод содержимого обычной очереди
void printQueue(struct Queue* queue) {
    if (isEmptyQueue(queue)) {
        printf("Очередь пуста!\n");
        return;
    }

    struct Node* current = queue->front;
    printf("Содержимое очереди: ");
    while (current != NULL) {
        printf("\"%s\" ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Освобождение памяти для обычной очереди
void freeQueue(struct Queue* queue) {
    while (!isEmptyQueue(queue)) {
        char* data = dequeueQueue(queue);
        free(data);
    }
    free(queue);
}

// Функция для отображения меню
void displayMenu() {
    printf("\nМеню:\n");
    printf("1. Добавить элемент в очередь\n");
    printf("2. Удалить элемент из очереди\n");
    printf("3. Показать всю очередь\n");
    printf("4. Выйти\n");
    printf("Выберите опцию: ");
}

int main() {
    setlocale(LC_ALL, "Rus");
    struct Queue* queue = createQueue();
    int choice;
    char data[256];

    do {
        displayMenu();
        scanf("%d", &choice);
        getchar(); // Очистка буфера после ввода

        switch (choice) {
        case 1:
            printf("Введите данные для добавления: ");
            fgets(data, sizeof(data), stdin);
            data[strcspn(data, "\n")] = '\0'; // Удаление символа новой строки
            enqueueQueue(queue, data);
            printf("Элемент добавлен в очередь.\n");
            break;
        case 2:
            if (!isEmptyQueue(queue)) {
                char* removedData = dequeueQueue(queue);
                printf("Удален элемент: \"%s\"\n", removedData);
                free(removedData);
            }
            break;
        case 3:
            printQueue(queue);
            break;
        case 4:
            printf("Выход из программы.\n");
            break;
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 4);

    // Освобождаем память
    freeQueue(queue);

    return 0;
}
