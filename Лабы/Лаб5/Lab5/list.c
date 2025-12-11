#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void init_list(List* L) {
    L->head = NULL;
    L->tail = NULL;
}

void add_front(List* L, int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return;
    }
    new_node->data = data;
    new_node->next = L->head;
    L->head = new_node;

    if (L->tail == NULL) {
        L->tail = new_node;
    }
}

void add_end(List* L, int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return;
    }
    new_node->data = data;
    new_node->next = NULL;

    if (L->tail == NULL) {
        L->head = L->tail = new_node;
    } else {
        L->tail->next = new_node;
        L->tail = new_node;
    }
}

void delete_node(List* L, int data) {
    if (L->head == NULL) return;

    if (L->head->data == data) {
        Node* temp = L->head;
        L->head = L->head->next;

        if (L->head == NULL) {
            L->tail = NULL;
        }
        free(temp);
        return;
    }

    Node* current = L->head;
    while (current->next != NULL && current->next->data != data) {
        current = current->next;
    }

    if (current->next != NULL) {
        Node* temp = current->next;
        current->next = current->next->next;
        if (current->next == NULL) {
            L->tail = current;
        }
        free(temp);
    }
}

void print_list(List* L) {
    Node* current = L->head;
    printf("Список: ");
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf(" -> NULL\n");
}

void find_elem(List* L, int data) {
    Node* current = L->head;
    int counter = 0;
    while (current != NULL) {
        if (current->data == data) {
            printf("Элемент найден в позиции: %d \n", counter);
            return;
        }
        current = current->next;
        counter++;
    }
    printf("Элемент не найден\n");
}

int list_length(List* L) {
    int count = 0;
    Node* current = L->head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void free_list(List* L) {
    Node* current = L->head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    L->head = NULL;
    L->tail = NULL;
}
