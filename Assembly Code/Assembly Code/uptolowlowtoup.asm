.model small
.stack 100h

.data     
   
.code

main proc 
    
    mov ah,1
    int 21h
     
    mov bl,al
    
    cmp bl,97
    jge small_to_big
    big_to_small:
    add bl,32
    
    mov ah,2
    mov dl,bl
    int 21h
    jmp exit 
    
    small_to_big:
    sub bl,32
    mov ah,2
    mov dl,bl
    int 21h
    
    
    exit:
    mov ah,4ch
    int 21h
    main endp
end main
     