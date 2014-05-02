#include <stdint.h>
#include <stdlib.h>
#include <c64.h>
#include <conio.h>
#include "test_cheap.h"
#include "test_asmheap.h"
#include "test_lockstep.h"
#include "test_benchmark.h"


void main(void) {
    VIC.addr = 0x17;
    VIC.bordercolor = 14;
    VIC.bgcolor0 = 6;
    clrscr();
    textcolor(1);
    
    cputs("Heap test suite\r\n\r\n");
    test_asmheap();
    test_cheap();
    test_lockstep();
    test_benchmark();
    cputs("All tests done");
}
