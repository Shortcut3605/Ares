#ifndef LIST_H
#define LIST_H

typedef struct LIST_STRUCT {
	void** data;
	int item_size;
	int size;
} list_T;

list_T* list_create(int size);

void list_push(list_T* list, void* item);

void list_destroy(list_T* list);

//TODO: IMPLEMENT PRINT

#endif // !LIST_H

