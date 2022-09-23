#include "list.h"
#include <stdlib.h>
list_T* list_create(int size) {
	list_T* list = malloc(sizeof(struct LIST_STRUCT));
	list->size = size;
	list->item_size = 0;
	list->data = malloc(sizeof(void*) * size);
	if (list->data == NULL) {
		// error
	}
	return list;
}

void list_push(list_T* list, void* item) {
	if (list->item_size < list->size) {
		list->data[list->item_size++] = item;
		return;
	}
	list->size *= 2;
	list->data = realloc(list->data, sizeof(void*) * list->size);
	if (list->data == NULL) {
		// ERROR
		return;
	}
	list->data[list->item_size++] = item;
}

void list_destroy(list_T* list) {
	for (int i = 0; i < list->item_size; i++) {
		free(list->data[i]);
	}
	free(list->data);
	free(list);
}
