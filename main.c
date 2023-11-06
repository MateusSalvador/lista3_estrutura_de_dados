#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_TITLE_LENGTH 100

// Definição da estrutura do nó para a fila (FIFO)
typedef struct QueueNode {
    char title[MAX_TITLE_LENGTH];
    char author[MAX_TITLE_LENGTH];
    struct QueueNode *next;
} QueueNode;

// Definição da estrutura do nó para a pilha (LIFO)
typedef struct StackNode {
    char title[MAX_TITLE_LENGTH];
    char author[MAX_TITLE_LENGTH];
    struct StackNode *next;
} StackNode;

// Função para ler os livros de um arquivo e criar a fila
QueueNode* createQueueFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", filename);
        exit(1);
    }

    QueueNode *front = NULL;
    QueueNode *rear = NULL;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        char *title = strtok(line, ";");
        char *author = strtok(NULL, "\n");

        QueueNode *newNode = (QueueNode*)malloc(sizeof(QueueNode));
        strcpy(newNode->title, title);
        strcpy(newNode->author, author);
        newNode->next = NULL;

        if (rear == NULL) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    fclose(file);
    return front;
}

// Função para exibir a fila de livros
void displayQueue(QueueNode *front) {
    QueueNode *current = front;
    while (current != NULL) {
        printf("Livro: %s\nAutor: %s\n\n", current->title, current->author);
        current = current->next;
    }
}

// Função para inserir um novo livro na fila
QueueNode* enqueue(QueueNode *front) {
    char title[MAX_TITLE_LENGTH];
    char author[MAX_TITLE_LENGTH];
    printf("Digite o nome do livro: ");
    scanf("%99[^\n]s", title);
    fflush(stdin);

    printf("Digite o autor do livro: ");
    scanf("%99[^\n]s", author);
    fflush(stdin);

    QueueNode *newNode = (QueueNode*)malloc(sizeof(QueueNode));
    strcpy(newNode->title, title);
    strcpy(newNode->author, author);
    newNode->next = NULL;

    if (front == NULL) {
        front = newNode;
    } else {
        QueueNode *current = front;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    return front;
}

// Função para remover um livro da fila
QueueNode* dequeue(QueueNode *front) {
    if (front == NULL) {
        printf("A fila está vazia.\n");
    } else {
        QueueNode *temp = front;
        front = front->next;
        free(temp);
        printf("Livro removido da fila com sucesso.\n");
    }
    return front;
}

// Função para ler os livros de um arquivo e criar a pilha
StackNode* createStackFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", filename);
        exit(1);
    }

    StackNode *top = NULL;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        char *title = strtok(line, ";");
        char *author = strtok(NULL, "\n");

        StackNode *newNode = (StackNode*)malloc(sizeof(StackNode));
        strcpy(newNode->title, title);
        strcpy(newNode->author, author);
        newNode->next = top;
        top = newNode;
    }

    fclose(file);
    return top;
}

// Função para escrever a pilha de livros em um arquivo
void writeStackToFile(StackNode *top, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s para escrita.\n", filename);
        return;
    }

    StackNode *current = top;
    while (current != NULL) {
        fprintf(file, "%s;%s\n", current->title, current->author);
        current = current->next;
    }

    fclose(file);
}

// Função para exibir a pilha de livros
void displayStack(StackNode *top) {
    StackNode *current = top;
    while (current != NULL) {
        printf("Livro: %s\nAutor: %s\n\n", current->title, current->author);
        current = current->next;
    }
}

// Função para inserir um novo livro na pilha
StackNode* push(StackNode *top) {
    char title[MAX_TITLE_LENGTH];
    char author[MAX_TITLE_LENGTH];
    printf("Digite o nome do livro: ");
    scanf("%99[^\n]s", title);
    fflush(stdin);

    printf("Digite o autor do livro: ");
    scanf("%99[^\n]s", author);
    fflush(stdin);

    StackNode *newNode = (StackNode*)malloc(sizeof(StackNode));
    strcpy(newNode->title, title);
    strcpy(newNode->author, author);
    newNode->next = top;

    return newNode;
}

// Função para remover um livro da pilha
StackNode* pop(StackNode *top) {
    if (top == NULL) {
        printf("A pilha está vazia.\n");
    } else {
        StackNode *temp = top;
        top = top->next;
        free(temp);
        printf("Livro removido da pilha com sucesso.\n");
    }
    return top;
}

// Função para escrever a fila de livros em um arquivo
void writeQueueToFile(QueueNode *front, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s para escrita.\n", filename);
        return;
    }

    QueueNode *current = front;
    while (current != NULL) {
        fprintf(file, "%s;%s\n", current->title, current->author);
        current = current->next;
    }

    fclose(file);
}

int main() {
    QueueNode *queueFront = createQueueFromFile("C:\\Users\\User\\Desktop\\lista03_ed\\fila_de_livros.txt");
    StackNode *stackTop = createStackFromFile("C:\\Users\\User\\Desktop\\lista03_ed\\pilha_de_livros.txt");

    int choice;

    // Define o valor das páginas de código UTF8 e default do Windows
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();

    // Define codificação como sendo UTF-8
    SetConsoleOutputCP(CPAGE_UTF8);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Exibir a fila de livros\n");
        printf("2. Inserir um livro na fila\n");
        printf("3. Inserir um livro na pilha\n");
        printf("4. Remover um livro da fila\n");
        printf("5. Remover um livro da pilha\n");
        printf("6. Exibir a pilha de livros\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);
        fflush(stdin);

        switch (choice) {
            case 1:
                printf("Fila de livros:\n");
                displayQueue(queueFront);
                break;
            case 2:
                queueFront = enqueue(queueFront);
                writeQueueToFile(queueFront, "C:\\Users\\User\\Desktop\\lista03_ed\\fila_de_livros.txt");
                printf("Livro inserido na fila com sucesso.\n");
                break;
            case 3:
                stackTop = push(stackTop);
                writeStackToFile(stackTop, "C:\\Users\\User\\Desktop\\lista03_ed\\pilha_de_livros.txt");
                printf("Livro inserido na pilha com sucesso.\n");
                break;
            case 4:
                queueFront = dequeue(queueFront);
                writeQueueToFile(queueFront, "C:\\Users\\User\\Desktop\\lista03_ed\\fila_de_livros.txt");
                break;
            case 5:
                stackTop = pop(stackTop);
                writeStackToFile(stackTop, "C:\\Users\\User\\Desktop\\lista03_ed\\pilha_de_livros.txt");
                break;
            case 6:
                printf("Pilha de livros:\n");
                displayStack(stackTop);
                break;
            case 7:
                exit(0);
            default:
                printf("Opção inválida.\n");
        }
    }

    // Retorna codificação padrão do Windows
    SetConsoleOutputCP(CPAGE_DEFAULT);
    return 0;
}