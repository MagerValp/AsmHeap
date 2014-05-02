#include <stdint.h>
#include <stdlib.h>
#include <conio.h>
#include "test.h"
#include "cheap.h"
#include "test_data.h"
#include "test_cheap.h"


void test_cheap_push(void) {
    TESTBegin("C heap push");
    cheap_init();
    TESTAssertEqual(cheap_size, 0);
    cheap_push(12);
    TESTAssertEqual(cheap_size, 1);
    cheap_push(23);
    TESTAssertEqual(cheap_size, 2);
    cheap_push(34);
    TESTAssertEqual(cheap_size, 3);
    TESTEnd();
}

void test_cheap_pop(void) {
    TESTBegin("C heap pop");
    cheap_init();
    TESTAssertEqual(cheap_size, 0);
    cheap_push(12);
    cheap_push(23);
    cheap_push(34);
    TESTAssertEqual(cheap_size, 3);
    TESTAssertEqual(cheap_pop(), 12);
    TESTAssertEqual(cheap_size, 2);
    TESTAssertEqual(cheap_pop(), 23);
    TESTAssertEqual(cheap_size, 1);
    TESTAssertEqual(cheap_pop(), 34);
    TESTAssertEqual(cheap_size, 0);
    TESTEnd();
}

void test_cheap_sort(void) {
    uint8_t i;
    
    TESTBegin("C heap sort 128 elements");
    cheap_init();
    for (i = 0; i < 128; ++i) {
        cheap_push(test_data_random[i]);
    }
    for (i = 0; i < 128; ++i) {
        TESTAssertEqual(cheap_pop(), test_data_sorted[i]);
    }
    TESTEnd();
}


void test_cheap(void) {
    cputs("C heap tests:\r\n");
    test_cheap_push();
    test_cheap_pop();
    test_cheap_sort();
    //test_cheap_benchmark();
    cputs("\r\n");
}
