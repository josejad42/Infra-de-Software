;;; Todos os locais das bombas do mapa 1
esquema_de_bombas2:

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

        cmp dx, 126 
        je Ganhou

        jmp .goBack

    .decide:
        mov cx, 1
        jmp .goBack

        ;call .endGame

        jmp .goBack
    
    .endGame:
        call _clear

    .goBack:
        ret