#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "list.h"


typedef union VALUE_UNION{
    int i;
    float f;
} value_T;
typedef struct SYMBOLTABLE_STRUCT{
    list_T* keys;
    list_T* values;
    list_T* types;
    struct SYMBOLTABLE_STRUCT* parent;
} symboltable_T;

value_T* value_create(union VALUE_UNION value);

int* type_create(int value);

symboltable_T* symboltable_create(symboltable_T* parent);

void symboltable_push(symboltable_T* symboltable, char* name, value_T value, int type);

void symboltable_pop(symboltable_T* symboltable);

value_T* symboltable_get(symboltable_T* symboltable,char* name);

int* symboltable_get_type(symboltable_T* symboltable,char* name);

#endif