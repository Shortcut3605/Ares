#include "token.h"
#include "position.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

token_T* token_create(int type, char* value, position_T* position, position_T* position_end) {
	token_T* token = malloc(sizeof(struct TOKEN_STRUCT));
	if (type < TT_INT || type > TT_EOF) {
		//ERROR
		printf("<TOKEN CREATE encountered type `%d`>\n", type);
		free(token);
		exit(1);
	}
	token->type = type;
	token->value = value;
	token->position = position_copy(position);
	if (position_end != NULL) {
		token->position_end = position_copy(position_end);
	}
	else { token->position_end = NULL; }
	token->hasDecimal = 0;
	return token;
}

char* token_type_to_str(int type) {
	switch (type) {
	case TT_INT: return "TT_INT";
	case TT_FLOAT: return "TT_FLOAT";
	case TT_PLUS: return "TT_PLUS";
	case TT_MINUS: return "TT_MINUS";
	case TT_MUL: return "TT_MUL";
	case TT_DIV: return "TT_DIV";
	case TT_POW: return "TT_POW";
	case TT_LPAREN: return "TT_LPAREN";
	case TT_RPAREN: return "T_RPAREN";
	default: { printf("<TOKEN TYPE TO STR encountered type `%d`>", type); exit(1); } break;
	}
}

void token_print(token_T* token) {
	printf("<TOKEN PRINT type = `%s`, value = `%s`>\n", token_type_to_str(token->type), (token->value == NULL) ? "NONE" : token->value);
}

char matches(token_T* tok, int type, char* value){
	if(tok->type == type && strcmp(tok->value,value)==0){
		return 1;
	}
	return 0;
}