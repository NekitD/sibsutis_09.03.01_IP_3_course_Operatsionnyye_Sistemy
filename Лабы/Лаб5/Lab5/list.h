#ifndef LIST_H
#define LIST_H

typedef struct node {
	int data;
	struct node* next;
} Node;

typedef struct list {
	Node* head;
	Node* tail;
} List;

void init_list(List* L); 
void add_front(List* L, int data);
void add_end(List* L, int data);
void delete_node(List* L, int data);
void print_list(List* L);
void find_elem(List* L, int data);
int list_length(List* L);
void free_list(List* L);

#endif
