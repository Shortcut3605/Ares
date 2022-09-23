#include "position.h"
#include <stdlib.h>

position_T* position_create(int idx, int ln, int col, char* fn, char* ftxt) {
	position_T* position = malloc(sizeof(struct POSITION_STRUCT));
	position->idx = idx;
	position->ln = ln;
	position->col = col;
	position->fn = fn;
	position->ftxt = ftxt;
	return position;
}

void position_advance(position_T* position, char current_char) {
	position->idx++;
	position->col++;
	if (current_char == '\n') {
		position->ln++;
		position->col = 0;
	}
}

position_T* position_copy(position_T* position) {
	//if (position == NULL) { return NULL; }
	return position_create(position->idx, position->ln, position->col, position->fn, position->ftxt);
}
