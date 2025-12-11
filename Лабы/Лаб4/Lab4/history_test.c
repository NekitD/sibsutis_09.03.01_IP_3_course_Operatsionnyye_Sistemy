#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int history_test() {
	int score = 0;
	char answer[10];
	printf("\n=== ТЕСТ ПО ИСТОРИИ ===\n");
	printf("Процесс теста PID: %d (Родитель: %d)\n", getpid(), getppid());
	// Вопрос 1
	printf("\n1. В каком году началась Вторая мировая война?\n");
	printf("a) 1939\nb) 1941\nc) 1937\nВаш ответ: ");
	scanf("%s", answer);
	if (strcmp(answer, "a") == 0 || strcmp(answer, "1939") == 0) {
		printf("Правильно! +1 балл\n");
        	score++;
    	}
    	// Вопрос 2
    	printf("\n2. Кто был первым президентом России?\n");
    	printf("a) Ельцин\nb) Горбачев\nc) Путин\nВаш ответ: ");
    	scanf("%s", answer);
    	if (strcmp(answer, "a") == 0) {
        	printf("Правильно! +1 балл\n");
        	score++;
    	}
    	return score;
}

int main() {
	int score = history_test();
	printf("\nРезультат: %d/2\n", score);
	if (score == 2) printf("Отлично!\n");
	else if (score == 1) printf("Удовлетворительно!\n");
	else printf("Неудовлетворительно\n");
	printf("Нажмите Enter для возврата...");
	getchar();
	return 0;
}

