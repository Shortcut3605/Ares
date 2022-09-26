#include "symboltable.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
value_T* value_create(union VALUE_UNION value){
    value_T* values = malloc(sizeof(union VALUE_UNION));
    *values = value;
    return values;
}

int* type_create(int value){
    int* type = malloc(sizeof(int));
    *type = value;
    return type;
}

symboltable_T* symboltable_create(symboltable_T* parent){
    symboltable_T* symboltable = malloc(sizeof(struct SYMBOLTABLE_STRUCT));
    symboltable->keys = list_create(1);
    symboltable->values = list_create(1);
    symboltable->types = list_create(1);
    symboltable->parent = parent;
    return symboltable;
}

int* symboltable_exists(symboltable_T* symboltable, char* name){
    for(int i = 0; i < symboltable->keys->item_size; i++){
            char* item = (char*)symboltable->keys->data[i];
            if(strcmp(item, name)==0){
                return type_create(i);
            }
    }
    if(symboltable->parent != NULL){
        return symboltable_get(symboltable->parent, name);
    }
    return NULL;
}

void symboltable_push(symboltable_T* symboltable, char* name, value_T value, int type){
    int* val = symboltable_exists(symboltable, name);
    if(val != NULL){
        value_T* val_get = (value_T*)symboltable->values->data[*val];
        int* val_type = (int*)symboltable->types->data[*val];
        *val_type = type;
        *val_get = value;
    }
    list_push(symboltable->keys, (void*)name);
    list_push(symboltable->types, (void*)type_create(type));
    list_push(symboltable->values, (void*)value_create(value));
    
}

void symboltable_pop(symboltable_T* symboltable){
    
}

value_T* symboltable_get(symboltable_T* symboltable,char* name){
    for(int i = 0; i < symboltable->keys->item_size; i++){
        char* item = (char*)symboltable->keys->data[i];
        if(strcmp(item, name)==0){
            return (value_T*)symboltable->values->data[i];
        }
    }
    if(symboltable->parent != NULL){
        return symboltable_get(symboltable->parent, name);
    }
    return NULL;
}

int* symboltable_get_type(symboltable_T* symboltable,char* name){
    for(int i = 0; i < symboltable->keys->item_size; i++){
        char* item = (char*)symboltable->keys->data[i];
        if(strcmp(item, name)==0){
            return (int*)symboltable->types->data[i];
        }
    }
    if(symboltable->parent != NULL){
        return symboltable_get_type(symboltable->parent, name);
    }
    return NULL;
}