gameSetup3: ; base visual do jogo
    call set_game
    call init3
    ret

init3: ; inicializa na posicao inicial
    call base_Init1
    push dx
    push cx
    call printObj

    pusha
    call set_Passos
    popa
    
    call getchar    ; lê w, a, s, d
    cmp al, 100
    je .right
    cmp al, 97
    je .left
    cmp al, 115
    je .down
    cmp al, 119
    je .up

    jmp init3
    
.right:
    pop cx
    push cx
    cmp cx, 120     ; verifica se n ultrapassa os limites do tabuleiro
    jg .continue3    

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

    add bx, 1

    pusha
    call set_Passos
    popa

    jmp .continue3

.left:
    pop cx
    push cx
    cmp cx, 22
    jl .continue3

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

    add bx, 1

    pusha
    call set_Passos
    popa

    jmp .continue3

.up:
    pop cx
    pop dx
    push dx
    push cx
    cmp dx, 22
    jl .continue3

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

    add bx, 1
    
    pusha
    call set_Passos
    popa


    jmp .continue3

.down:
    pop cx
    pop dx
    push dx
    push cx
    cmp dx, 120
    jg .continue3

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

    add bx, 1

    pusha
    call set_Passos
    popa

    jmp .continue3

.continue3:     ; continua printando na ocasiao do bixin estar parado

    mov si, Red_Square
    pop cx
    pop dx
    push dx
    push cx
    call printObj

    ;;;;
    call esquema_de_bombas3
    cmp cx, 1
    je .bomb3
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
 
    jmp .continue3

    ;;; Mudar a cor do quadrado onde tem bomba
    .bomb3:
        mov si, DarkRed_Square
        pop cx
        pop dx
        call printObj
        
        call init3

ret