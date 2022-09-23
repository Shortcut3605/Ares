#ifndef STRING_H
#define STRING_H

typedef struct STRING_STRUCT {
	char* string;
	int str_size;
	int size;
} string_T;

string_T* string_create(int size);

string_T* string_create_string(char* string);

void string_push(string_T* string, char item);

void string_push_string(string_T* string, char* item);

void string_destroy(string_T* string);

int string_rfind(string_T* string, char* substr, int start, int end);

int string_find(string_T* string, char* substr, int start, int end);

string_T* string_getsubstr(string_T* string, int start, int end);

char* string_replace(char* str, char* orig, char* rep);

#endif