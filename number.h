#ifndef NUMBER_H
#define NUMBER_H
#include "position.h"
typedef struct NUMBER_STRUCT {
	union{
		int i;
		float f;
	} value;
	int type;
	position_T* pos_start;
	position_T* pos_end;
} number_T;

number_T number_create(int type, int value, float value_f);

number_T added_to(number_T current, number_T other);

number_T subbed_by(number_T current, number_T other);

number_T multed_by(number_T current, number_T other);

number_T divided_by(number_T current, number_T other);

number_T set_pos(number_T number,position_T* start, position_T* end);

#endif
