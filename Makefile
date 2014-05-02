TARGET=c64
CC=cl65
AS=ca65
LD=ld65
C1541=c1541
CFLAGS=-Oirs -t $(TARGET)
AFLAGS=-t $(TARGET)
LDFLAGS=
GCC=gcc
GCCFLAGS=-O


%.o: %.c
	$(CC) -c $(CFLAGS) $<

%.o: %.s
	$(AS) $(AFLAGS) $<


all: main.prg


OBJS = \
	main.o \
	test.o \
	benchmark.o \
	asmheap.o \
	cheap.o \
	test_asmheap.o \
	test_cheap.o \
	test_lockstep.o \
	test_benchmark.o \
	test_data.o


test_asmheap.o: test_asmheap.c test.h
test_cheap.o: test_cheap.c test.h
test_lockstep.o: test_lockstep.c test.h

asmheap.d64: asmheap.prg
	@-rm -f tmp.d64
	@c1541 -format 'asmheap,gp' d64 tmp.d64
	@c1541 tmp.d64 -write asmheap.prg 	   	'asmheap     /mv'
	@mv tmp.d64 $@

asmheap.prg: main.prg
	exomizer sfx sys -m 4096 -q -o $@ $^

main.prg: $(OBJS)
	$(CC) -m asmheap.map -C asmheap.cfg -o $@ $(LDFLAGS) $^


clean:
	rm -f *.o
	rm -f asmheap.prg main.prg asmheap.map
	rm -f asmheap.d64 tmp.d64


distclean: clean
	rm -f *~
