org 0x7c00
jmp 0x0000:_start
data:
    frase db 'como eh facil trocar a cor', 0

getchar:
    mov ah, 0x00
    int 16h
ret

putchar:
    mov ah, 0xe
    mov bh, 0
   
    int 10h

   

ret

endl:
    mov al, 0x0a
    call putchar
    mov al, 0x0d
    call putchar

ret
_start:
    mov si, frase
    xor ax, ax
    xor dx, dx

    mov ah, 0
    mov al, 12h
    int 10h

    .input:
    ;para inserir um numero menor que 10, eh necessario inserir o '0' na frente
        xor ax, ax
        xor dx, dx
        call getchar
        mov dh, al
        sub dh, 48
        call getchar
        mov dl, al
        sub dl, 48
        mov al, 10
        mul dh
        add al, dl
        mov bl, al
        jmp .loop

   

    .loop:
        lodsb
        call putchar
       
        cmp al, 0
        jne .loop
        mov si, frase
        call endl
        jmp .input
   
   

   



 

   
   


times 510 - ($ - $$) db 0
dw 0xaa55 ; assinatura de boot
