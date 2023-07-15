set_options:
    mov bp, ax

    mov ah, 13h
    mov al, 00h
    mov bh, 0
    mov bl, 0xf
    mov dl, 28 ;posicao inicial na linha
    int 10h
    ret

menu:
    mov si, image

    mov ah, 0
    mov al, 12h
    int 10h

    call print

    xor ax, ax
    mov es, ax
    mov ax, opcao1
    mov cx, 26 ;quantidades de chars na string
    mov dh, 8  ;altura da string na tela
    call set_options

    xor ax, ax
    mov es, ax
    mov ax, opcao2
    mov cx, 14 ;quantidades de chars na string
    mov dh, 10
    call set_options

    xor ax, ax
    mov es, ax
    mov ax, opcao3
    mov cx, 18 ;quantidades de chars na string
    mov dh, 12
    call set_options

    xor ax, ax
    mov es, ax
    mov ax, opcao4
    mov cx, 23 ;quantidades de chars na string
    mov dh, 14
    call set_options

    xor ax, ax
    mov es, ax
    mov ax, sair
    mov cx, 7
    mov dh, 16
    call set_options

    mov cx, 0
    mov dx, 150
    mov ah, 0ch
    mov bh, 0
    mov al, 0xf

    mov dx, 115

    .linha1:
      int 10h
      inc cx
      cmp cx, 640
      jb .linha1

    mov cx, 0
    mov dx, 285

    .linha2:
      int 10h
      inc cx
      cmp cx, 640
      jb .linha2

ret

print:
    mov cx, 623
    mov dx, 463

    .loop:
  		cmp dx, 479
  		je .endloop

        cmp cx, 639
        je .endline
  		
        lodsb

        mov ah, 0ch
        int 10h
  		inc cx 		

  		jmp .loop

    .endline:
        mov cx, 623
        inc dx
        jmp .loop

  	.endloop:
        ret
jmp $