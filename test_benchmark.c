#include <stdint.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "benchmark.h"
#include "asmheap.h"
#include "cheap.h"
#include "test_data.h"
#include "test_benchmark.h"


void test_benchmark_asmheap(void) {
    static uint8_t i, j;
    
    cputs("  Asm heap 100 * 128 push/pop:   ");
    asmheap_init();
    
    benchmark_init();
    benchmark_start();
    
    for (j = 0; j < 100; ++j) {
        for (i = 0; i < 128; ++i) {
            asmheap_push(test_data_random[i]);
        }
        for (i = 0; i < 128; ++i) {
            asmheap_pop();
        }
    }
    benchmark_stop();
    cprintf("%3d.%02d\r\n",
            benchmark_result() / 100,
            benchmark_result() % 100);
    
    benchmark_exit();
}

void test_benchmark_cheap(void) {
    static uint8_t i, j;
    
    cputs("  C heap 100 * 128 push/pop:     ");
    cheap_init();
    
    benchmark_init();
    benchmark_start();
    
    for (j = 0; j < 100; ++j) {
        for (i = 0; i < 128; ++i) {
            cheap_push(test_data_random[i]);
        }
        for (i = 0; i < 128; ++i) {
            cheap_pop();
        }
    }
    benchmark_stop();
    cprintf("%3d.%02d\r\n",
            benchmark_result() / 100,
            benchmark_result() % 100);
    
    benchmark_exit();
}


void test_benchmark(void) {
    cputs("Benchmarks:\r\n");
    test_benchmark_asmheap();
    test_benchmark_cheap();
    cputs("\r\n");
}
