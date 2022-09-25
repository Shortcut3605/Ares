#include "context.h"

context_T context_create(char* display_name, context_T parent, position_T* parent_entry_pos){
    context_T context;
    context.display_name = display_name;
    context.parent = &parent;
    context.parent_entry_pos = parent_entry_pos;
    context._null = 0;
    return context;
}