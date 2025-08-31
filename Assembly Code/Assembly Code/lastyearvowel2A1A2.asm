.model small
.stack 100h 
.data
  cc db 0
  vc db 0
.code

main proc
    mov ax,@data
    mov ds,ax
    
    iter: 
    mov ah,1
    int 21h
    cmp al,13
    je exit
    cmp al,'a'
    je vow
    cmp al,'e'
    je vow
    cmp al,'i'
    je vow
    cmp al,'o'
    je vow
    cmp al,'u'
    je vow
    jmp con
    
    vow:
    inc vc
    jmp iter
    
    con:
    inc cc
    jmp iter
    
    
    exit:
    mov bl,vc
    mov ax,bx
    call print_number
    mov cl,cc
    mov ch,0
    mov ax,cx
    call print_number
    mov ah,4ch
    int 21h
    main endp
print_number proc
push ax
push bx
push cx
push dx

mov bx, 10 ; Divisor
xor cx, cx ; Digit count

next_digit:
xor dx, dx
div bx ; AX / 10 ? AL=quotient, AH=remainder
push dx ; Save remainder (digit)
inc cx
cmp ax, 0
jne next_digit

print_digits:
pop dx ; Get digit from stack
add dl, '0' ; Convert to ASCII
mov ah, 02h
int 21h
loop print_digits

pop dx
pop cx
pop bx
pop ax
ret
print_number endp

end main
    
    