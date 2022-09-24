#ifndef RESULT_H
#define RESULT_H
#include "number.h"
#include "error.h"
//RUNTIME RESULT
typedef struct RTRESULT_STRUCT {
    number_T number;
    error_T* error;
} rtresult_T;

rtresult_T rtresult_create();

number_T rtresult_register(rtresult_T current, rtresult_T res);

rtresult_T rtresult_success(rtresult_T current, number_T res);

rtresult_T rtresult_failure(rtresult_T current, error_T* res);

#endif