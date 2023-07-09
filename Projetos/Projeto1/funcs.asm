teste: ; função para testar as outras fucoes
    mov ax, 8 ; cor do quadrado -> cinza escuro
    call criaSquare14 

    mov si, tsquare
    mov cx, 20 ; até 640
    mov dx, 20 ; até 350
    call printObj


    mov ax, 10
    call criaSquare9

    mov si, tsquare
    mov cx, 23
    mov dx, 23
    call printObj

    ret


init: ; inicializa na posicao inicial
    mov ax, 12
    call criaSquare14 

    mov si, tsquare
    mov cx, 21
    mov dx, 21
    push dx
    push cx
    call printObj
    
    call getchar    ; lê w, a, s, d
    cmp al, 100
    je .right
    cmp al, 97
    je .left
    cmp al, 115
    je .down
    cmp al, 119
    je .up

    jmp init
    
.right:
    pop cx
    push cx
    cmp cx, 120     ; verifica se n ultrapassa os limites do tabuleiro
    jg .continue    

    mov ax, 10
    call criaSquare14 
    mov si, tsquare
    pop cx
    pop dx
    push dx
    push cx
    call printObj   ; muda a cor da posicao anterior

    mov ax, 12
    call criaSquare14 
    mov si, tsquare
    pop cx
    pop dx
    add cx, 15      ; muda de posicao
    push dx
    push cx
    call printObj

    jmp .continue

.left:
    pop cx
    push cx
    cmp cx, 22
    jl .continue

    mov ax, 10
    call criaSquare14 
    mov si, tsquare
    pop cx
    pop dx
    push dx
    push cx
    call printObj

    mov ax, 10
    call criaSquare14 

    
    mov si, tsquare
    pop cx
    pop dx
    sub cx, 15
    push dx
    push cx

    call printObj
    jmp .continue

.up:
    pop cx
    pop dx
    push dx
    push cx
    cmp dx, 22
    jl .continue

    mov ax, 10
    call criaSquare14 
    mov si, tsquare
    pop cx
    pop dx
    push dx
    push cx
    call printObj

    mov ax, 10
    call criaSquare14 
    
    mov si, tsquare
    pop cx
    pop dx
    sub dx, 15
    push dx
    push cx

    call printObj
    jmp .continue

.down:
    pop cx
    pop dx
    push dx
    push cx
    cmp dx, 120
    jg .continue

    mov ax, 10
    call criaSquare14 
    mov si, tsquare
    pop cx
    pop dx
    push dx
    push cx
    call printObj

    mov ax, 10
    call criaSquare14 
    
    mov si, tsquare
    pop cx
    pop dx
    add dx, 15
    push dx
    push cx

    call printObj
    jmp .continue

.continue:     ; continua printando na ocasiao do bixin estar parado
    mov ax, 12
    call criaSquare14 

    mov si, tsquare
    pop cx
    pop dx
    push dx
    push cx
    call printObj
    
    call getchar
    cmp al, 100
    je .right
    cmp al, 97
    je .left
    cmp al, 115
    je .down
    cmp al, 119
    je .up
 
    jmp .continue

ret


getchar:
    mov ah, 0x00
    int 16h
ret

criaSquare14:
    xor bx, bx
    xor cx, cx
    xor dx, dx
    .loop1:
        inc dx
        mov word tsquare [bx], ax
        inc bx

        cmp dx, 14 ; num de colunas
            je .EOF
        jmp .loop1

    .EOF:
        inc cx
        cmp cx, 14 ; num de linhas
            je .END
        mov word tsquare [bx], '*'
        inc bx
        xor dx, dx
        jmp .loop1   

    .END:  
        mov word tsquare[bx], '#'
        ret

criaSquare9:
    xor bx, bx
    xor cx, cx
    xor dx, dx
    .loop1:
        inc dx
        mov word tsquare [bx], ax
        inc bx

        cmp dx, 9 ; num de colunas
            je .EOF
        jmp .loop1

    .EOF:
        inc cx
        cmp cx, 9 ; num de linhas
            je .END
        mov word tsquare [bx], '*'
        inc bx
        xor dx, dx
        jmp .loop1   

    .END:  
        mov word tsquare[bx], '#'
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


_clearKeys: ; apaga o buffer do teclado
 	mov ah, 05h
	int 16h
	ret

_clear: ; Apagar tela
    mov ah, 0
    mov al, 10h
    int 10h
    ret
