#include "number.h"
#include <stdio.h>

number_T number_create(int type, int value, float value_f){
	number_T number;
	number.type = type;
	switch (type) {
	case 1: number.i = value; break;
	case 2: number.f = value_f; break;
	}
	number.pos_start = NULL;
	number.pos_end = NULL;
	return number;
}

number_T added_to(number_T current,number_T other) {
	if (other.type == current.type) {
		return number_create(other.type, (current.i + other.i), (current.f + other.f));
	}
}

number_T subbed_by(number_T current, number_T other) {
	if (other.type == current.type) {
		return number_create(other.type, (current.i - other.i), (current.f - other.f));
	}
}

number_T multed_by(number_T current, number_T other) {
	if (other.type == current.type) {
		return number_create(other.type, (current.i * other.i), (current.f * other.f));
	}
}

number_T divided_by(number_T current, number_T other) {
	if (other.type == current.type) {
		return number_create(other.type, (current.i / other.i), (current.f / other.f));
	}
}

number_T set_pos(number_T number, position_T* start, position_T* end) {
	number.pos_start = start;
	number.pos_end = end;
	return number;
}
