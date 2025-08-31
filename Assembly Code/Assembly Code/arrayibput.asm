 .model small
 .stack 100h
  
  .data
        arr db ?
  .code
         main proc
            mov ax,@data
            mov ds,ax
            mov si,offset arr 
            
            mov cx,5
            
            input:
            mov ah,1
            int 21h
            mov [si],al
            inc si
            loop input
            mov [si] ,'$' 
            ;mov ah,2
            ;mov dl,arr[2]
            ;int 21h
            
            mov si,offset arr
            mov cx,5
             
            output:
                
               mov ah,2
               mov dl,[si]
               int 21h
               inc si
               loop output
               
            
           main endp
         end main
  