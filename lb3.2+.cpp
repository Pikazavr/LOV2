#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Структура узла стека
struct Node {
    char data[256];
    struct Node* next;
};

// Структура стека
struct Stack {
    struct Node* top;
};

// Функция для создания нового стека
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}

// Проверка, пуст ли стек
int isEmpty(struct Stack* stack) {
    return stack->top == NULL;
}

// Операция добавления элемента в стек (push)
void push(struct Stack* stack, const char* data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->data, data);
    newNode->next = stack->top;
    stack->top = newNode;
}

// Операция извлечения элемента из стека (pop)
char* pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Стек пуст!\n");
        return NULL;
    }

    struct Node* temp = stack->top;
    char* data = (char*)malloc(strlen(temp->data) + 1);
    strcpy(data, temp->data);

    stack->top = stack->top->next;
    free(temp);

    return data;
}

// Операция просмотра вершины стека (peek)
char* peek(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Стек пуст!\n");
        return NULL;
    }

    return stack->top->data;
}

// Функция для печати содержимого стека
void printStack(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Стек пуст!\n");
        return;
    }

    struct Node* current = stack->top;
    printf("Содержимое стека: ");
    while (current != NULL) {
        printf("\"%s\" ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Освобождение памяти для стека
void freeStack(struct Stack* stack) {
    while (!isEmpty(stack)) {
        char* data = pop(stack);
        free(data);
    }
    free(stack);
}

// Функция для отображения меню
void displayMenu() {
    printf("\nМеню:\n");
    printf("1. Добавить элемент в стек\n");
    printf("2. Просмотреть вершину стека\n");
    printf("3. Удалить элемент из стека\n");
    printf("4. Показать весь стек\n");
    printf("5. Выйти\n");
    printf("Выберите опцию: ");
}

int main() {
    setlocale(LC_ALL, "Rus");
    struct Stack* stack = createStack();
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
            push(stack, data);
            printf("Элемент добавлен в стек.\n");
            break;
        case 2:
            if (!isEmpty(stack)) {
                printf("Вершина стека: \"%s\"\n", peek(stack));
            }
            break;
        case 3:
            if (!isEmpty(stack)) {
                printf("Извлечен элемент: \"%s\"\n", pop(stack));
            }
            break;
        case 4:
            printStack(stack);
            break;
        case 5:
            printf("Выход из программы.\n");
            break;
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 5);

    // Освобождаем память
    freeStack(stack);

    return 0;
}
