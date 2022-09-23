#ifndef PARSER_H
#define PARSER_H
#include "list.h"
#include "node.h"
typedef struct PARSER_STRUCT {
	list_T* tokenlist;
	int tok_idx;
	token_T* current_tok;
} parser_T;

parser_T* parser_create(list_T* tokenlist);

void parser_advance(parser_T* parser);

node_T* parser_factor(parser_T* parser);

node_T* parser_term(parser_T* parser);

node_T* parser_expr(parser_T* parser);

node_T* parser_parse(parser_T* parser);

position_T* node_position(node_T* node);

node_T* bin_op(parser_T* parser, int type, int OP1, int OP2);

#endif