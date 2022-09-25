#ifndef RESULT_H
#define RESULT_H

#include "error.h"

//RUNTIME RESULT
#include "result_struct.h"
#include "number_struct.h"

rtresult_T rtresult_create();


number_T rtresult_register(rtresult_T* current, rtresult_T res);

rtresult_T rtresult_success(rtresult_T current, number_T res);

rtresult_T rtresult_failure(rtresult_T current, error_T* res);

#endif