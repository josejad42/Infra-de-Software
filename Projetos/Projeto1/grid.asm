print_grind:
    mov si, sp
    mov cx, [si + 2]
    mov bl, 21

    cmp cx, 0
    je .seila

    .somar:
      add bl, 15
      sub cx, 1
      cmp cx, 0
      jne .somar
      




    .seila:
    

    mov cx, 20
    mov dx, 20
    

    .loop:
      mov ah, 0ch
      mov al, 15
      mov bh, 0
      int 10h

      add dx, 1
      cmp dx, bx
      je .parte2
      jmp .loop

      .parte2:
        add cx, 15
        mov dx, 20
        cmp cx, bx
        jae .loop3

        jmp .loop


    .loop3:
      mov cx, 20
      mov dx, 20
      jmp .loop2
      

    .loop2:
      mov ah, 0ch
      mov al, 15
      mov bh, 0
      int 10h

      add cx, 1
      cmp cx, bx
      je .parte3
      jmp .loop2

      .parte3:
        add dx, 15
        mov cx, 20
        cmp dx, bx
        jae .fim

        jmp .loop2

      .fim:
        ret
      
%macro print_grind 1



%endmacro

      
  

start:
    xor ax, ax
    mov ds, ax
    mov es, ax

    mov ah, 0
    mov al, 13h
    int 10h

    

    push 8
    call print_grind
    add sp, 2
    
    
    

   

jmp $
