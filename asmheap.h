#ifndef ASMHEAP_H
#define ASMHEAP_H


extern uint8_t asmheap_size;
#ifdef HEAP_DEBUG
extern uint8_t asmheap_tree[];
#endif

void asmheap_init();
void __fastcall__ asmheap_push(uint8_t value);
uint8_t asmheap_pop(void);


#endif
