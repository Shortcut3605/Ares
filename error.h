#ifndef ERROR_H
#define ERROR_H
#include "position.h"
typedef struct ERROR_STRUCT {
	char* error_name;
	char* details;
	position_T* position_start;
	position_T* position_end;
} error_T;

error_T* error_create(char* error_name, char* details, position_T* position_start, position_T* position_end);

char* error_as_string(error_T* error);

char* error_add_arrows(char* txt, position_T* position_start, position_T* position_end);

void error_destroy(error_T* error);

// ACTUAL ERRORS

error_T* IllegalCharacterError(char* details, position_T* position_start, position_T* position_end);

error_T* InvalidSyntaxError(char* details, position_T* position_start, position_T* position_end);

error_T* RTError(char* details, position_T* position_start, position_T* position_end);


#endif