.model small
.stack 100h


   

.code
main proc
   
     mov ah,1 
     int 21h
     mov bl,al
     
     mov ah,1
     int 21h
     mov bh,al
     
     sub bl,bh
     
     add bl,48
     mov ah,2
     mov dl,bl
     int 21h
     
     mov ah,4ch
     int 21h
    
    
 main endp
 end main
 
    