#include "string.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

string_T* string_create(int size) { // INVALID SIZE?
	string_T* string = malloc(sizeof(struct STRING_STRUCT));
	string->string = malloc(size);
	string->size = size;
	string->str_size = 0;
	return string;
}

string_T* string_create_string(char* string) {
	string_T* string_type = string_create(4);
	string_push_string(string_type, string);
	return string_type;
}

void string_push(string_T* string, char item) {
	if (string->str_size < string->size) {
		string->string[string->str_size++] = item;
		string->string[string->str_size] = '\0';
		return;
	}
	string->size *= 2;
	string->string = realloc(string->string, sizeof(char) * string->size);
	string->string[string->str_size++] = item;
	string->string[string->str_size] = '\0';
}

void string_push_string(string_T* string, char* item) {
	int diff = string->str_size - strlen(item);
	if (diff < 0) {
		diff = abs(diff);
		string->size += diff;
		string->string = realloc(string->string, string->size);
	}
	for (int i = 0; i < strlen(item); i++) {
		char ch = *(item+i);
		string_push(string, ch);
	}
}



void string_destroy(string_T* string) {
	free(string->string);
	free(string);
}

int string_rfind(string_T* string, char* substr, int start, int end) {
	char* ptr = string_getsubstr(string, start, end);
	char* originalPtr = ptr;
	char* found = NULL;

	while ((ptr = strstr(ptr, substr)) != NULL) {
		found = ptr++;
	}
	if (found) {
		return (found - originalPtr + 1);
	}
	return NULL;
}

int string_find(string_T* string, char* substr, int start, int end) {
	char* ptr = string_getsubstr(string, start, end);
	char* originalPtr = ptr;
	char* found = NULL;

	while ((ptr = strstr(ptr, substr)) != NULL) {
		found = ptr++;
		return (found - originalPtr + 1);
	}
	if (found) {
		return (found - originalPtr + 1);
	}
	return NULL;
}

string_T* string_getsubstr(string_T* string, int start, int end) {
	string_T* string_type = string_create(4);
	char* txt = string->string;
	for (int i = start; i <= end; i++) {
		char _char = string->string[i];
		string_push(string_type, _char);
	}
	return string_type;
}

char* string_replace(char* str, char* orig, char* rep)
{
	static char buffer[4096];
	char* p;
	int i = 0;

	while (str[i]) {
		if (!(p = strstr(str + i, orig)))  return str;
		strncpy(buffer + strlen(buffer), str + i, (p - str) - i);
		buffer[p - str] = '\0';
		strcat(buffer, rep);
		i = (p - str) + strlen(orig);
	}
	return buffer;
}