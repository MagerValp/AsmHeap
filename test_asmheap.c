#include <stdint.h>
#include <stdlib.h>
#include <conio.h>
#include "test.h"
#include "asmheap.h"
#include "test_data.h"
#include "test_asmheap.h"


void test_asmheap_push(void) {
    TESTBegin("Asm heap push");
    asmheap_init();
    TESTAssertEqual(asmheap_size, 0);
    asmheap_push(12);
    TESTAssertEqual(asmheap_size, 1);
    asmheap_push(23);
    TESTAssertEqual(asmheap_size, 2);
    asmheap_push(34);
    TESTAssertEqual(asmheap_size, 3);
    TESTEnd();
}

void test_asmheap_pop(void) {
    TESTBegin("Asm heap pop");
    asmheap_init();
    TESTAssertEqual(asmheap_size, 0);
    asmheap_push(12);
    asmheap_push(23);
    asmheap_push(34);
    TESTAssertEqual(asmheap_size, 3);
    TESTAssertEqual(asmheap_pop(), 12);
    TESTAssertEqual(asmheap_size, 2);
    TESTAssertEqual(asmheap_pop(), 23);
    TESTAssertEqual(asmheap_size, 1);
    TESTAssertEqual(asmheap_pop(), 34);
    TESTAssertEqual(asmheap_size, 0);
    TESTEnd();
}

void test_asmheap_sort(void) {
    uint8_t i;
    
    TESTBegin("Asm heap sort 128 elements");
    asmheap_init();
    for (i = 0; i < 128; ++i) {
        asmheap_push(test_data_random[i]);
    }
    for (i = 0; i < 128; ++i) {
        TESTAssertEqual(asmheap_pop(), test_data_sorted[i]);
    }
    TESTEnd();
}


void test_asmheap(void) {
    cputs("Asm heap tests:\r\n");
    test_asmheap_push();
    test_asmheap_pop();
    test_asmheap_sort();
    //test_asmheap_benchmark();
    cputs("\r\n");
}
