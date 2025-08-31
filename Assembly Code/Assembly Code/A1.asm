.model small
.stack 100h
.data
    i db 0
    j db ?
    k db 0
    n db ?
    
;for(i=0;i<n;i++){
;  for(j=n;j>i;j--)
;   {print#}
;  for(k=0;k<=i;k++)
;   {print k+1}
;}    
    



.code
main proc
    mov ax,@data
    mov ds,ax
    
     
    mov ah,1
    int 21h
    sub al, '0'
    mov n,al
    
    mov ah,2
    mov dl,13
    int 21h
    mov dl,10
    int 21h
    
    mov i,0
            
            
    i_loop:
         mov al,i
            
         cmp al,n
         jge exit
    
    
    L1:
        ;mov j,al
        mov al,n
        sub al,i
        mov cl,al
        
        L2:
            cmp cl,0
            je L3
            mov dl,'#'
            mov ah,2
            int 21h
            
            dec cl
            jmp L2
            
            
        L3: 
            mov k,0
            
            L4:
                mov al,k
                cmp al,i
                jg next
                inc al
                add al,'0'
                mov dl,al
                mov ah,2
                int 21h
            
                inc k
                jmp L4  
             
     next:
        mov ah,2
        mov dl,13
        int 21h
        mov dl,10
        int 21h
        inc i
        loop i_loop
        
     exit:
        mov ah,4ch
        int 21h
    
    main endp
end main