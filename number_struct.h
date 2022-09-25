#ifndef NUMBER_STRUCT_H
#define NUMBER_STRUCT_H
#include "position.h"
#include "context.h"
typedef struct NUMBER_STRUCT {
	union{
		int i;
		float f;
	} value;
	int type;
	position_T* pos_start;
	position_T* pos_end;
	context_T context;
} number_T;
#endif