.model small
.stack 100h 
.code
main proc 
    mov ax,4
    push ax
    
    call func1 
    
    
    
    mov ah,4ch
    int 21h
    main endp

    
    
    
    
    func1 proc near
        push bp
        mov bp,sp
        mov bx,word ptr[bp+4] 
        
        cmp bx,1
        jle then
        jmp else
        
        then:
        mov ax,5
        jmp return
        
        else:
        sub bx,1
        push bx
        call func1 
        add ax,2
        
        
        return:
        pop bp
        ret 2
        
    end main
    
        
        