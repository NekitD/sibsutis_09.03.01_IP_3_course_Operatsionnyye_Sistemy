#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int math_test() {
	int score = 0;
	char answer[10];
	printf("\n=== МАТЕМАТИЧЕСКИЙ ТЕСТ ===\n");
	printf("Процесс теста PID: %d (Родитель: %d)\n", getpid(), getppid());
	// Вопрос 1
	printf("\n1. Сколько будет 2 + 2 × 2?\n");
	printf("a) 6\nb) 8\nc) 4\nВаш ответ: ");
	scanf("%s", answer);
	if (strcmp(answer, "a") == 0 || strcmp(answer, "6") == 0) {
        	printf("Правильно! +1 балл\n");
        	score++;
    	} else {
        	printf("Неправильно! Правильный ответ: 6\n");
    	}
    	// Вопрос 2
    	printf("\n2. Чему равен квадратный корень из 64?\n");
    	printf("a) 6\nb) 8\nc) 7\nВаш ответ: ");
    	scanf("%s", answer);
    	if (strcmp(answer, "b") == 0 || strcmp(answer, "8") == 0) {
        	printf("Правильно! +1 балл\n");
        	score++;
    	} else {
        	printf("Неправильно! Правильный ответ: 8\n");
    	}
    	// Вопрос 3
    	printf("\n3. Решите уравнение: 3x - 7 = 14\n");
    	printf("a) x=5\nb) x=7\nc) x=9\nВаш ответ: ");
    	scanf("%s", answer);
    	if (strcmp(answer, "b") == 0 || strcmp(answer, "7") == 0) {
        	printf("Правильно! +1 балл\n");
        	score++;
    	} else {
        	printf("Неправильно! Правильный ответ: x=7\n");
    	}
    	return score;
}

int main() {
	int score = math_test();
    	printf("\n=== РЕЗУЛЬТАТЫ ТЕСТА ===\n");
    	printf("Ваш результат: %d/3\n", score);
    	if (score == 3) printf("Отлично!\n");
    	else if (score == 2) printf("Хорошо!\n");
    	else if (score == 1) printf("Удовлетворительно!\n");
    	else printf("Неудовлетворительно\n");
    	printf("\nНажмите Enter для возврата в меню...");
    	getchar(); getchar();
    	return 0;
}
