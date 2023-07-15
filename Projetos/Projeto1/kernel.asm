org 0x7e00
jmp 0x0000:start

%include "data.asm"
%include "funcs.asm"
%include "grid.asm"
%include "game1.asm"
%include "game2.asm"
%include "game3.asm"
%include "game4.asm"
%include "bombardeio.asm"
%include "menu.asm"

start:
    xor ax, ax
    xor bx, bx
    xor cx, cx
    xor dx, dx
    mov ds, ax
    mov es, ax

    call _clear


    mov ah, 00h
        mov al, 10h
        int 10h

    call menu

    ;;; As fases do jogo - não está funcional porque falta pegar o input do user
    cmp al, 1
    je gameSetup1 
    cmp al, 2
    je gameSetup2
    cmp al, 3
    je gameSetup3
    cmp al, 4
    je gameSetup4
    ;;;;;;;;;;;;;;;

    
    ;Código do projeto...

   

jmp $