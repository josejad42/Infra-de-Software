SetBandeira:
    mov si, bandeira
    mov cx, 141 ; horizontal
    mov dx, 126 ;vertical
    call printObj
    ret    

getchar:
    mov ah, 0x00
    int 16h
ret

set_game:
    xor bx, bx
    call gridar
    call SetBandeira
    ret

base_Init1:
    mov si, Red_Square
    mov cx, 21
    mov dx, 21
    ret

set_Passos:
    mov dh, 0
    mov dl, 0
    mov ax, passos
    call print_string

    mov ax, bx
    call tostring
    
    mov dh, 0
    mov dl, 7
    mov ax, string
    call print_string
    ret

printObj:  ;printa a string na posição (linha, coluna) = (dx, cx)
    push dx
	push cx
	.loop:
		lodsb  

		cmp al,'#'
		je .END

		cmp al,'*'	
		je .next_line

		.next_pixel:
			call printPixel
			inc cx      ;Percorrendo as colunas de pixel
			jmp .loop	
		
		.next_line:	
			pop cx      ;volta cx para a primeira posição para começar a próxima linha
			push cx

			inc dx
			lodsb
			jmp .next_pixel
		
	.END:
		pop cx
		pop dx		
		ret 


printPixel:      ;printa pixel na posição (linha, coluna) = (dx, cx)
    mov ah, 0ch
    mov bh, 0
    int 10h
    ret


;;;;;;;; RESOLVAM AÍ PARA PRINTAR O BX QUE EH O NUMERO DE PASSOS DADOS

reverse:              ; mov si, string
  mov di, si
  xor cx, cx          ; zerar contador
  .loop1:             ; botar string na stack
    lodsb
    cmp al, 0
    je .endloop1
    inc cl
    push ax
    jmp .loop1
  .endloop1:
  .loop2:             ; remover string da stack        
    pop ax
    stosb
    loop .loop2
  ret

tostring:              ; mov ax, int / mov di, string
  mov di, string
  push di
  .loop1:
    cmp ax, 0
    je .endloop1
    xor dx, dx
    mov bx, 10
    div bx            ; ax = 9999 -> ax = 999, dx = 9
    xchg ax, dx       ; swap ax, dx
    add ax, 48        ; 9 + '0' = '9'
    stosb
    xchg ax, dx
    jmp .loop1
  .endloop1:
  pop si
  cmp si, di
  jne .done
  mov al, 48
  stosb
  .done:
  mov al, 0
  stosb
  call reverse
  ret

putChar:
    mov ah, 0eh
    mov bl, dl

    int 10h
ret

printString:
    .loop:
        lodsb
        cmp al, 0
        je .endloop
        call putChar
        jmp .loop

    .endloop:
    ret

;;;;;;;;; ESSA PARTE TODA PEGUEI DA LISTA 5


_clearKeys: ; apaga o buffer do teclado
 	mov ah, 05h
	int 16h
	ret

_clear: ; Apagar tela
    mov ah, 0
    mov al, 12h
    int 10h
    ret

;;;;;; APAGA A TELA E PRINTA A QUANTIDADE DE PASSOS
Ganhou:
    call _clear
    call set_Passos
    


print_string:   ; mov ax, string
                ; dh --> pos y
                ; dl --> pos x

    pusha
    xor cx, cx
    mov si, ax
    
    push ax
    .contar:
      add cx, 1
      lodsb

      cmp al, 0
      jne .contar
    pop ax

    push ax
    xor ax, ax
    mov es, ax
    pop ax


    mov bp, ax

    mov ah, 13h
    mov al, 00h
    mov bh, 0
    mov bl, 0xf
    
    int 10h

    popa

    ret
