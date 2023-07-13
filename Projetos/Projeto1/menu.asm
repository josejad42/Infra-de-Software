org 0x7e00
jmp 0x0000:start

data:
	string db 16, 16, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 6, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 6, 14, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 6, 6, 6, 4, 4, 6, 14, 6, 4, 4, 4, 4, 4, 4, 4, 6, 14, 14, 6, 4, 4, 4, 6, 14, 6, 4, 4, 4, 4, 4, 6, 14, 14, 14, 6, 4, 4, 4, 4, 14, 14, 4, 4, 4, 4, 4, 4, 6, 6, 6, 14, 6, 4, 4, 4, 6, 14, 4, 4, 4, 4, 4, 4, 4, 4, 4, 6, 14, 6, 4, 4, 6, 14, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 6, 14, 6, 4, 14, 14, 4, 4, 4, 4, 4, 4, 6, 6, 4, 4, 4, 6, 14, 14, 14, 14, 4, 4, 4, 4, 4, 6, 14, 6, 14, 6, 6, 6, 14, 14, 14, 6, 4, 4, 4, 4, 6, 14, 6, 4, 6, 14, 14, 14, 14, 14, 14, 6, 4, 4, 4, 4, 14, 6, 4, 4, 4, 4, 4, 4, 4, 4, 6, 14, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
  opcao1 db "1. Mapa 1", 0
  opcao2 db "2. Mapa 2", 0
  opcao3 db "3. Mapa 3", 0
  sair db "4. Sair", 0


	;Dados do projeto...

start:
    mov si, string

    mov ah, 0
    mov al, 12h
    int 10h

    call print

    xor ax, ax
    mov es, ax
    mov ax, opcao1
    mov bp, ax

    mov ah, 13h
    mov al, 00h
    mov bh, 0
    mov bl, 0xf
    mov cx, 9
    mov dh, 10
    mov dl, 35
    int 10h

    xor ax, ax
    mov es, ax
    mov ax, opcao2
    mov bp, ax

    mov ah, 13h
    mov al, 00h
    mov bh, 0
    mov bl, 0xf
    mov cx, 9
    mov dh, 12
    mov dl, 35
    int 10h

    xor ax, ax
    mov es, ax
    mov ax, opcao3
    mov bp, ax

    mov ah, 13h
    mov al, 00h
    mov bh, 0
    mov bl, 0xf
    mov cx, 9
    mov dh, 14
    mov dl, 35
    int 10h

    xor ax, ax
    mov es, ax
    mov ax, sair
    mov bp, ax

    mov ah, 13h
    mov al, 00h
    mov bh, 0
    mov bl, 0xf
    mov cx, 7
    mov dh, 16
    mov dl, 35
    int 10h

    mov cx, 0
    mov dx, 150
    mov ah, 0ch
    mov bh, 0
    mov al, 0xf

    .linha1:
      int 10h

      inc cx

      cmp cx, 640
      jb .linha1

    mov cx, 0
    mov dx, 280

    .linha2:
      int 10h
      
      inc cx

      cmp cx, 640
      jb .linha2







    




    

    jmp $

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
