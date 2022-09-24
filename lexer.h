#ifndef LEXER_H
#define LEXER_H
#include "token.h"
#include "list.h"
#include "position.h"
#include "error.h"
typedef struct LEXER_STRUCT {
	char* src;
	int src_len;
	position_T* pos;
	char current_char;
	error_T* error;
} lexer_T;

void lexer_advance(lexer_T* lexer);

void lexer_skip_whitespace(lexer_T* lexer);

lexer_T* lexer_create(char* src, char* fn);

token_T* lexer_make_number(lexer_T* lexer);

list_T* lexer_make_tokens(lexer_T* lexer);

#endif // !LEXER_H

