#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#define func(x) x

#include "dequef.h"

typedef int (*func_type)(void);

/*
    To test df_set you must edit errno with some non-zero value when your function is expected to report
    a failure and then return any valid value.

    REQUIRED: df_get correctly implemented
*/

float fabs(float x) {
    if(x < 0) return -x;
    return x;
}

int compare_floats(float a, float b) {
    return fabs(a - b) < 1e-9;
}

int teste_1() {
    // get with first = 0
    float cur_data[8] = {1.0, 2.0, 3.0, 5.0, 8.0, 13.0, 21.0, 34.0};
    float after_data[8] = {1.0, 2.0, 3.0, 12.0, 8.0, 13.0, 21.0, 34.0};
    dequef *res = df_alloc(8, 2.0);
    for(int i = 0; i < 8; i++) res -> data[i] = cur_data[i];
    res -> first = 0;
    res -> size = 8;
    errno = 0;
    df_set(res, -1, 12.0);
    if(!errno) {
        return 0;
    }
    errno = 0;
    df_set(res, 8, 12.0);
    if(!errno) {
        return 0;
    }
    errno = 0;
    df_set(res, 3, 12.0);
    if(errno) {
        return 0;
    }
    if(res -> first != 0) return 0;
    if(res -> size != 8) return 0;
    if(res -> cap != 8) return 0;
    if(res -> mincap != 8) return 0;
    if(!compare_floats(res -> factor, 2.0)) return 0;
    for(int i = 0; i < 8; i++) {
        if(!compare_floats(after_data[i], df_get(res, i))) return 0;
    }
    return 1;
}

int teste_2() {
    // Simple insert with first in the middle
    float cur_data[8] = {1.0, 2.0, 3.0, 5.0, 8.0, 13.0, 21.0, 34.0};
    float after_data[8] = {1.0, 2.0, 3.0, 12.0, 8.0, 13.0, 21.0, 34.0};
    dequef *res = df_alloc(8, 2.0);
    for(int i = 0; i + 2 < 8; i++) res -> data[i + 2] = cur_data[i];
    for(int i = 6; i < 8; i++) res -> data[i - 6] = cur_data[i];
    res -> first = 2;
    res -> size = 8;
    errno = 0;
    df_set(res, -1, 12.0);
    if(!errno) {
        return 0;
    }
    errno = 0;
    df_set(res, 8, 12.0);
    if(!errno) {
        return 0;
    }
    errno = 0;
    df_set(res, 3, 12.0);
    if(errno) {
        return 0;
    }
    if(res -> first != 2) return 0;
    if(res -> size != 8) return 0;
    if(res -> cap != 8) return 0;
    if(res -> mincap != 8) return 0;
    if(!compare_floats(res -> factor, 2.0)) return 0;
    for(int i = 0; i < 8; i++) {
        if(!compare_floats(after_data[i], df_get(res, i))) return 0;
    }
    return 1;
}

int main() {
    func_type func[2] = {&teste_1, &teste_2};
    int NO_TESTS = 2;
    for(int i = 0; i < NO_TESTS; i++) {
        if(!func[i]()) printf("Test %d - FAILED\n", i + 1);
        else printf("Test %d - Passed\n", i + 1);
    }
    return 0;
}