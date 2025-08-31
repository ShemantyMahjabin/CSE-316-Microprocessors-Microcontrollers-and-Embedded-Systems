.model small
.stack 100h
.code
main proc
    mov ax,3
    push ax
    call factorial
    
    mov ah,4ch
    int 21h
    main endp
    
    
    
    
    
   factorial proc near
        push bp
        mov bp,sp
        cmp word ptr[bp+4],1
        jg end_if
        mov ax,1
        jmp return
        
        end_if:
        mov cx,[bp+4]
        dec cx
        push cx
        call factorial
        mul word ptr[bp+4]
        return:
        pop bp
        ret 2
    end main
        