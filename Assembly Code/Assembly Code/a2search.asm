.model small
.stack 100h

.data
arr db 9 dup(?)
size db ?
.code
main proc
    mov ax,@data
    mov ds,ax
    lea si,arr
    
    mov ah,1
    int 21h
    sub al, '0'
    mov ah,0
    mov cl,al
    mov ch,0
    mov bl,0
    
    input:
    mov ah,1
    int 21h
    sub al, '0'
    mov [si],al
    inc si
    inc bl
    cmp bl,cl
    jl input
    
    
    mov ah,1
    int 21h
    sub al, '0'
    mov bl,al
    
    lea di,arr
    mov dl,0
    
    search:
    cmp bl,[di]
    jne next
    mov ax,di
    jmp return
    
    next:
    inc di
    inc dl
    cmp dl,cl
    jl search
    jmp return
    
    return:
    cmp ax,cx
    jge l1
    add ax,'0'
    mov ah,0
    mov ah,2
    mov dx,ax
    int 21h
    jmp exit
    
    l1:
    mov ax,0
    add ax,'0'
    mov ah,2
    mov dx,ax
    int 21h
    
    exit:
    mov ah,4ch
    int 21h
    main endp
end main
    
     
    
    
    