#ifndef TOKEN_H
#define TOKEN_H
#include "position.h"
typedef struct TOKEN_STRUCT {
	char* value;
	enum {
		TT_INT,
		TT_FLOAT,
		TT_PLUS,
		TT_MINUS,
		TT_MUL,
		TT_DIV,
		TT_LPAREN,
		TT_RPAREN,
		TT_EOF,
	} type; 
	position_T* position;
} token_T;

char* token_type_to_str(int type);

token_T* token_create(int type, char* value , position_T* position);

void token_print(token_T* token);

#endif // !TOKEN_H

