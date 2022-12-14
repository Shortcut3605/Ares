#ifndef TOKEN_H
#define TOKEN_H
#include "position.h"
typedef struct TOKEN_STRUCT {
	char* value;
	enum {
		TT_INT,
		TT_FLOAT,
		TT_IDENTIFIER,
		TT_KEYWORD,
		TT_PLUS,
		TT_MINUS,
		TT_MUL,
		TT_DIV,
		TT_POW,
		TT_EQ,
		TT_LPAREN,
		TT_RPAREN,
		TT_EE,
		TT_NE,
		TT_LT,
		TT_GT,
		TT_LTE,
		TT_GTE,
		TT_EOF,
	} type; 
	position_T* position;
	position_T* position_end;
	char hasDecimal;
} token_T;

char* token_type_to_str(int type);

token_T* token_create(int type, char* value , position_T* position, position_T* position_end);

void token_print(token_T* token);

char matches(token_T* tok, int type, char* value);

#endif // !TOKEN_H

