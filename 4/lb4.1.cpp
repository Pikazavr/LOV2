#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Функция для создания нового узла дерева
struct Node* CreateTree(struct Node* root, struct Node* r, int data) {
    if (r == NULL) {
        r = (struct Node*)malloc(sizeof(struct Node));
        if (r == NULL) {
            printf("Ошибка выделения памяти");
            exit(0);
        }
        r->left = NULL;
        r->right = NULL;
        r->data = data;

        if (root == NULL) return r;
        if (data < root->data) root->left = r;
        else root->right = r;
        return r;
    }

    if (data < r->data)
        CreateTree(r, r->left, data);
    else
        CreateTree(r, r->right, data);

    return root;
}

// Функция вывода дерева сверху вниз (корень сверху, затем ветви)
void print_tree(struct Node* r, int depth) {
    if (r != NULL) {
        // Выводим узел с отступом
        for (int i = 0; i < depth; i++) {
            printf("   "); // Отступ для уровня глубины
        }
        printf("|--%d\n", r->data);

        // Рекурсивно выводим сначала левое, затем правое поддерево с увеличением глубины
        print_tree(r->left, depth + 1);
        print_tree(r->right, depth + 1);
    }
}

// Функция для поиска элемента в дереве
struct Node* search(struct Node* root, int value) {
    if (root == NULL || root->data == value) {
        return root;
    }

    if (value < root->data) {
        return search(root->left, value);  // Ищем в левом поддереве
    }
    else {
        return search(root->right, value);  // Ищем в правом поддереве
    }
}

// Функция подсчёта числа вхождений элемента в дерево
int count_occurrences(struct Node* root, int value) {
    if (root == NULL) {
        return 0;  // Если узел пустой, возвращаем 0
    }

    // Если значение совпало с текущим узлом, увеличиваем счетчик
    if (root->data == value) {
        return 1 + count_occurrences(root->left, value) + count_occurrences(root->right, value);
    }

    // Ищем значение в левом и правом поддереве
    return count_occurrences(root->left, value) + count_occurrences(root->right, value);
}

int main() {
    setlocale(LC_ALL, "");
    struct Node* root = NULL;
    int D, start = 1, search_value;

    printf("-1 - окончание построения дерева\n");
    while (start) {
        printf("Введите число: ");
        scanf("%d", &D);
        if (D == -1) {
            printf("Построение дерева окончено\n\n");
            start = 0;
        }
        else {
            root = CreateTree(root, root, D);
        }
    }

    print_tree(root, 0);  // Вывод дерева сверху вниз

    // Поиск элемента в дереве
    printf("\nВведите число для поиска: ");
    scanf("%d", &search_value);

    struct Node* result = search(root, search_value);
    if (result != NULL) {
        printf("Число %d найдено в дереве.\n", result->data);
    }
    else {
        printf("Число %d не найдено в дереве.\n", search_value);
    }

    // Подсчёт числа вхождений элемента в дерево
    int count = count_occurrences(root, search_value);
    printf("Число %d встречается в дереве %d раз(а).\n", search_value, count);

    free(root);  // Освобождение памяти
    return 0;
}
