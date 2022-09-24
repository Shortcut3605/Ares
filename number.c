#include "number.h"
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

number_T added_to(number_T current,number_T other) {
	if (other.type == current.type) {
		return number_create(other.type, (current.value.i + other.value.i), (current.value.f + other.value.f));
	}
	else {
		if (current.type == 2){
			other.value.f = (float)other.value.i;
			return number_create(2, -1, (current.value.f + other.value.f));
		}
		current.value.f = (float)current.value.i;
		return number_create(2, -1, (current.value.f + other.value.f));
	}
}

number_T subbed_by(number_T current, number_T other) {
	if (other.type == current.type) {
		return number_create(other.type, (current.value.i - other.value.i), (current.value.f - other.value.f));
	}
	else {
		if (current.type == 2) {
			other.value.f = (float)other.value.i;
			return number_create(2, -1, (current.value.f - other.value.f));
		}
		
		current.value.f = (float)current.value.i;
		return number_create(2, -1, (current.value.f - other.value.f));
	}
}

number_T multed_by(number_T current, number_T other) {
	if (other.type == current.type) {
		return number_create(other.type, (current.value.i * other.value.i), (current.value.f * other.value.f));
	}
	else {
		if (current.type == 2) {
			other.value.f = (float)other.value.i;
			return number_create(2, -1, (current.value.f * other.value.f));
		}
		
		current.value.f = (float)current.value.i;
		return number_create(2, -1, (current.value.f * other.value.f));
	}
}

number_T divided_by(number_T current, number_T other) {
	if (other.type == current.type) {
		return number_create(other.type, (current.value.i / other.value.i), (current.value.f / other.value.f));
	}
	else {
		if (current.type == 2) {
			other.value.f = (float)other.value.i;
			return number_create(2, -1, (current.value.f / other.value.f));
		}
		
		current.value.f = (float)current.value.i;
		return number_create(2, -1, (current.value.f / other.value.f));
	}
}

number_T set_pos(number_T number, position_T* start, position_T* end) {
	number.pos_start = start;
	number.pos_end = end;
	return number;
}
