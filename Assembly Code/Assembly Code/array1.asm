.model small
.stack 100h

.data
    ;arr db 1,2,3,4,5
    ;array db 'A','A','A'
    ;str db 'AAA'
    ;arr db 3 dup<'A'>
    arr db 30 dup<?> 
    
    
    
    
.code   
    main proc
        mov ax,@data
        mov ds,ax
        ;mov dl,arr[2]
        ;add dl,48
        ;mov ah,2
        ;int 21h  
        
        mov si,offset arr
        mov dl,[si]
        ;add dl,48
        ;mov ah,2
        ;int 21h 
        
        mov arr[3],50
        mov dl,arr[3]
        mov ah,2
        int 21h
               
        mov si[4] ,52
        mov dl,si[4]
        mov ah,2
        int 21h
    main endp
end main

