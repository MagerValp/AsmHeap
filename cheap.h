#ifndef CHEAP_H
#define CHEAP_H


extern uint8_t cheap_size;
#ifdef HEAP_DEBUG
extern uint8_t cheap_tree[];
#endif

void cheap_init();
void cheap_push(uint8_t value);
uint8_t cheap_pop(void);


#endif
