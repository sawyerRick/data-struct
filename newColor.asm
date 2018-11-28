assume cs:code ds:data ss:stack

stack segment

	dd 0,0,0,0

stack ends

data segment
	db "FUUUUUUUUUUUUUUK"
data ends

code segment

start:
	mov ax,0b800h
	mov ds,ax
	mov ax,data
	mov es,ax
	
	mov ax,stack
	mov ss,ax
	mov sp,10h
	
	mov si,0
	mov di,0
	mov bx,0
	
	mov cx,80
s1:
	push cx
	mov cx,16
	s0:
		mov bl,es:[si]
		mov ds:[bx+di],bl
		mov byte ptr ds:[bx+di+1],42h
		inc si
		add di, 2
		loop s0
	add bx,160
	pop cx
	loop s1

mov ax,4c00h

code ends
end start