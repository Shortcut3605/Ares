#include "interpreter.h"
#include "node.h"
#include "number.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>

position_T* get_startpos(node_T* node) {
	switch (node->type) {
	case NT_NUMBER: return position_copy(((numbernode_T*)node)->tok->position); break;
	case NT_BINOP: return get_startpos(((binopnode_T*)node)->left); break;
	case NT_UNARY: return position_copy(((unaryopnode_T*)node)->op_tok->position); break;
	default: return NULL;
	}
}

position_T* get_endpos(node_T* node) {
	switch (node->type) {
	case NT_NUMBER: return position_copy(((numbernode_T*)node)->tok->position_end); break;
	case NT_BINOP: return get_startpos(((binopnode_T*)node)->left); break;
	case NT_UNARY: return position_copy(((unaryopnode_T*)node)->op_tok->position); break;
	default: return NULL;
	}
}

number_T visit(node_T* node) {
	switch (node->type) {
	case NT_NUMBER: return visit_NumberNode(node); break;
	case NT_BINOP: return visit_BinOpNode(node); break;
	case NT_UNARY: return visit_UnaryOpNode(node); break;
	default: break;
	}
}

number_T visit_NumberNode(node_T* node) {
	numbernode_T* nn = (numbernode_T*)node;
	if (nn->tok->hasDecimal) {
		return set_pos(number_create(2, -1, atof(nn->tok->value)), node->pos_start, node->pos_end);
	}
	return set_pos(number_create(1, atoi(nn->tok->value) ,-1.0), node->pos_start, node->pos_end);
}

number_T visit_BinOpNode(node_T* node) {
	binopnode_T* bn = (binopnode_T*)node;
	number_T left = visit(bn->left);
	number_T right = visit(bn->right);
	number_T result;
	switch (bn->op_tok->type) {
	case TT_PLUS: result = added_to(left, right); break;
	case TT_MINUS: result = subbed_by(left, right); break;
	case TT_MUL: result = multed_by(left, right); break;
	case TT_DIV: result = divided_by(left, right); break;
	default: printf("UNEXPECTED TOKEN\n"); break;
	}
	return set_pos(result, node->pos_start, node->pos_end);
}

number_T visit_UnaryOpNode(node_T* node) {
	unaryopnode_T* unop = (unaryopnode_T*)node;
	number_T number = visit(unop->right);
	if (unop->op_tok->type == TT_MINUS) {
		switch (number.type) {
		case 1: number.value.i *= -1; break;
		case 2: number.value.f *= -1; break;
		default: printf("WHAT IS IN FRONT OF THAT NUMBER ????? \n"); break;
		}
	}
	return set_pos(number, node->pos_start, node->pos_end);
}