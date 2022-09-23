#include "parser.h"
#include "token.h"
#include <stdlib.h>
#include <stdio.h>

parser_T* parser_create(list_T* tokenlist) {
	parser_T* parser = malloc(sizeof(struct PARSER_STRUCT));
	parser->tokenlist = tokenlist;
	parser->tok_idx = -1;
	parser->current_tok = NULL;
	parser_advance(parser);
	return parser;
}

void parser_advance(parser_T* parser) {
	parser->tok_idx++;
	if (parser->tok_idx < parser->tokenlist->item_size) {
		parser->current_tok = (token_T*)parser->tokenlist->data[parser->tok_idx];
	}
}

node_T* parser_factor(parser_T* parser) {
	token_T* tok = parser->current_tok;
	node_T* factor = NULL;
	node_T* expr = NULL;
	if (tok->type == TT_PLUS || tok->type == TT_MINUS) {
		parser_advance(parser);
		factor = parser_factor(parser);
		return unaryopnode_create(tok, factor);
	}
	else if (tok->type == TT_INT || tok->type == TT_FLOAT) {
		parser_advance(parser);
		return numbernode_create(tok);
	}
	else if (tok->type == TT_LPAREN) {
		parser_advance(parser);
		expr = parser_expr(parser);
		if (parser->current_tok->type == TT_RPAREN) {
			parser_advance(parser);
		}
		return expr;
	}
	printf("<PARSER FACTOR Invalid syntax: expected INT or FLOAT in FILE %s, LINE %d COL %d", tok->position->fn, tok->position->ln , tok->position->col);
	exit(1);
}

node_T* parser_term(parser_T* parser) {
	return bin_op(parser, 0, TT_MUL, TT_DIV);
}

node_T* parser_expr(parser_T* parser) {
	return bin_op(parser, 1, TT_PLUS, TT_MINUS);
}

node_T* parser_parse(parser_T* parser) {
	node_T* ast = parser_expr(parser);
	if (parser->current_tok->type != TT_EOF) {
		printf("Did not end at the end of file.\n");
		exit(1);
	}
	return ast;
}

position_T* node_position(node_T* node) {
	switch (node->type) {
	case NT_NUMBER:	return ((numbernode_T*)node)->tok->position;
	case NT_BINOP: return ((binopnode_T*)node)->op_tok->position;
	case NT_UNARY: return ((unaryopnode_T*)node)->op_tok->position;
	}
}

node_T* bin_op(parser_T* parser, int type, int OP1, int OP2) {
	node_T* left = NULL;
	node_T* right = NULL;
	token_T* op_tok = NULL;
	switch (type) {
	case 0: left = parser_factor(parser); break;
	case 1: left = parser_term(parser); break;
	}
	while (parser->current_tok->type == OP1 || parser->current_tok->type == OP2) {
		op_tok = parser->current_tok;
		parser_advance(parser);
		switch (type) {
		case 0: right = parser_factor(parser); break;
		case 1: right = parser_term(parser); break;
		}
		left = binopnode_create(left, op_tok, right);
	}
	if (right == NULL && op_tok != NULL) {
		position_T* pos = node_position(left);
		printf("Parser expected +, -, / or * in FILE %s, LINE %d COL %d\n", pos->fn, pos->ln, pos->col);
		exit(1);
	}
	return left;
}