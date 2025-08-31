.model small
.stack 100h
.data
str db ' stUDeNTs ','$'

.code 
    main proc
        mov ax,@data
        mov ds,ax
               
        mov si,offset str
        mov ah,9
        int 21h
               
        mov ah,2
        mov dl,13
        int 21h
        mov ah,2
        mov dl,10
        int 21h
        
        cmp [si],'$'
        je exit
        
        cmp [si],97
        jge small
        
        jmp first_big
         
        small:
            inc si
            cmp [si],'$'
            je exit
            cmp [si],97
            jge small
            jmp first_big     
            
        
        
        first_big:
                cmp [si],32
                je small
                  mov dl,[si]
                  mov ah,2
                  int 21h
                  jmp last_big
        
        
        last_big:
            inc si
            cmp [si],'$'
            je exit
            cmp [si],97
            jge last_big
            cmp [si],32
            je last_big
            mov bl,[si]
            jmp last_big
        
        
            
        exit:
        mov dl,bl
        mov ah,2
        int 21h
        mov ah,4ch
        int 21h
        