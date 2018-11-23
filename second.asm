assume cs:code ds:data ss:stack

data segment

db "some"

data ends

stack segment

dw 0,0,0,0,0,0,0,0

stack ends

code segment
start:
	mov ax, data
	mov ds, ax
	mov ax, stack
	mov ss, ax
	
	mov dx, 0
	mov cx, 15
s0:
	push cx
	mov cx, 100h
	s1:
		mov bx,1
		push cx
		mov cx,4
		s2:
			mov di,0
			mov al,ds:[di]
			inc di
			loop s2
		pop cx
		add bx,16
	loop s1
	pop cx
	add dx, 1000h
	mov ds, dx
loop s0
	
mov ax, 4c00h
int 21h
code ends
end start