org 0x7e00
jmp 0x0000:start

%include "data.asm"
%include "funcs.asm"
%include "grid.asm"
%include "game.asm"

data:
	
	;Dados do projeto...

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

    call gameSetup



    
    ;Código do projeto...

   

jmp $