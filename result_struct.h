#ifndef RESULT_STRUCT
#define RESULT_STRUCT
#include "number_struct.h"
#include "error.h"
typedef struct RTRESULT_STRUCT {
    number_T number;
    error_T* error;
} rtresult_T;
#endif