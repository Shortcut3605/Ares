#ifndef NODE_H
#define NODE_H
#include "token.h"
typedef struct NODE_STRUCT {
	enum {
		NT_NUMBER,
		NT_BINOP,
		NT_UNARY,
	} type;
} node_T;

node_T node_create(int type);

void node_print(node_T* node);

typedef struct NUMBERNODE_STRUCT {
	node_T node;
	token_T* tok;
} numbernode_T;

node_T* numbernode_create(token_T* tok);

typedef struct BINOPNODE_STRUCT {
	node_T node;
	node_T* left;
	token_T* op_tok;
	node_T* right;
} binopnode_T;

node_T* binopnode_create(node_T* left, token_T* op_tok, node_T* right);

typedef struct UNARYOPNODE_STRUCT
{
	node_T node;
	token_T* op_tok;
	node_T* right;
} unaryopnode_T;

node_T* unaryopnode_create(token_T* op_tok, node_T* right);

#endif