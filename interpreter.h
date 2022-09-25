#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "node.h"
#include "number.h"
#include "result.h"


position_T* get_startpos(node_T* node);

position_T* get_endpos(node_T* node);

rtresult_T visit(node_T* node);

rtresult_T visit_NumberNode(node_T* node);

rtresult_T visit_BinOpNode(node_T* node);

rtresult_T visit_UnaryOpNode(node_T* node);

#endif