.model small
.stack 100h  

.data
array db 10,20,20,30,40,50,60,70,76,80,80,100,110,120,120,120,130 
length dw 17 

ascending_msg db 'Ascending$'
descending_msg db 'Descending$'
not_sorted_msg db 'Not sorted$'
  
  
 .code
 main:
 
    mov ax,@data
    mov ds,ax
    
    mov bl,1
    mov bh,1
    mov si,0  
    
    check_loop:
        mov al,array[si]
        mov ah,array[si+1]
        
        cmp al,ah
        jl not_descending
        jg not_ascending
        
    next_element:   
        inc si
        mov cx,length
        sub cx,2
        cmp si,cx
        jl check_loop
    
        
    
        cmp bl,1
        jne check_descending
        lea dx, ascending_msg
        jmp print_message
    
    
    check_descending:
        cmp bh,1
        jne not_sorted
        lea dx,descending_msg
        jmp print_message
        
    not_sorted:
        lea dx,not_sorted_msg
        
        
    print_message:
        mov ah,9
        int 21h
        jmp program_end
        
                     
                   
    
    program_end:
        mov ah,4ch
        int 21h 
    
    not_descending:
        mov bh,0
        jmp next_element
        
    not_ascending:
        mov bl,0
        jmp next_element
    
end main
   