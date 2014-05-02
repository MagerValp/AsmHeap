#ifndef TEST_H
#define TEST_H


#include <stdint.h>
#include <conio.h>


extern uint16_t test_err_cnt;


#define TESTBegin(name) do { \
        gotox(0); \
        textcolor(1); \
        cprintf("  %-32s [ ]", name); \
        test_err_cnt = 0; \
    } while (0);
#define TESTEnd() do { \
        gotox(36); \
        if (test_err_cnt) { \
            textcolor(10); \
            cputs("x\r\n"); \
        } else { \
            textcolor(13); \
            cprintf("%c\r\n", 0xba); \
        } \
        textcolor(1); \
    } while (0);
#define TESTAssertTrue(expr) if (!(expr)) { ++test_err_cnt; }
#define TESTAssertEqual(a, b) if ((a) != (b)) { ++test_err_cnt; }

#endif
