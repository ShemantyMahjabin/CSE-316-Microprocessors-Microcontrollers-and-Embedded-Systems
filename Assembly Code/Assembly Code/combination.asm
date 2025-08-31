.model small
.stack 100h 


;int combination(int n, int r) {
;    if (r > n) return 0;
;    return factorial(n) / (factorial(r) * factorial(n - r));
;}

.code
main proc
    mov ax,7;n
    push ax
    mov ax,2;r
    push ax
    call combination
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
    
   combination proc near
        push bp
        mov bp,sp
        mov bx,[bp+6];bx=n
        mov cx,[bp+4];cx=r
        cmp cx,bx
        jg zero
        
        ;push ax
        mov ax,cx
        push ax
        call factorial;(fac(r) 
        push ax
        mov bx,[bp+6]
        sub bx,[bp+4]
        mov ax,bx
        push ax
        call factorial;fac(n-r)
     
        pop bx
        xchg bx,ax
        mov bh,0 
        mov ah,0
        
        mul bl
        push ax
        
        mov ax,[bp+6]
        push ax
        call factorial
        pop bx
        div bl
        jmp returna
        
        
        zero:
             mov ax,0
             jmp returna
        
        returna:
            pop bp
            ret 4
        
        
        
        combination endp 
    
    
    
   factorial proc near
        push bp
        mov bp,sp
        cmp word ptr[bp+4],1
        jg end_if
        mov ax,1
        jmp return
        
        end_if:
        mov cx,[bp+4]
        dec cx
        push cx
        call factorial
        mul word ptr[bp+4]
        return:
        pop bp
        ret 2
        
    end main
        