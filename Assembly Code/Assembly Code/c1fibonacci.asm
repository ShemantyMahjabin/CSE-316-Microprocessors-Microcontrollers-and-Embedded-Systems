.model small
.stack 100h 
.data
.code

main proc
    mov ax,@data
    mov ds,ax 
    mov ah,1
    int 21h
    sub al, '0'  ; Convert ASCII to integer
    mov ah, 0
    push ax
    call fibonacci
    
    mov bx,ax
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
    
    
    
    
   fibonacci proc near
    
    
        push bp
        mov bp,sp
        mov bx,word ptr[bp+4]
        cmp bx,0
        je zero
        cmp bx,1
        jg else
        mov ax,1
        jmp return
        
        else:
        mov bx,word ptr[bp+4]
        dec bx
        push bx
        call fibonacci
        push ax
        mov cx,word ptr[bp+4]
        dec cx
        dec cx
        push cx
        call fibonacci
        pop bx
        add ax,bx
        jmp return 
        
        zero:
        mov ax,0
        jmp return
                      
    return:
        pop bp
        ret 2
 end main 
    
    
    
    
    