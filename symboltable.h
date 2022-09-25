#ifndef SYMBOLTABLE_H
#define SYMBOLTALE_H
#include "list.h"
typedef struct SYMBOLTABLE_STRUCT{
    list_T* keys;
    list_T* values;
} symboltable_T;

#endif