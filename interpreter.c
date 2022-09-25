#include "interpreter.h"
#include "node.h"
#include "number.h"
#include "token.h"
#include "result.h"
#include "error.h"
#include "context.h"
#include <stdio.h>
#include <stdlib.h>

rtresult_T visit(node_T* node, context_T context) {
	switch (node->type) {
	case NT_NUMBER: return visit_NumberNode(node, context); break;
	case NT_BINOP: return visit_BinOpNode(node, context); break;
	case NT_UNARY: return visit_UnaryOpNode(node, context); break;
	default: break;
	}
}

rtresult_T visit_NumberNode(node_T* node, context_T context) {
	numbernode_T* nn = (numbernode_T*)node;
	if (nn->tok->hasDecimal) {
		return rtresult_success(rtresult_create(),set_context(set_pos(number_create(2, -1, atof(nn->tok->value)), node->pos_start, node->pos_end),context));
	}
	return rtresult_success(rtresult_create(),set_context(set_pos(number_create(1, atoi(nn->tok->value) ,-1.0), node->pos_start, node->pos_end),context));
}

rtresult_T visit_BinOpNode(node_T* node, context_T context) {
	binopnode_T* bn = (binopnode_T*)node;
	rtresult_T res = rtresult_create();
	number_T left = rtresult_register(&res,visit(bn->left, context));
	if(res.error){return res;}
	number_T right = rtresult_register(&res,visit(bn->right, context));
	if(res.error){return res;}
	rtresult_T result;
	switch (bn->op_tok->type) {
	case TT_PLUS: result = added_to(left, right); break;
	case TT_MINUS: result = subbed_by(left, right); break;
	case TT_MUL: result = multed_by(left, right); break;
	case TT_DIV: result = divided_by(left, right); break;
	case TT_POW: result = powed_by(left, right); break;
	default: printf("UNEXPECTED TOKEN\n"); break;
	}
	if(result.error){
		return rtresult_failure(res,result.error);
	}
	return rtresult_success(rtresult_create(),set_pos(result.number, node->pos_start, node->pos_end));
}

rtresult_T visit_UnaryOpNode(node_T* node, context_T context) { 
	unaryopnode_T* unop = (unaryopnode_T*)node;
	rtresult_T res = rtresult_create();
	number_T number = rtresult_register(&res,visit(unop->right, context));
	if(res.error){
		return res;
	}
	rtresult_T result = rtresult_create();
	if (unop->op_tok->type == TT_MINUS) {
		result = multed_by(number, number_create(1,-1,0));
	}
	if(result.error){
		return rtresult_failure(res, result.error);
	}
	return rtresult_success(rtresult_create(),set_pos(number, node->pos_start, node->pos_end));
}