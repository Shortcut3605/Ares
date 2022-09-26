#include "list.h"
#include "token.h"
#include "lexer.h"
#include "node.h"
#include "parser.h"
#include "interpreter.h"
#include "error.h"
#include "string.h"
#include "context.h"
#include "symboltable.h"
#include <stdio.h>
#include <stdlib.h>

list_T* read_file(const char* filename){
	FILE* ptr;
	char ch;
	string_T* res = string_create(4);
	list_T* ans = list_create(1);
	ptr = fopen(filename, "r");
	if(ptr == NULL){
		return NULL;
	}
	while(!feof(ptr)){
		ch = fgetc(ptr);
		if(ch=='\n'){
			list_push(ans, (void*)res);
			res = string_create(4);
		}
		string_push(res, ch);
	}
	res->str_size--;
	res->string[res->str_size]='\0';
	list_push(ans, (void*)res);
	return ans;
}

int main(int argc, char** argv) { // the main file

	if(argc < 2){
		return 1;
	}
	int len = 0;
	list_T* file_read = read_file(argv[1]);
	symboltable_T* global_symbol_table = symboltable_create(NULL);
		//symboltable_push(global_symbol_table, "a", v, 1);
		//symboltable_push(global_symbol_table, "a", v, 2);
	context_T context = context_create("<program>", NULL, position_create(-1, -1, -1, NULL, NULL));
	context.symboltable = global_symbol_table;
	for(int i = 0; i < file_read->item_size; i++){
		string_T* src = (string_T*)file_read->data[i];
		printf("%s\n",src->string);
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
		union VALUE_UNION v;
		v.i = 0;
		rtresult_T res = visit(node, context);
		if(res.error != NULL){
			char* _error = error_as_string(res.error);
			printf("%s\n", _error);
			free(_error);
			error_destroy(res.error);
			exit(1);
		}
		switch(res.number.type){
			case 1: printf("%d\n",res.number.value.i); break;
			case 2: printf("%f\n",res.number.value.f); break;
		}
		

		list_destroy(list);
		string_destroy(src);
	}
}