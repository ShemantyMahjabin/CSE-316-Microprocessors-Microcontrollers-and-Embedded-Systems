.model small
.stack 100h
.data
    arr db  1,3,10,12,4,6,2,9,7,11
    max1 db 0
    max2 db 0
    
    
.code

    main proc
        mov ax,@data
        mov ds,ax 
        lea si,arr
        
        mov cx,10
        
        i_loop:
            mov al,[si]
            mov bl,max1
            cmp bl,al
            jg L2
        updatemax1:
            mov max2,bl 
            mov max1,al
            jmp next
            
         L2: 
            mov bl,max2
            cmp bl,al
            jl cngmax2 ;max2<[si] 
            jmp next
            
         cngmax2:
            mov bl,al
            mov max2,bl
            jmp next
             
         next:
            inc si
            loop i_loop
            
         exit:
            
            mov ax,0
            mov al,max2
            mov ah,0
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
        
        
        
     