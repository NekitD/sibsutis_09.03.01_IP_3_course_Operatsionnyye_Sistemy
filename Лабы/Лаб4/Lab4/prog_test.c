#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int math_test() {
	int score = 0;
    	char answer[10];
    	printf("\n=== ТЕСТ ПО ПРОГРАММИРОВАНИЮ ===\n");
    	printf("Процесс теста PID: %d (Родитель: %d)\n", getpid(), getppid());
    	// Вопрос 1
    	printf("\n1. Сколько байт весит переменная типа char?\n");
    	printf("a) 1\nb) 2\nc) 3\nВаш ответ: ");
    	scanf("%s", answer);
    	if (strcmp(answer, "a") == 0 || strcmp(answer, "1") == 0) {
        	printf("Правильно! +1 балл\n");
        	score++;
    	} else {
        	printf("Неправильно! Правильный ответ: 1\n");
    	}
    	// Вопрос 2
    	printf("\n2. Какого ключевого слова нет в C?\n");
    	printf("a) for\nb) while\nc) until\nВаш ответ: ");
    	scanf("%s", answer);
    	if (strcmp(answer, "c") == 0 || strcmp(answer, "until") == 0) {
        	printf("Правильно! +1 балл\n");
        	score++;
    	} else {
        	printf("Неправильно! Правильный ответ: until\n");
    	}
    	// Вопрос 3
    	printf("\n3. С чего начинается нумерация массива?\n");
    	printf("a) 0\nb) 1\nВаш ответ: ");
    	scanf("%s", answer);
    	if (strcmp(answer, "a") == 0 || strcmp(answer, "0") == 0) {
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
    else printf("Неудовлетворительно!\n");
    printf("\nНажмите Enter для возврата в меню...");
    getchar();
    return 0;
}
