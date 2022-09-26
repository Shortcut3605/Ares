#include "number.h"
#include "result.h"
#include "math.h"
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
	number.context._null = 1;
	return number;
}

rtresult_T added_to(number_T current,number_T other) {
	rtresult_T res;
	res = rtresult_create();
	if (other.type == current.type) {
		res.number = set_context(number_create(other.type, (current.value.i + other.value.i), (current.value.f + other.value.f)), current.context);
		return res;
	}
	else {
		if (current.type == 2){
			other.value.f = (float)other.value.i;
			res.number = set_context(number_create(2, -1, (current.value.f + other.value.f)), current.context);
			return res;
		}
		current.value.f = (float)current.value.i;
		res.number = set_context(number_create(2, -1, (current.value.f + other.value.f)), current.context);
		return res;
	}
}

rtresult_T subbed_by(number_T current, number_T other) {
	rtresult_T res = rtresult_create();
	if (other.type == current.type) {
		res.number = set_context(number_create(other.type, (current.value.i - other.value.i), (current.value.f - other.value.f)), current.context);
		return res;
	}
	else {
		if (current.type == 2) {
			other.value.f = (float)other.value.i;
			res.number = set_context(number_create(2, -1, (current.value.f - other.value.f)), current.context);
			return res;
		}
		
		current.value.f = (float)current.value.i;
		res.number = set_context(number_create(2, -1, (current.value.f - other.value.f)), current.context);
		return res;
	}
}

rtresult_T multed_by(number_T current, number_T other) {
	rtresult_T res =  rtresult_create();
	if (other.type == current.type) {
		res.number = set_context(number_create(other.type, (current.value.i * other.value.i), (current.value.f * other.value.f)), current.context);
		return res;
	}
	else {
		if (current.type == 2) {
			other.value.f = (float)other.value.i;
			res.number = set_context(number_create(2, -1, (current.value.f * other.value.f)), current.context);
			return res;
		}
		
		current.value.f = (float)current.value.i;
		res.number = set_context(number_create(2, -1, (current.value.f * other.value.f)), current.context);
		return res;
	}
}

rtresult_T divided_by(number_T current, number_T other) {
	rtresult_T res = rtresult_create();
	if(other.value.i == 0){
		
		res.error = RTError("Division by zero",other.pos_start, other.pos_end, current.context);
		res.number = number_create(1, 1, 1);
		return res;
	}
	if (other.type == current.type) {
		res.number = set_context(number_create(other.type, (current.value.i / other.value.i), (current.value.f / other.value.f)), current.context);
		return res;
	}
	else {
		if (current.type == 2) {
			other.value.f = (float)other.value.i;
			res.number = set_context(number_create(2, -1, (current.value.f / other.value.f)), current.context);
			return res;
		}
		
		current.value.f = (float)current.value.i;
		res.number = set_context(number_create(2, -1, (current.value.f / other.value.f)), current.context);
		return res;
	}
}

rtresult_T powed_by(number_T current, number_T other){
	rtresult_T res = rtresult_create();
	if(other.type == current.type){
		if(current.type == 1){
			res.number = set_context(number_create(current.type, (int)power((float)current.value.i, (float)other.value.i), -1.0),current.context);
			return res;
		}
		res.number = set_context(number_create(current.type, -1, power(current.value.f, other.value.f)),current.context);
		return res;
	}
	else{
		if(current.type == 2){
			other.value.f = (float)other.value.i;
			res.number = set_context(number_create(current.type, -1, power(current.value.f, other.value.f)),current.context);
			return res;
		}
		current.value.f = (float)current.value.i;
		res.number = set_context(number_create(current.type, -1, power(current.value.f, other.value.f)),current.context);
		return res;
	}
}

rtresult_T get_comparision_eq(number_T current, number_T other){
	rtresult_T res = rtresult_create();
	if(current.type == other.type){
	switch(current.type){
		case 1: res.number = set_context(number_create(1, (current.value.i == other.value.i), -1), current.context); return res; break;
		case 2: res.number = set_context(number_create(1, (current.value.f == other.value.f), -1), current.context); return res; break;
	}
	}
	else {
		switch(current.type){
			case 1: current.value.f = (float)current.value.i; res.number = set_context(number_create(1, (current.value.f == other.value.f), -1), current.context); return res; break;
			case 2: other.value.f = (float)other.value.i; res.number = set_context(number_create(1, (current.value.f == other.value.f), -1), current.context); return res; break;
		}
	}
	return res;
}

