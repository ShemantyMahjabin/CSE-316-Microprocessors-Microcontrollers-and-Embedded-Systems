.model small
.stack 100h
.data
    arr db 'u','y','h','i','t','n','a','e'
    vowel db 'a','e','i','o','u'
    vcount db 0
    ccount db 0
    ;n db 8
.code
main proc
    mov ax,@data
    mov ds,ax
    
    lea si,arr
    lea di,vowel
    
    mov cx,5
    
    vc:
    mov bl,[si]
    check_vowel:
    cmp bl,[di]
    je isvowel
    inc di
    loop check_vowel
    inc ccount
    jmp next 
    
    isvowel:
        lea di,vowel
        inc vcount
        jmp next
        
    
    next:
        inc si
        mov bx,8
        cmp si,bx
        jge exit
        jmp vc
    exit:
        mov al,vcount
        mov bl,ccount
        mov ah,0
        mov bh,0
        ;add ax,'0'
        ;add bx,'0'
        
        ;mov ax,bx
        call print_number
        mov ax,bx
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