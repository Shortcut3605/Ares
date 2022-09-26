#ifndef CONTEXT_H
#define CONTEXT_H
#include "position.h"
#include "symboltable.h"
typedef struct CONTEXT_STRUCT {
    char* display_name;
    struct CONTEXT_STRUCT* parent;
    position_T* parent_entry_pos;
    int _null;
    symboltable_T* symboltable;
} context_T;

context_T context_create(char* display_name, context_T* parent, position_T* parent_entry_pos);
#endif