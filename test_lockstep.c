#include <stdint.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "test.h"
#define HEAP_DEBUG 1
#include "asmheap.h"
#include "cheap.h"
#include "test_data.h"
#include "test_lockstep.h"


/*
void print_tree(uint8_t *tree, uint8_t size) {
    static uint8_t i, c;
    static uint8_t items_per_line;
    
    items_per_line = 1;
    i = 0;
    while (i < size) {
        c = 0;
        while (c < items_per_line && i < size) {
            cprintf("%3d ", *tree++);
            ++i;
            ++c;
        }
        items_per_line *= 2;
        c = 0;
        cputs("\r\n");
    }
}
*/

void test_lockstep_random(void) {
    static uint8_t i;
    
    TESTBegin("Push/pop 128 elements");
    memset(asmheap_tree, 0, 128);
    memset(cheap_tree, 0, 128);
    
    asmheap_init();
    cheap_init();
    
    for (i = 0; i < 128; ++i) {
        cheap_push(test_data_random[i]);
        asmheap_push(test_data_random[i]);
        TESTAssertEqual(memcmp(asmheap_tree, cheap_tree, 128), 0);
    }
    for (i = 0; i < 8; ++i) {
        TESTAssertEqual(asmheap_pop(), cheap_pop());
        TESTAssertEqual(memcmp(asmheap_tree, cheap_tree, 128), 0);
    }
    
    TESTEnd();
}


void test_lockstep(void) {
    cputs("Lockstep test:\r\n");
    test_lockstep_random();
    cputs("\r\n");
}
