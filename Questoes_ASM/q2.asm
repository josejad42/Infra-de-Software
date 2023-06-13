org 0x7c00
jmp 0x0000:start

string: times 9 db 0
start:
    mov di, string
    call gets
    call getchar
    mov bl, al
    call putchar
    call endl
    call printTam
    jmp $

putchar:    
    mov ah, 0x0e
    int 10h
    ret

getchar:
    mov ah, 0x00
    int 16h
    ret

endl:
    mov al, 0x0a
    call putchar
    mov al, 0x0d
    call putchar
    ret

delchar:
    mov al, 0x08
    call putchar

    mov al, ''
    call putchar

    mov al, 0x08
    call putchar

    ret

gets:
    xor cx, cx
    mov di, cx

    .loop:
        call getchar
        cmp al, 0x08
        je .backspace
        cmp al, 0x0d
        je .done
        cmp cl, 50
        je .loop
        stosb
        inc cl
        call putchar
        jmp .loop
        
        .backspace:
            cmp cl, 0
            je .loop
            dec di
            dec cl
            mov byte[di], 0
            call delchar
            jmp .loop

        .done:
            mov al, 0
            stosb
            mov al, 0x0a
            call putchar
            mov al, 0x0d
            call putchar

            ret 

printOcorr:


printTam:
    xor dl, dl
    xor cl, cl

    .loop:
        lodsb

        cmp al, 0
        je .endloop

        cmp al, bl
        je .incr
        
        inc dl

        jmp .loop

    .incr:
        inc cl
        inc dl 
        jmp .loop

    .endloop:
        
        mov al, cl
        add al, 48
        call putchar

        mov al, 47
        call putchar

        mov al, dl
        add al, 48
        call putchar
        ret

times 510 - ($ - $$) db 0
dw 0xaa55
