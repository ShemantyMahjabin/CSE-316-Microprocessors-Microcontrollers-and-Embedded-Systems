.model small
.stack 100h

.code
main proc 
    mov ax,48 ;a
    push ax
    mov ax,18 ;b
    push ax
    call gcd
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
 
 gcd proc near
    push bp
    mov bp,sp
    mov cx,word ptr[bp+4] ;b
    mov dx,word ptr[bp+6] ;a
    cmp cx,0
    je base
    xchg cx,dx;cx=a,dx=b
    mov bx,dx ;bx=b
    push dx
    xor ax,ax
    mov ax,cx ;ax divedend
    div bl   ;divisor bx
    mov al,ah
    mov ah,0
    push ax 

    ;push dx
    ;push ax
    call gcd
    jmp return
    
    base:
    mov ax,[bp+6]
    jmp return
    
    return:
    pop bp
    ret 4
    gcd endp
    end main
       