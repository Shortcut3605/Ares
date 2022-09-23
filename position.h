#ifndef POSITION_H
#define POSITION_H

typedef struct POSITION_STRUCT {
	int idx;
	int ln;
	int col;
	char* fn;
	char* ftxt;
} position_T;

position_T* position_create(int idx, int ln, int col, char* fn, char* ftxt);

void position_advance(position_T* position, char current_char);

position_T* position_copy(position_T* position);

#endif
