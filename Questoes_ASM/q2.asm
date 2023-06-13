; A QUESTÃO AINDA NÃO ESTÁ FINALIZADA

org 0x7c00
jmp 0x0000:start

string: times 9 db 0, 0
start:
    mov di, string
    call gets
    call getchar
    ;call printTam

putchar:
    mov ah, 0x0e
    int 10h
    ret

getchar:
    mov ah, 0x00
    int 16h
    ret

delchar:
    mov al, 0x08
    call putchar

    mov al, ''
    call putchar

    mov al, 0x08org 0x7c00
jmp 0x0000:start

string: times 9 db 0, 0
start:
    mov di, string
    call gets
    call getchar
    ;call printTam

putchar:
    mov ah, 0x0e
    int 10h
    ret

getchar:
    mov ah, 0x00
    int 16h
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
    .loop1:
        call getchar
        cmp al, 0x08
        je .backspace
        cmp al, 0x0d
        je .done
        cmp cl, 50
        je .loop1
        stosb
        inc cl
        call putchar
        jmp .loop1
        
        .backspace:
            cmp cl, 0
            je .loop1
            dec di
            dec cl
            mov byte[di], 0
            call delchar
            jmp .loop1

        .done:
            mov al, 0
            stosb
            mov al, 0x0a
            call putchar
            mov al, 0x0d
            call putchar
            ret 

printTam:
    .loop:
        lodsb
        cmp al, 0
        je .endloop

        call putchar

        jmp .loop

    call putchar

    .endloop:
        ret


times 510 - ($ - $$) db 0
dw 0xaa55
    call putchar

    ret

gets:
    .loop1:
        call getchar
        cmp al, 0x08
        je .backspace
        cmp al, 0x0d
        je .done
        cmp cl, 50
        je .loop1
        stosb
        inc cl
        call putchar
        jmp .loop1
        
        .backspace:
            cmp cl, 0
            je .loop1
            dec di
            dec cl
            mov byte[di], 0
            call delchar
            jmp .loop1

        .done:
            mov al, 0
            stosb
            mov al, 0x0a
            call putchar
            mov al, 0x0d
            call putchar
            ret 

printTam:
    .loop:
        lodsb
        cmp al, 0
        je .endloop

        call putchar

        jmp .loop

    call putchar

    .endloop:
        ret


times 510 - ($ - $$) db 0
dw 0xaa55
