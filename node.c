#include "node.h"
#include <stdlib.h>
#include <stdio.h>

node_T node_create(int type,position_T* pos_start, position_T* pos_end) {
	node_T node;
	node.type = type;
	node.pos_start = pos_start;
	node.pos_end = pos_end;
	return node;
}

void node_print(node_T* node) {
	switch (node->type) {
	case NT_NUMBER:
		token_print(((numbernode_T*)node)->tok);
		break;
	case NT_BINOP:
		printf("(\n");
		node_print(((binopnode_T*)node)->left);
		token_print(((binopnode_T*)node)->op_tok);
		node_print(((binopnode_T*)node)->right);
		printf(")\n");
		break;
	case NT_UNARY:
		printf("(\n");
		token_print(((unaryopnode_T*)node)->op_tok);
		node_print(((unaryopnode_T*)node)->right);
		printf(")\n");
		break;
	default:
		printf("?????? WHAT IS DIS NODE\n"); exit(1); break;
	}
}

node_T* numbernode_create(token_T* tok) {
	numbernode_T* numbernode = malloc(sizeof(struct NUMBERNODE_STRUCT));
	numbernode->tok = tok;
	numbernode->node = node_create(NT_NUMBER, tok->position, tok->position_end);
	return &numbernode->node;
}

node_T* binopnode_create(node_T* left, token_T* op_tok, node_T* right) {
	binopnode_T* binopnode = malloc(sizeof(struct BINOPNODE_STRUCT));
	binopnode->left = left;
	binopnode->op_tok = op_tok;
	binopnode->right = right;
	binopnode->node.type = NT_BINOP;
	binopnode->node.pos_start = left->pos_start;
	binopnode->node.pos_end = right->pos_end;
	return &(binopnode->node);
}

node_T* unaryopnode_create(token_T* op_tok, node_T* right) {
	unaryopnode_T* unaryopnode = malloc(sizeof(struct UNARYOPNODE_STRUCT));
	unaryopnode->node = node_create(NT_UNARY, op_tok->position, right->pos_end);
	unaryopnode->op_tok = op_tok;
	unaryopnode->right = right;
	return &(unaryopnode->node);
}

node_T* varaccessnode_create(token_T* var_name_tok){
	varaccessnode_T* varaccessnode = malloc(sizeof(struct VARACCESSNODE_STRUCT));
	varaccessnode->var_name_tok = var_name_tok;
	varaccessnode->node = node_create(NT_VARACCESS, var_name_tok->position, var_name_tok->position_end);
	return &(varaccessnode->node);
}

node_T* varassignnode_create(token_T* var_name_tok, node_T* value_node){
	varassignnode_T* varassignnode = malloc(sizeof(struct VARASSIGNNODE_STRUCT));
	varassignnode->var_name_tok = var_name_tok;
	varassignnode->value_node = value_node;
	varassignnode->node = node_create(NT_VARASSIGN, var_name_tok->position, var_name_tok->position_end);
	return &(varassignnode->node);
}