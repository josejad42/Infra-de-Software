teste: ; função para testar as outras fucoes
    xor bx, bx
    call SetBandeira
    call SetLives

    call init
    ret

SetLives: ;Inicial life
    mov si, heart
    mov cx, 23
    mov dx, 9
    call printObj

    mov si, heart
    mov cx, 36
    mov dx, 9
    call printObj

    mov si, heart
    mov cx, 48
    mov dx, 9
    call printObj

    ret

SetBandeira:
    mov si, bandeira
    mov cx, 141 ; horizontal
    mov dx, 126 ;vertical
    call printObj
    ret



init: ; inicializa na posicao inicial

    mov si, Red_Square
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

    mov si, LGreen_Square
    pop cx
    pop dx
    push dx
    push cx
    call printObj   ; muda a cor da posicao anterior

    mov si, Red_Square
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

    mov si, LGreen_Square
    pop cx
    pop dx
    push dx
    push cx
    call printObj

    
    mov si, LGreen_Square
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

    mov si, LGreen_Square
    pop cx
    pop dx
    push dx
    push cx
    call printObj

    
    mov si, LGreen_Square
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

    mov si, LGreen_Square
    pop cx
    pop dx
    push dx
    push cx
    call printObj

    
    mov si, LGreen_Square
    pop cx
    pop dx
    add dx, 15
    push dx
    push cx

    call printObj
    jmp .continue

.continue:     ; continua printando na ocasiao do bixin estar parado

    mov si, Red_Square
    pop cx
    pop dx
    push dx
    push cx
    call printObj

    ;Estou mexendo
    call bombas_PrimeiraVida
    ;Estou mexendo
    
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


bombas_PrimeiraVida:

    cmp cx, 21 ; coluna 1
    je .coluna1 

    cmp cx, 36
    je .coluna2

    cmp cx, 51
    je .coluna3

    cmp cx, 66
    je .coluna4
    
    cmp cx, 81
    je .coluna5

    cmp cx, 96
    je .coluna6

    cmp cx, 111
    je .coluna7

    cmp cx, 126
    je .coluna8

    jmp .goBack


    .coluna1:
        cmp dx, 51
        je .decide

        cmp dx, 81
        je .decide

        cmp dx, 126
        je .decide

        jmp .goBack

    .coluna2:
        cmp dx, 51
        je .decide

        cmp dx, 111
        je .decide

        jmp .goBack

    .coluna3:
        cmp dx, 21
        je .decide

        cmp dx, 81
        je .decide

        jmp .goBack

    .coluna4:
        cmp dx, 51
        je .decide

        cmp dx, 96
        je .decide

        cmp dx, 111
        je .decide

        jmp .goBack

    .coluna5:
        cmp dx, 36
        je .decide

        cmp dx, 66
        je .decide

        cmp dx, 126
        je .decide

        jmp .goBack

    .coluna6:
        cmp dx, 81
        je .decide

        cmp dx, 111
        je .decide

        jmp .goBack

    .coluna7:
        cmp dx, 21
        je .decide

        cmp dx, 51
        je .decide

        cmp dx, 96
        je .decide

        jmp .goBack

    .coluna8:
        cmp dx, 36
        je .decide

        cmp dx, 66
        je .decide

        jmp .goBack

    .decide:
        add bx, 1

        cmp bx, 1
        je .firstLife

        cmp bx, 2
        je .secondLife

        cmp bx, 3
        je .thirdLife

        jmp .goBack


    .firstLife:
        mov si, black
        mov cx, 48
        mov dx, 9
        call printObj

        pop cx
        pop dx
        push dx
        push cx  

        jmp .goBack


    .secondLife: ; Apaga a primeira vida

        mov si, black
        mov cx, 36
        mov dx, 9
        call printObj

        pop cx
        pop dx
        push dx
        push cx  

        jmp .goBack
    
    .thirdLife: ;Apaga a terceira vida
        mov si, black
        mov cx, 23
        mov dx, 9
        call printObj

        pop cx
        pop dx
        push dx
        push cx   

        jmp .endgame

        jmp .goBack

    .endgame:
        call _clear

    .goBack:
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


_clearKeys: ; apaga o buffer do teclado
 	mov ah, 05h
	int 16h
	ret

_clear: ; Apagar tela
    mov ah, 0
    mov al, 10h
    int 10h
    ret
