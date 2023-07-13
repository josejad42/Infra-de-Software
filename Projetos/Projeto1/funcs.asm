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
    mov al, 10h
    int 10h
    ret
