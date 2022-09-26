#include "lexer.h"
#include "token.h"
#include "string.h"
#include "position.h"
#include "error.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

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

char isKeyword(char* str){
	char* KEYWORDS[] = {"and","or","not"};
	int KEYWORDS_LEN = 3;
	
	for(int i = 0; i < KEYWORDS_LEN; i++){
		if(strcmp(KEYWORDS[i],str)==0){
			return 1;
		}	
	}
	return 0;
}

token_T* lexer_make_identifier(lexer_T* lexer) {
	string_T* id_str = string_create(4);
	position_T* pos_start = position_copy(lexer->pos);
	while(lexer->current_char != -1 && ((isdigit(lexer->current_char) || isalpha(lexer->current_char)) || lexer->current_char == '_')){
		string_push(id_str, lexer->current_char);
		lexer_advance(lexer);
	}
	token_T* tok;
	
	if(isKeyword(id_str->string)){
		tok = token_create(TT_KEYWORD, id_str->string, pos_start ,lexer->pos);
		return tok;
	}
	tok = token_create(TT_IDENTIFIER, id_str->string, pos_start ,lexer->pos);
	return tok;
}

token_T* make_not_equals(lexer_T* lexer){
	position_T* pos_start = position_copy(lexer->pos);
	lexer_advance(lexer);
	if(lexer->current_char == '='){
		lexer_advance(lexer);
		return token_create(TT_NE, NULL, pos_start, lexer->pos);
	}
	lexer_advance(lexer);
	lexer->error = error_create("Expected Character", '`=` (after `!`)', pos_start, lexer->pos);
	return NULL;
}

token_T* make_equals(lexer_T* lexer){
	position_T* pos_start = position_copy(lexer->pos);
	lexer_advance(lexer);
	if(lexer->current_char == '='){
		lexer_advance(lexer);
		return token_create(TT_EE, NULL, pos_start, lexer->pos);
	}
	return token_create(TT_EQ, NULL, pos_start, lexer->pos);
}

token_T* make_less_than(lexer_T* lexer){
	position_T* pos_start = position_copy(lexer->pos);
	lexer_advance(lexer);
	if(lexer->current_char == '='){
		lexer_advance(lexer);
		return token_create(TT_LTE, NULL, pos_start, lexer->pos);
	}
	return token_create(TT_LT, NULL, pos_start, lexer->pos);
}

token_T* make_greater_than(lexer_T* lexer){
	position_T* pos_start = position_copy(lexer->pos);
	lexer_advance(lexer);
	if(lexer->current_char == '='){
		lexer_advance(lexer);
		return token_create(TT_GTE, NULL, pos_start, lexer->pos);
	}
	return token_create(TT_GT, NULL, pos_start, lexer->pos);
}

list_T* lexer_make_tokens(lexer_T* lexer) {
	list_T* list = list_create(1);

	while (lexer->current_char != -1) {
		lexer_skip_whitespace(lexer);
		if ('0' <= lexer->current_char && lexer->current_char <= '9') {
			list_push(list, (void*)lexer_make_number(lexer));
			continue;
		}
		else if('a' <= lexer->current_char && lexer->current_char <= 'z'){
			list_push(list, (void*)lexer_make_identifier(lexer));
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
				case '^': list_push(list, (void*)token_create(TT_POW, NULL, lexer->pos, NULL)); break;
				case '(': list_push(list, (void*)token_create(TT_LPAREN, NULL, lexer->pos, NULL)); break;
				case ')': list_push(list, (void*)token_create(TT_RPAREN, NULL, lexer->pos, NULL)); break;
				case '!':{
					token_T* tok = make_not_equals(lexer);
					if(tok==NULL){
						//error
						return NULL;
					}
					list_push(list, (void*)tok);
					break;
				}
				case '=': list_push(list, (void*)make_equals(lexer)); break; 
				case '<': list_push(list, (void*)make_less_than(lexer)); break;
				case '>': list_push(list, (void*)make_greater_than(lexer)); break;
				case '\n': break;
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