rtresult_T get_comparison_ne(number_T current, number_T other){
	rtresult_T res = rtresult_create();
	if(current.type == other.type){
	switch(current.type){
		case 1: res.number = set_context(number_create(1, (current.value.i != other.value.i), -1), current.context); return res; break;
		case 2: res.number = set_context(number_create(1, (current.value.f != other.value.f), -1), current.context); return res; break;
	}
	}
	else {
		switch(current.type){
			case 1: current.value.f = (float)current.value.i; res.number = set_context(number_create(1, (current.value.f != other.value.f), -1), current.context); return res; break;
			case 2: other.value.f = (float)other.value.i; res.number = set_context(number_create(1, (current.value.f != other.value.f), -1), current.context); return res; break;
		}
	}
	return res;
}

rtresult_T get_comparison_lt(number_T current, number_T other){
	rtresult_T res = rtresult_create();
	if(current.type == other.type){
	switch(current.type){
		case 1: res.number = set_context(number_create(1, (current.value.i < other.value.i), -1), current.context); return res; break;
		case 2: res.number = set_context(number_create(1, (current.value.f < other.value.f), -1), current.context); return res; break;
	}
	}
	else {
		switch(current.type){
			case 1: current.value.f = (float)current.value.i; res.number = set_context(number_create(1, (current.value.f < other.value.f), -1), current.context); return res; break;
			case 2: other.value.f = (float)other.value.i; res.number = set_context(number_create(1, (current.value.f < other.value.f), -1), current.context); return res; break;
		}
	}
	return res;
}

rtresult_T get_comparison_gt(number_T current, number_T other){
	rtresult_T res = rtresult_create();
	if(current.type == other.type){
	switch(current.type){
		case 1: res.number = set_context(number_create(1, (current.value.i > other.value.i), -1), current.context); return res; break;
		case 2: res.number = set_context(number_create(1, (current.value.f > other.value.f), -1), current.context); return res; break;
	}
	}
	else {
		switch(current.type){
			case 1: current.value.f = (float)current.value.i; res.number = set_context(number_create(1, (current.value.f > other.value.f), -1), current.context); return res; break;
			case 2: other.value.f = (float)other.value.i; res.number = set_context(number_create(1, (current.value.f > other.value.f), -1), current.context); return res; break;
		}
	}
	return res;
}

rtresult_T get_comparison_lte(number_T current, number_T other){
	rtresult_T res = rtresult_create();
	if(current.type == other.type){
	switch(current.type){
		case 1: res.number = set_context(number_create(1, (current.value.i <= other.value.i), -1), current.context); return res; break;
		case 2: res.number = set_context(number_create(1, (current.value.f <= other.value.f), -1), current.context); return res; break;
	}
	}
	else {
		switch(current.type){
			case 1: current.value.f = (float)current.value.i; res.number = set_context(number_create(1, (current.value.f <= other.value.f), -1), current.context); return res; break;
			case 2: other.value.f = (float)other.value.i; res.number = set_context(number_create(1, (current.value.f <= other.value.f), -1), current.context); return res; break;
		}
	}
	return res;
}

rtresult_T get_comparison_gte(number_T current, number_T other){
	rtresult_T res = rtresult_create();
	if(current.type == other.type){
	switch(current.type){
		case 1: res.number = set_context(number_create(1, (current.value.i >= other.value.i), -1), current.context); return res; break;
		case 2: res.number = set_context(number_create(1, (current.value.f >= other.value.f), -1), current.context); return res; break;
	}
	}
	else {
		switch(current.type){
			case 1: current.value.f = (float)current.value.i; res.number = set_context(number_create(1, (current.value.f >= other.value.f), -1), current.context); return res; break;
			case 2: other.value.f = (float)other.value.i; res.number = set_context(number_create(1, (current.value.f >= other.value.f), -1), current.context); return res; break;
		}
	}
	return res;
}

rtresult_T anded_by(number_T current, number_T other){

}

rtresult_T ored_by(number_T current, number_T other){

}

number_T set_pos(number_T number, position_T* start, position_T* end) {
	number.pos_start = start;
	number.pos_end = end;
	return number;
}

number_T set_context(number_T number, context_T context){
	number.context = context;
	return number;
}
