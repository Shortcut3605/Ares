#include "list.h"
#include "token.h"
#include "lexer.h"
#include "node.h"
#include "parser.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
int main() { // the main file
	
	lexer_T* lexer = lexer_create("e", "<stdin>");
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
	node_print(node);

	list_destroy(list);
}