#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void show_menu() {
	printf("\n=== СИСТЕМА ТЕСТИРОВАНИЯ ===\n");
    	printf("1. Математический тест\n");
    	printf("2. Тест по истории\n");
    	printf("3. Тест по программированию\n");
    	printf("4. Выйти\n");
    	printf("Выберите тест (1-4): ");
}

void run_test(const char* test_name) {
    	pid_t pid = fork();
    	if (pid == -1) {
        	perror("Ошибка создания процесса");
        	return;
    	}
    	if (pid == 0) {
        	char *args[] = {test_name, NULL};
        	if (execvp(test_name, args) == -1) {
            		perror("Ошибка запуска теста");
            		exit(1);
        	}
    	} else {
        	int status;
        	waitpid(pid, &status, 0);
        	printf("\nТест завершен. Нажмите Enter для продолжения...");
        	getchar(); getchar();
    	}
}

int main() {
	int choice;
    	while (1) {
        	show_menu();
        	scanf("%d", &choice);
        	getchar();
        	switch (choice) {
            	case 1:
                	printf("\nЗапуск математического теста...\n");
                	printf("Родительский PID: %d\n", getpid());
                	run_test("./math_test");
                	break;
            	case 2:
                	printf("\nЗапуск теста по истории...\n");
                	printf("Родительский PID: %d\n", getpid());
                	run_test("./history_test");
                	break;
            	case 3:
                	printf("\nЗапуск теста по программированию...\n");
                	printf("Родительский PID: %d\n", getpid());
                	run_test("./prog_test");
                	break;
            	case 4:
                	printf("Выход из системы тестирования.\n");
                	return 0;
            	default:
                	printf("Неверный выбор! Попробуйте снова.\n");
        	}
    	}
}
