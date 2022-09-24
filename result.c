#include "result.h"
#include "number.h"
#include <stdio.h>
rtresult_T rtresult_create(){
    rtresult_T res;
    res.error = NULL;
    res.number.type = -1;
    return res;
}

number_T rtresult_register( rtresult_T current, rtresult_T res){
    if(res.error != NULL){
        current.error = res.error;
    }
    return res.number; 
}

rtresult_T rtresult_success(rtresult_T current, number_T res){
    current.number = res;
    return current;
}

rtresult_T rtresult_failure(rtresult_T current, error_T* res){
    current.error = res;
    return current;
}