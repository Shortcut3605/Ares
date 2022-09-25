#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "node.h"
#include "number.h"
#include "result.h"
#include "context.h"

rtresult_T visit(node_T* node, context_T context);

rtresult_T visit_NumberNode(node_T* node, context_T context);

rtresult_T visit_BinOpNode(node_T* node, context_T context);

rtresult_T visit_UnaryOpNode(node_T* node, context_T context);

#endif