gameSetup2: ; base visual do jogo
    call set_game
    call init2
    ret

init2: ; inicializa na posicao inicial
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

    jmp init2
    
.right:
    pop cx
    push cx
    cmp cx, 120     ; verifica se n ultrapassa os limites do tabuleiro
    jg .continue2    

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

    jmp .continue2

.left:
    pop cx
    push cx
    cmp cx, 22
    jl .continue2

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

    jmp .continue2

.up:
    pop cx
    pop dx
    push dx
    push cx
    cmp dx, 22
    jl .continue2

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


    jmp .continue2

.down:
    pop cx
    pop dx
    push dx
    push cx
    cmp dx, 120
    jg .continue2

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

    jmp .continue2

.continue2:     ; continua printando na ocasiao do bixin estar parado

    mov si, Red_Square
    pop cx
    pop dx
    push dx
    push cx
    call printObj

    ;;;;
    call esquema_de_bombas2
    cmp cx, 1
    je .bomb2
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
 
    jmp .continue2

    ;;; Mudar a cor do quadrado onde tem bomba
    .bomb2:
        mov si, DarkRed_Square
        pop cx
        pop dx
        call printObj
        
        call init2

ret