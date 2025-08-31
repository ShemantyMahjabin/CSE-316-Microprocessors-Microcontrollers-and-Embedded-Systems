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
    