include 'EMU8086.INC'
.model small
.stack 100h
.data
    str db 'we are duet students $'
    
   .code
   
    main proc
        mov ax,@data
        mov ds,ax
        mov cx,10
        loop1: 
        
        printn 'we are duet students'
         
        ;mov dx,offset str
         
        ;mov ah,9
        ;int 21h
        
        mov ah,2
        mov dl,13
        int 21h
        
        mov ah,2
        mov dl,10
        int 21h
        
        loop loop1
    main endp
    end main
    
    