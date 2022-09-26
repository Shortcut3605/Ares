#include "interpreter.h"
#include "node.h"
#include "number.h"
#include "token.h"
#include "result.h"
#include "error.h"
#include "context.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

rtresult_T visit(node_T* node, context_T context) {
	switch (node->type) {
	case NT_NUMBER: return visit_NumberNode(node, context); break;
	case NT_BINOP: return visit_BinOpNode(node, context); break;
	case NT_UNARY: return visit_UnaryOpNode(node, context); break;
	case NT_VARACCESS: return visit_VarAccessNode(node, context); break;
	case NT_VARASSIGN: return visit_VarAssignNode(node, context); break;
	default: {printf("WTF\n"); exit(1);} break;
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
	if(matches(bn->op_tok, TT_KEYWORD, "and")){
		result = anded_by(left, right);
	}
	else if (matches(bn->op_tok, TT_KEYWORD, "or")) {
		result = ored_by(left, right);
	}
	else {
		switch (bn->op_tok->type) {
		case TT_PLUS: result = added_to(left, right); break;
		case TT_MINUS: result = subbed_by(left, right); break;
		case TT_MUL: result = multed_by(left, right); break;
		case TT_DIV: result = divided_by(left, right); break;
		case TT_POW: result = powed_by(left, right); break;
		case TT_EE: result = get_comparision_eq(left, right); break;
		case TT_NE: result = get_comparison_ne(left, right); break;
		case TT_LT: result = get_comparison_lt(left, right); break;
		case TT_GT: result = get_comparison_gt(left, right); break;
		case TT_LTE: result = get_comparison_lte(left, right); break;
		case TT_GTE: result = get_comparison_gte(left, right); break;
		default: printf("UNEXPECTED TOKEN\n"); break;
		}
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
	} else if(matches(unop->op_tok, TT_KEYWORD, "not")){
		result = notted(number);
	}
	if(result.error){
		return rtresult_failure(res, result.error);
	}
	return rtresult_success(rtresult_create(),set_pos(number, node->pos_start, node->pos_end));
}

rtresult_T visit_VarAccessNode(node_T* node, context_T context){
	rtresult_T res = rtresult_create();
	varaccessnode_T* va = (varaccessnode_T*)node;
	char* var_name = va->var_name_tok->value;
	value_T* value = symboltable_get(context.symboltable, var_name);
	int* type = symboltable_get_type(context.symboltable, var_name);
	if(value == NULL){
		string_T* output = string_create(4);
		string_push_string(output, var_name);
		string_push_string(output, " was not defined.");
		return rtresult_failure(res, RTError(output->string, node->pos_start, node->pos_end, context));
	}
	number_T out_value;
	switch(*type){
		case 1: out_value = set_pos(number_create(1, value->i, -1.0), node->pos_start, node->pos_end); break;
		case 2: out_value = set_pos(number_create(2, -1, value->f), node->pos_start, node->pos_end); break;
	}
	return rtresult_success(res, out_value);
}

rtresult_T visit_VarAssignNode(node_T* node, context_T context){
	rtresult_T res = rtresult_create();
	varassignnode_T* va = (varassignnode_T*)node;
	char* var_name = va->var_name_tok->value;
	number_T value = rtresult_register(&res, visit(va->value_node, context));
	if(res.error) { return res; }
	union VALUE_UNION v;
	v.f = value.value.f;
	v.i = value.value.i;
	symboltable_push(context.symboltable, var_name, v, value.type);
	return rtresult_success(res, value);
}