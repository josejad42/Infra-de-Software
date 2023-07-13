;;;;;;;; FUNCOES QUE NAO ESTAO MAIS SENDO USADAS ;;;;;;;

criaSquare14: ;; nesse precisa passar a cor em ax, mas está em desuso porque preciso do registrador ax
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



;;;; Quadrado 14x14 na cor 12 - VERMELHO
criaSquare14_12:
    xor bx, bx
    xor cx, cx
    xor dx, dx
    .loop1:
        inc dx
        mov word tsquare [bx], 12
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

;;;; Quadrado 14x14 na cor 10 - VERDE CLARO
criaSquare14_10:
    xor bx, bx
    xor cx, cx
    xor dx, dx
    .loop1:
        inc dx
        mov word tsquare [bx], 10
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
        mov word tsquare [bx], 0
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

    .firstLife:
        mov si, black
        mov cx, 48
        mov dx, 9
        call printObj

        mov cx, 1

        jmp .goBack


    .secondLife: ; Apaga a primeira vida

        mov si, black
        mov cx, 36
        mov dx, 9
        call printObj

        mov cx, 1

        jmp .goBack
    
    .thirdLife: ;Apaga a terceira vida
        mov si, black
        mov cx, 23
        mov dx, 9
        call printObj

        mov cx, 1

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