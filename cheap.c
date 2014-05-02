#include <stdint.h>
#include "cheap.h"


uint8_t cheap_size;
uint8_t cheap_tree[128];


void cheap_init(void) {
    cheap_size = 0;
}


#define SWAP(X, Y) \
    temp = cheap_tree[(X)]; \
    cheap_tree[(X)] = cheap_tree[(Y)]; \
    cheap_tree[(Y)] = temp;


#define heap_parent(i) ((uint8_t)(((i) - 1) / 2))

void cheap_push(uint8_t value) {
    static uint8_t currentIndex, newIndex, temp;
    
    currentIndex = cheap_size;
    cheap_tree[cheap_size++] = value;
    newIndex = heap_parent(currentIndex);
    while (currentIndex != 0 && cheap_tree[currentIndex] < cheap_tree[newIndex]) {
        SWAP(currentIndex, newIndex);
        currentIndex = newIndex;
        newIndex = heap_parent(currentIndex);
    }
}


#define heap_left_child(i) ((uint8_t)(((i) * 2) + 1))
#define heap_right_child(i) ((uint8_t)(((i) * 2) + 2))

uint8_t cheap_pop(void) {
    static uint8_t topValue, bottomValue, temp;
    static uint8_t currentIndex, newIndex, leftIndex, rightIndex;
    
    topValue = cheap_tree[0];
    bottomValue = cheap_tree[--cheap_size];
    cheap_tree[0] = bottomValue;
    currentIndex = 0;
    for (;;) {
        leftIndex = heap_left_child(currentIndex);
        rightIndex = heap_right_child(currentIndex);
        newIndex = currentIndex;
        if (leftIndex < cheap_size && cheap_tree[newIndex] > cheap_tree[leftIndex]) {
            newIndex = leftIndex;
        }
        if (rightIndex < cheap_size && cheap_tree[newIndex] > cheap_tree[rightIndex]) {
            newIndex = rightIndex;
        }
        if (newIndex == currentIndex) {
            return topValue;
        }
        SWAP(currentIndex, newIndex);
        currentIndex = newIndex;
    }
}
