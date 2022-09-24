#include "list.h"
#include "token.h"
#include "lexer.h"
#include "node.h"
#include "parser.h"
#include "interpreter.h"
#include "error.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

string_T* read_file(const char* filename){
	FILE* ptr;
	char ch;
	string_T* res = string_create(4);
	ptr = fopen(filename, "r");
	if(ptr == NULL){
		return NULL;
	}
	while(!feof(ptr)){
		ch = fgetc(ptr);
		string_push(res, ch);
	}
	res->str_size--;
	res->string[res->str_size]='\0';
	return res;
}

int main(int argc, char** argv) { // the main file

	if(argc < 2){
		return 1;
	}
	string_T* src = read_file(argv[1]);
	if(src==NULL){return 1;}
	lexer_T* lexer = lexer_create(src->string, "<stdin>");
	list_T* list = lexer_make_tokens(lexer);
	if (lexer->error != NULL) {
		char* res = error_as_string(lexer->error);
		printf("%s\n", res);
		free(res);
		error_destroy(lexer->error);
		exit(1);
	}
	//node_T* node = binopnode_create(numbernode_create(token_create(0, "1")), token_create(2, NULL), numbernode_create(token_create(0, "2")));
	parser_T* parser = parser_create(list);
	node_T* node = parser_expr(parser);
	//node_print(node);
	number_T number = visit(node);
	switch (number.type) {
	case 1: printf("%d\n", number.value.i); break;
	case 2: printf("%f\n", number.value.f); break;
	}
	

	list_destroy(list);
	string_destroy(src);
}