	.include "macro.i"


	.export _asmheap_size
	.export _asmheap_init
	.export _asmheap_push
	.export _asmheap_pop
	.export _asmheap_tree

	.bss

	.align 128

tree:	.res 128	; Reserve 128 bytes for the tree, which allows
size:	.res 1		; us to use the N flag to check if it's full.

; Exported names.
_asmheap_tree = tree
_asmheap_size = size


	.code

; Initialize an empty heap.
_asmheap_init:
	lda #0
	sta size
	rts


; Swap node at x with node at y.
  .macro swap
	lda tree,x
	sta @temp
	lda tree,y
	sta tree,x
@temp = * + 1
	lda #$5e		; Self mod.
	sta tree,y
  .endmacro

; Push a value into the tree.
_asmheap_push:
	ldx size
	; If the heap is full, overwrite the last node.
	bpl :+
	dex
	stx size
:	; Push A to the bottom of the heap.
	sta tree,x
	inc size

	; Set Y to the parent node = (X - 1) / 2.
	txa
	sec
	sbc #1
	lsr
	tay
@heapify:
	; If X is at the top of the heap, we're done.
	cpx #0
	beq @done
	; If X is larger than its parent Y, we're done.
	lda tree,x
	cmp tree,y
	bcs @done
	; Swap X with its parent Y.
	swap
	; Set X to point at its parent.
	tya
	tax
	; Set Y to the new parent node.
	sec
	sbc #1
	lsr
	tay
	jmp @heapify
@done:
	rts


; Pop the lowest value from the tree.
_asmheap_pop:
	; Save the item at the top so we can return it.
	lda tree
	sta @return_value
	; Remove the item at the bottom of the tree.
	dec size
	beq @done
	ldy size
	lda tree,y
	; Move it to the top of the tree.
	sta tree
	; Heapify the tree.
	ldx #0
	stx @current_node
@heapify:
	; Left child is at x * 2 + 1.
	txa
	asl
	;clc		; X is always < 128
	adc #1
	tay
	; Check if we're at the bottom of the tree.
	cpy size
	bcs @done
	; Check if left child is smaller.
	lda tree,y
	cmp tree,x
	; If not skip to checking the right child.
	bcs @check_right
	; Since it was smaller let X point to the left child.
	tya
	tax
@check_right:
	; Right child is at x * 2 + 2, or left + 1.
	iny
	; Check if we're at the bottom of the tree.
	cpy size
	bcs @check_swap
	; Check if right child is smaller.
	lda tree,y
	cmp tree,x
	bcs @check_swap
	tya
	tax

@check_swap:
	; If either child was smaller X is different from the current node.
@current_node = * + 1
	cpx #$5e		; Self mod.
	; If not we're done.
	beq @done
	
	; Swap parent with child.
	ldy @current_node
	swap
	; Let the child be the new current node.
	stx @current_node
	; Repeat.
	jmp @heapify
@done:
	ldx #0
@return_value = * + 1
	lda #$5e		; Self mod.
	rts
