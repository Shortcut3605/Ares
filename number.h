#ifndef NUMBER_H
#define NUMBER_H
#include "position.h"
#include "error.h"
#include "result_struct.h"
#include "number_struct.h"

number_T number_create(int type, int value, float value_f);

rtresult_T added_to(number_T current, number_T other);

rtresult_T subbed_by(number_T current, number_T other);

rtresult_T multed_by(number_T current, number_T other);

rtresult_T divided_by(number_T current, number_T other);

rtresult_T powed_by(number_T current, number_T other);

number_T set_pos(number_T number,position_T* start, position_T* end);

number_T set_context(number_T number, context_T context);

#endif
