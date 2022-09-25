#include "number.h"
#include "result.h"
#include <stdio.h>

number_T number_create(int type, int value, float value_f){
	number_T number;
	number.type = type;
	switch (type) {
	case 1: number.value.i = value; break;
	case 2: number.value.f = value_f; break;
	}
	number.pos_start = NULL;
	number.pos_end = NULL;
	return number;
}

rtresult_T added_to(number_T current,number_T other) {
	rtresult_T res;
	res = rtresult_create();
	if (other.type == current.type) {
		res.number = number_create(other.type, (current.value.i + other.value.i), (current.value.f + other.value.f));
		return res;
	}
	else {
		if (current.type == 2){
			other.value.f = (float)other.value.i;
			res.number = number_create(2, -1, (current.value.f + other.value.f));
			return res;
		}
		current.value.f = (float)current.value.i;
		res.number = number_create(2, -1, (current.value.f + other.value.f));
		return res;
	}
}

rtresult_T subbed_by(number_T current, number_T other) {
	rtresult_T res = rtresult_create();
	if (other.type == current.type) {
		res.number = number_create(other.type, (current.value.i - other.value.i), (current.value.f - other.value.f));
		return res;
	}
	else {
		if (current.type == 2) {
			other.value.f = (float)other.value.i;
			res.number = number_create(2, -1, (current.value.f - other.value.f));
			return res;
		}
		
		current.value.f = (float)current.value.i;
		res.number = number_create(2, -1, (current.value.f - other.value.f));
		return res;
	}
}

rtresult_T multed_by(number_T current, number_T other) {
	rtresult_T res =  rtresult_create();
	if (other.type == current.type) {
		res.number = number_create(other.type, (current.value.i * other.value.i), (current.value.f * other.value.f));
		return res;
	}
	else {
		if (current.type == 2) {
			other.value.f = (float)other.value.i;
			res.number = number_create(2, -1, (current.value.f * other.value.f));
			return res;
		}
		
		current.value.f = (float)current.value.i;
		res.number = number_create(2, -1, (current.value.f * other.value.f));
		return res;
	}
}

rtresult_T divided_by(number_T current, number_T other) {
	rtresult_T res = rtresult_create();
	if(other.value.i == 0){
		res.error = RTError("Division by zero",other.pos_start, other.pos_end);
		res.number = number_create(1, 1, 1);
		return res;
	}
	if (other.type == current.type) {
		res.number = number_create(other.type, (current.value.i / other.value.i), (current.value.f / other.value.f));
		return res;
	}
	else {
		if (current.type == 2) {
			other.value.f = (float)other.value.i;
			res.number = number_create(2, -1, (current.value.f / other.value.f));
			return res;
		}
		
		current.value.f = (float)current.value.i;
		res.number = number_create(2, -1, (current.value.f / other.value.f));
		return res;
	}
}

number_T set_pos(number_T number, position_T* start, position_T* end) {
	number.pos_start = start;
	number.pos_end = end;
	return number;
}
