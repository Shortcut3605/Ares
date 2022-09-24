#include "error.h"
#include "string.h"
#include "math.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

error_T* error_create(char* error_name, char* details, position_T* position_start, position_T* position_end) {
	error_T* error = malloc(sizeof(struct ERROR_STRUCT));
	error->error_name = error_name;
	error->details = details;
	error->position_start = position_start;
	error->position_end = position_end;	
	return error;
}

char* error_as_string(error_T* error) {
	const char* template = "%s: %s\nFile %s, line %d\n\n%s";
	char* str = error_add_arrows(error->position_start->ftxt, error->position_start, error->position_end);
	char* buff = malloc(((sizeof(template) + sizeof(error->error_name) + sizeof(error->details) + sizeof(error->position_start->fn) + sizeof(str)) * sizeof(char) + ((sizeof(error->position_start->ln)) * sizeof(int)) + 1));
	sprintf(buff, template, error->error_name, error->details, error->position_start->fn, error->position_start->ln+1, str);
	return buff;
}

char* error_add_arrows(char* txt, position_T* position_start, position_T* position_end) {
	string_T* result = string_create(4);
	string_T* text = string_create_string(txt);
	int idx_start = MAX(string_rfind(text, (char*)"\n", 0, position_start->idx), 0);
	int idx_end = string_find(text, (char*)"\n", idx_start + 1, text->str_size);
	if (idx_end < 0) {
		idx_end = strlen(text->string);
	}
	int line_count = 0;
	line_count = position_end->ln - position_start->ln + 1;
	string_T* line = NULL;
	for (int i = 0; i < line_count; i++) {
		line = string_getsubstr(text, idx_start, idx_end);
		int col_start = (i == 0) ? position_start->col : 0;
		int col_end = (i == line_count-1) ? position_end->col : (strlen(line)-1);
		string_push_string(result, line->string);
		string_push(result, '\n');
		for (int j = 0; j < col_start; j++) {
			string_push(result, ' ');
		}
		for (int j = 0; j < (col_end-col_start); j++) {
			string_push(result, '^');
		}
		idx_start = idx_end;
		idx_end = string_find(text, (char*)"\n", idx_start + 1, text->str_size);
		if (idx_end < 0) { idx_end = strlen(text->string); }
	}
	return string_replace(result->string, (char*)"\t", (char*)"");
}

void error_destroy(error_T* error){
	free(error);
}

error_T* IllegalCharacterError(char* details, position_T* position_start, position_T* position_end) {
	return error_create("Illegal Character", details, position_start, position_end);
}


error_T* InvalidSyntaxError(char* details, position_T* position_start, position_T* position_end) {
	return error_create("Invalid Syntax", details, position_start, position_end);
}

error_T* RTError(char* details, position_T* position_start, position_T* position_end){
	return error_create("Runtime Error", details, position_start, position_end);
}