;;; Todos os locais das bombas do mapa 1
esquema_de_bombas1:
    cmp cx, 21 ; coluna 1
    je .coluna1 
    cmp cx, 36 ; coluna 2
    je .coluna2
    cmp cx, 51 ; coluna 3
    je .coluna3
    cmp cx, 66 ; coluna 4
    je .coluna4
    cmp cx, 81 ; coluna 5
    je .coluna5
    cmp cx, 96 ; coluna 6
    je .coluna6
    cmp cx, 111 ; coluna 7
    je .coluna7
    cmp cx, 126 ; coluna 8
    je .coluna8

    jmp .goBack

    .coluna1:
        cmp dx, 66
        je .decide

        cmp dx, 81
        je .decide

        jmp .goBack

    .coluna2:
        cmp dx, 36
        je .decide

        cmp dx, 96
        je .decide

        jmp .goBack

    .coluna3:
        cmp dx, 51
        je .decide

        cmp dx, 66
        je .decide

        cmp dx, 111
        je .decide

        jmp .goBack

    .coluna4:
        cmp dx, 21
        je .decide

        cmp dx, 51
        je .decide

        cmp dx, 66
        je .decide

        cmp dx, 81
        je .decide
    
        cmp dx, 111
        je .decide

        jmp .goBack

    .coluna5:
        cmp dx, 21
        je .decide

        cmp dx, 81
        je .decide

        cmp dx, 126
        je .decide

        jmp .goBack

    .coluna6:
        cmp dx, 36
        je .decide

        cmp dx, 51
        je .decide

        cmp dx, 96
        je .decide

        cmp dx, 126
        je .decide

        jmp .goBack

    .coluna7:
        cmp dx, 66
        je .decide

        cmp dx, 126
        je .decide

        jmp .goBack

    .coluna8:
        cmp dx, 81
        je .decide

        cmp dx, 96
        je .decide

        cmp dx, 126 
        je Ganhou

        jmp .goBack

    .decide:
        mov cx, 1
        jmp .goBack

    .goBack:
        ret

;;; Todos os locais das bombas do mapa 2
esquema_de_bombas2:
    cmp cx, 21 ; coluna 1
    je .coluna1 
    cmp cx, 36 ; coluna 2
    je .coluna2
    cmp cx, 51 ; coluna 3
    je .coluna3
    cmp cx, 66 ; coluna 4
    je .coluna4
    cmp cx, 81 ; coluna 5
    je .coluna5
    cmp cx, 96 ; coluna 6
    je .coluna6
    cmp cx, 111 ; coluna 7
    je .coluna7
    cmp cx, 126 ; coluna 8
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

    .goBack:
        ret

;;; Todos os locais das bombas do mapa 3
esquema_de_bombas3:
    cmp cx, 21 ; coluna 1
    je .coluna1 
    cmp cx, 36 ; coluna 2
    je .coluna2
    cmp cx, 51 ; coluna 3
    je .coluna3
    cmp cx, 66 ; coluna 4
    je .coluna4
    cmp cx, 81 ; coluna 5
    je .coluna5
    cmp cx, 96 ; coluna 6
    je .coluna6
    cmp cx, 111 ; coluna 7
    je .coluna7
    cmp cx, 126 ; coluna 8
    je .coluna8

    jmp .goBack

    .coluna1:
        cmp dx, 66
        je .decide

        cmp dx, 126
        je .decide

        jmp .goBack

    .coluna2:
        cmp dx, 36
        je .decide

        cmp dx, 66
        je .decide

        cmp dx, 96
        je .decide

        jmp .goBack

    .coluna3:
        cmp dx, 66
        je .decide

        cmp dx, 111
        je .decide

        jmp .goBack

    .coluna4:
        cmp dx, 21
        je .decide

        cmp dx, 36
        je .decide

        cmp dx, 66
        je .decide

        cmp dx, 81
        je .decide
    
        cmp dx, 111
        je .decide

        jmp .goBack

    .coluna5:
        cmp dx, 21
        je .decide

        cmp dx, 66
        je .decide

        cmp dx, 111
        je .decide

        jmp .goBack

    .coluna6:
        cmp dx, 51
        je .decide

        cmp dx, 66
        je .decide

        cmp dx, 96
        je .decide

        jmp .goBack

    .coluna7:
        cmp dx, 36
        je .decide

        cmp dx, 51
        je .decide

        cmp dx, 96
        je .decide

        cmp dx, 126
        je .decide

        jmp .goBack

    .coluna8:
        cmp dx, 81
        je .decide

        cmp dx, 96
        je .decide

        cmp dx, 126 
        je Ganhou

        jmp .goBack

    .decide:
        mov cx, 1
        jmp .goBack

    .goBack:
        ret
        
;;; Todos os locais das bombas do mapa 4
esquema_de_bombas4:
    cmp cx, 36 ; coluna 2
    je .coluna2
    cmp cx, 51 ; coluna 3
    je .coluna3
    cmp cx, 66 ; coluna 4
    je .coluna4
    cmp cx, 81 ; coluna 5
    je .coluna5
    cmp cx, 96 ; coluna 6
    je .coluna6
    cmp cx, 111 ; coluna 7
    je .coluna7
    cmp cx, 126 ; coluna 8
    je .coluna8

    jmp .goBack

    .coluna2:
        cmp dx, 51
        je .decide

        cmp dx, 81
        je .decide

        cmp dx, 111
        je .decide

        jmp .goBack

    .coluna3:
        cmp dx, 66
        je .decide

        jmp .goBack

    .coluna4:
        cmp dx, 36
        je .decide

        cmp dx, 96
        je .decide
    
        cmp dx, 111
        je .decide

        jmp .goBack

    .coluna5:
        cmp dx, 81
        je .decide

        cmp dx, 111
        je .decide

        cmp dx, 126
        je .decide

        jmp .goBack

    .coluna6:
        cmp dx, 36
        je .decide

        cmp dx, 66
        je .decide

        cmp dx, 81
        je .decide

        jmp .goBack

    .coluna7:
        cmp dx, 51
        je .decide

        cmp dx, 96
        je .decide

        jmp .goBack

    .coluna8:
        cmp dx, 111
        je .decide

        cmp dx, 126 
        je Ganhou

        jmp .goBack

    .decide:
        mov cx, 1
        jmp .goBack

    .goBack:
        ret