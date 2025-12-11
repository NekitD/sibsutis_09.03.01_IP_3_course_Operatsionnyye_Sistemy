#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>
#include <string.h>

typedef struct List{
    void* head;
    void* tail;
} List;

typedef void (*init_list_func)(List*);
typedef int (*list_length_func)(List*);
typedef void (*add_front_func)(List*, int);
typedef void (*add_end_func)(List*, int);
typedef void (*print_list_func)(List*);
typedef void (*free_list_func)(List*);
typedef void (*delete_node_func)(List*, int);
typedef void (*find_elem_func)(List*, int);

void show_maps(pid_t pid) {
    printf("\n--- Current Memory Maps ---\n");
    char command[256];
    snprintf(command, sizeof(command), "grep liblist.so /proc/%d/maps", pid);
    system(command);
}

void show_menu() {
    printf("\n=== Dynamic Library Loader ===\n");
    printf("1. Загрузить библиотеку\n");
    printf("2. Режим использования функций библиотеки\n");
    printf("3. Распложения в памяти\n");
    printf("4. Выгрузить библиотеку\n");
    printf("5. Завершение работы\n");
    printf("Введите команду: ");
}

void lab5_main(init_list_func init_list,
               list_length_func list_length,
               add_front_func add_front,
               add_end_func add_end,
               print_list_func print_list,
               free_list_func free_list,
               delete_node_func delete_node,
               find_elem_func find_elem);

int main() {
    pid_t pid = getpid();
    void* handle = NULL;

    init_list_func init_list = NULL;
    list_length_func list_length = NULL;
    add_front_func add_front = NULL;
    add_end_func add_end = NULL;
    print_list_func print_list = NULL;
    free_list_func free_list = NULL;
    delete_node_func delete_node = NULL;
    find_elem_func find_elem = NULL;

    printf("Process PID: %d\n", pid);

    int choice;
    while (1) {
        show_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (handle) {
                    printf("Библиотека уже загружена!\n");
                    break;
                }
                handle = dlopen("./liblist.so", RTLD_LAZY);
                if (handle) {
                    printf("Библиотека успешно загружена!\n");

                    init_list = (init_list_func)dlsym(handle, "init_list");
                    list_length = (list_length_func)dlsym(handle, "list_length");
                    add_front = (add_front_func)dlsym(handle, "add_front");
                    add_end = (add_end_func)dlsym(handle, "add_end");
                    print_list = (print_list_func)dlsym(handle, "print_list");
                    free_list = (free_list_func)dlsym(handle, "free_list");
                    delete_node = (delete_node_func)dlsym(handle, "delete_node");
                    find_elem = (find_elem_func)dlsym(handle, "find_elem");

                    if (!init_list || !list_length || !add_front || !add_end ||
                        !print_list || !free_list || !delete_node || !find_elem) {
                        printf("Ошибка: не все функции найдены в библиотеке!\n");
                        dlclose(handle);
                        handle = NULL;
                    } else {
                        printf("Все функции успешно загружены!\n");
                        show_maps(pid);
                    }
                } else {
                    printf("Error: %s\n", dlerror());
                }
                break;

            case 2:
                if (!handle) {
                    printf("Библиотека не была загружена!\n");
                    break;
                }
                printf("Режим использования функций библиотеки.\n");
                lab5_main(init_list, list_length, add_front, add_end,
                         print_list, free_list, delete_node, find_elem);
                break;

            case 3:
                show_maps(pid);
                break;

            case 4:
                if (handle) {
                    List temp_list;
                    if (init_list && free_list) {
                        init_list(&temp_list);
                        free_list(&temp_list);
                    }
                    dlclose(handle);
                    handle = NULL;
                    init_list = NULL;
                    list_length = NULL;
                    add_front = NULL;
                    add_end = NULL;
                    print_list = NULL;
                    free_list = NULL;
                    delete_node = NULL;
                    find_elem = NULL;
                    printf("Библиотека выгружена!\n");
                    show_maps(pid);
                } else {
                    printf("Нет загруженных библиотек!\n");
                }
                break;

            case 5:
                if (handle) {
                    List temp_list;
                    if (init_list && free_list) {
                        init_list(&temp_list);
                        free_list(&temp_list);
                    }
                    dlclose(handle);
                }
                printf("Завершение работы...\n");
                return 0;

            default:
                printf("Команда не найдена!\n");
        }
    }
}

void lab5_main(init_list_func init_list,
               list_length_func list_length,
               add_front_func add_front,
               add_end_func add_end,
               print_list_func print_list,
               free_list_func free_list,
               delete_node_func delete_node,
               find_elem_func find_elem) {

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
        printf("Другое - Выход из режима\n\n");

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
                init_list(&my_list);
                break;

            default:
                free_list(&my_list);
                return;
        }
    }
}
