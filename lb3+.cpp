#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "locale.h"

// Определение структуры узла
struct Node {
    char data[256];
    int priority;
    struct Node* next;
};

// Определение структуры приоритетной очереди
struct PriorityQueue {
    struct Node* front;
};

// Функция для создания новой очереди
struct PriorityQueue* createQueue() {
    struct PriorityQueue* queue = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
    queue->front = NULL;
    return queue;
}

// Проверка, пуста ли очередь
int isEmpty(const struct PriorityQueue* queue) {
    return queue->front == NULL;
}

// Функция для добавления элемента в приоритетную очередь
void enqueue(struct PriorityQueue* queue, const char* data, int priority) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->data, data);
    newNode->priority = priority;
    newNode->next = NULL;

    // Вставка в начало очереди, если очередь пуста или приоритет выше
    if (isEmpty(queue) || priority > queue->front->priority) {
        newNode->next = queue->front;
        queue->front = newNode;
        return;
    }

    // Вставка в подходящее место в очереди
    struct Node* current = queue->front;
    while (current->next != NULL && priority <= current->next->priority) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}

// Функция для удаления элемента с наивысшим приоритетом
char* dequeue(struct PriorityQueue* queue) {
    if (isEmpty(queue)) {
        printf("Очередь пуста!\n");
        return NULL;
    }

    struct Node* temp = queue->front;
    char* data = (char*)malloc(sizeof(temp->data));
    strcpy(data, temp->data);

    queue->front = queue->front->next;
    free(temp);
    return data;
}

// Функция для отображения всей очереди
void printQueue(const struct PriorityQueue* queue) {
    if (isEmpty(queue)) {
        printf("Очередь пуста!\n");
        return;
    }

    struct Node* current = queue->front;
    while (current != NULL) {
        printf("Имя: %s, Приоритет: %d\n", current->data, current->priority);
        current = current->next;
    }
}

// Функция для отображения элемента с наивысшим приоритетом
void peek(const struct PriorityQueue* queue) {
    if (isEmpty(queue)) {
        printf("Очередь пуста!\n");
        return;
    }

    printf("Элемент с наивысшим приоритетом: Имя: %s, Приоритет: %d\n", queue->front->data, queue->front->priority);
}

// Функция для выбора действия
void choice(struct PriorityQueue* queue) {
    int option;
    char data[256];
    int priority;

    while (1) {
        printf("\nВыберите действие:\n");
        printf("1. Добавить элемент\n");
        printf("2. Просмотреть элемент с наивысшим приоритетом\n");
        printf("3. Удалить элемент с наивысшим приоритетом\n");
        printf("4. Показать всю очередь\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");
        scanf("%d", &option);

        switch (option) {
        case 1:
            printf("Введите данные элемента: ");
            scanf(" %[^\n]s", data);
            printf("Введите приоритет элемента (целое число): ");
            scanf("%d", &priority);
            enqueue(queue, data, priority);
            printf("Элемент добавлен.\n");
            break;
        case 2:
            peek(queue);
            break;
        case 3:
        {
            char* removedData = dequeue(queue);
            if (removedData != NULL) {
                printf("Удален элемент: %s\n", removedData);
                free(removedData);
            }
        }
        break;
        case 4:
            printf("Текущая очередь:\n");
            printQueue(queue);
            break;
        case 0:
            printf("Выход из программы.\n");
            return;
        default:
            printf("Неверный выбор. Попробуйте еще раз.\n");
            break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    struct PriorityQueue* queue = createQueue();
    choice(queue);

    // Освобождаем память
    while (!isEmpty(queue)) {
        free(dequeue(queue));
    }
    free(queue);

    return 0;
}
