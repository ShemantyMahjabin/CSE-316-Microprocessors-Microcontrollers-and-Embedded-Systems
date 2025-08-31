.model small
.stack 100h
.code
main proc
    mov ax,2 ;k=2
    push ax
    mov ax,3 ;n=3
    push ax
    call binomial
    call print_number
    mov ah,4ch
    int 21h
    
    main endp

binomial proc near
    push bp
    mov bp,sp
    mov bx,[bp+6];bx=k
    cmp bx,[bp+4]
    je one
    cmp bx,0
    jne else
    one:
        mov ax,1
        jmp return 
    
    else:
        push [bp+6]
        mov cx,[bp+4];cx=n
        dec cx
        push cx
        call binomial
        push ax
        mov bx,[bp+6] ;bx=k
        dec bx
        push bx 
        mov cx,[bp+4]
        dec cx
        ;push bx
        push cx
        call binomial
        pop bx
        add ax,bx
        
    return:
        pop bp
        ret 4
        binomial endp



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
        