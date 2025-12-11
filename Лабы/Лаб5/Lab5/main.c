#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "list.h"


void functions_list(const char* filename) {
    printf("\nЭкспортированные функции:\n");
    printf("---------------------------\n");
    char command[512];
    strcpy(command, "nm -D --defined-only ");
    strcat(command, filename);
    strcat(command, " | grep ' T ' | cut -d' ' -f3");
    printf("Команда: %s\n", command);
    printf("---------------------------\n");
    printf("Результат:\n");
    system(command);
    printf("\n");
}



int main() {
    functions_list("liblist.so");
    List my_list;
    init_list(&my_list);
    int choice, data;

    while (1) {

        printf("\n");
        print_list(&my_list);
        printf("\n");
        printf("Длина списка: %d\n", list_length(&my_list));
        printf("\n");

        printf("1 - Добавить в начало\n");
        printf("2 - Добавить в конец\n");
        printf("3 - Найти элемент\n");
        printf("4 - Удалить элемент\n");
        printf("5 - Очистить список\n");
        printf("Другое - Выход из программы\n\n");

        printf("Выберите действие: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Введите число: ");
                scanf("%d", &data);
                add_front(&my_list, data);
                break;

            case 2:
                printf("Введите число: ");
                scanf("%d", &data);
                add_end(&my_list, data);
                break;

            case 3:
                printf("Введите число: ");
                scanf("%d", &data);
                find_elem(&my_list, data);
                printf("\n");
                break;

            case 4:
                printf("Введите число: ");
                scanf("%d", &data);
                delete_node(&my_list, data);
                break;

            case 5:
                free_list(&my_list);
                break;

            default:
                return 0;
        }
    }

    return 0;
}
