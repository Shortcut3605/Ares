#include "lexer.h"
#include "token.h"
#include "string.h"
#include "position.h"
#include "error.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void lexer_advance(lexer_T* lexer) {
	position_advance(lexer->pos, lexer->current_char);
	if (lexer->pos->idx < lexer->src_len) {
		lexer->current_char = lexer->src[lexer->pos->idx];
		return;
	}
	lexer->current_char = -1;
}

void lexer_skip_whitespace(lexer_T* lexer) {
	while ((lexer->current_char == ' ' || lexer->current_char == '\t') && lexer->current_char != -1) {
		lexer_advance(lexer);
	}
}

lexer_T* lexer_create(char* src, char* fn) {
	lexer_T* lexer = malloc(sizeof(struct LEXER_STRUCT));
	lexer->src = src;
	lexer->src_len = strlen(lexer->src);
	lexer->pos = position_create(-1, 0, -1, fn, src);
	lexer->current_char = -1;
	lexer->error = NULL;
	lexer_advance(lexer);
	return lexer;
}

token_T* lexer_make_number(lexer_T* lexer) { // TODO MAKE STRINGS MORE EFFICIENT : A FINISH STRING METHOD TO MAKE SURE NOT ALLOCATING UNNECESSARY MEMORY
	string_T* value = string_create(1);
	char dot = 0;
	position_T* start_pos = position_copy(lexer->pos);
	while (('0' <= lexer->current_char && lexer->current_char <= '9') || lexer->current_char == '.')
	{
		if (lexer->current_char == '.') {
			if (dot == 1) {
				printf("<LEXER MAKE NUMBER encountered many decimals while trying to parse number: FILE: %s, LINE: %d, COL: %d>\n",lexer->pos->fn, lexer->pos->ln, lexer->pos->col);
				exit(1);
			}
			dot++;
		}
		string_push(value, lexer->current_char);
		lexer_advance(lexer);
	}
	
	if (dot) {
		token_T* tok = token_create(TT_FLOAT, value->string, start_pos, lexer->pos);
		tok->hasDecimal = 1;
		return tok;
	}
	else {
		return token_create(TT_INT, value->string, start_pos, lexer->pos);
	}
}

list_T* lexer_make_tokens(lexer_T* lexer) {
	list_T* list = list_create(1);

	while (lexer->current_char != -1) {
		lexer_skip_whitespace(lexer);
		if ('0' <= lexer->current_char && lexer->current_char <= '9') {
			list_push(list, (void*)lexer_make_number(lexer));
			continue;
		}
		else {
			if (lexer->current_char == -1) {
				break;
			}
			else {
				switch (lexer->current_char) {
				case '+': list_push(list, (void*)token_create(TT_PLUS, NULL, lexer->pos, NULL)); break;
				case '-': list_push(list, (void*)token_create(TT_MINUS, NULL, lexer->pos, NULL)); break;
				case '*': list_push(list, (void*)token_create(TT_MUL, NULL, lexer->pos, NULL)); break;
				case '/': list_push(list, (void*)token_create(TT_DIV, NULL, lexer->pos, NULL)); break;
				case '(': list_push(list, (void*)token_create(TT_LPAREN, NULL, lexer->pos, NULL)); break;
				case ')': list_push(list, (void*)token_create(TT_RPAREN, NULL, lexer->pos, NULL)); break;
				default: {
					position_T* position_start = position_copy(lexer->pos);
					const char* template = "`%c`";
					char* buff = malloc((sizeof(template) + sizeof(char) * sizeof(char) + 1));
					sprintf(buff, template, lexer->current_char);
					lexer_advance(lexer);
					lexer->error = IllegalCharacterError(buff, position_start, lexer->pos);
					return NULL;
				}
				}
				lexer_advance(lexer);
			}
		}
	}
	list_push(list, (void*)token_create(TT_EOF, NULL, lexer->pos, NULL));
	return list;
}