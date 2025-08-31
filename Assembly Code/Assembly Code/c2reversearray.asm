.model small
.stack 100h

.data
arr db 1,3,5,2,9,2,3,10

.code
main proc 
    mov ax,@data
    mov ds,ax
    lea si,arr
    lea di,arr+7
    reverse_loop:
        cmp si,di
        jge done
    
    boom:
        mov al,[si]
        mov bl,[di]
        mov [si],bl
        mov [di],al
        inc si
        dec di
        jmp reverse_loop
        
    done:
        
         xor si,si
         mov cx,8
        
    print:
        mov al,arr[si]
        mov ah,0
        call print_number
        inc si
        loop print
     
    mov ah,4ch
    int 21h

         
    
; --------------------------------------
; print_number
; AX = number (0 to 255)
; prints number as ASCII characters
; --------------------------------------
print_number proc
push ax
push bx
push cx
push dx

mov bx, 10 ; Divisor
mov cx,0

next_digit:
mov dx,0
div bx ; AX / 10 ? Ax=quotient, dx=remainder
push dx ; Save remainder (digit)
inc cx
cmp ax, 0
jne next_digit

print_digits:
pop dx ; Get digit from stack
add dl, '0' ; Convert to ASCII
mov ah, 2
int 21h
loop print_digits

pop dx
pop cx
pop bx
pop ax
ret
print_number endp    






