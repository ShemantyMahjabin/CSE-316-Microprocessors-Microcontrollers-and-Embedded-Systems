.model small
.stack 100h

.data     
   
.code

main proc 
    mov cx,5
    mov ah,1
    int 21h
     
    mov bl,al
    
    cmp bl,97
    jge small_to_big
    
    
    add bl,33  
    big_to_small:
        mov ah,2
        mov dl,bl
        int 21h
        inc bl
        loop big_to_small
        jmp exit 
    
    small_to_big:
        sub bl,31
        big:
            mov ah,2
            mov dl,bl
            int 21h
            inc bl
            loop big
        
    
    exit:
        mov ah,4ch
        int 21h
    main endp
end main
     