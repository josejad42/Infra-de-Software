gameSetup1: ; base visual do jogo
    xor bx, bx
    call gridar
    call SetBandeira
    call init1
    ret

init1: ; inicializa na posicao inicial

    mov si, Red_Square
    mov cx, 21
    mov dx, 21
    push dx
    push cx
    call printObj

    pusha
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

    jmp init1
    
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

    add bx, 1

    pusha
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
    popa

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

    add bx, 1

    pusha
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
    popa

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

    add bx, 1
    
    pusha
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
    popa


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

    add bx, 1

    pusha
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
    popa

    jmp .continue

.continue:     ; continua printando na ocasiao do bixin estar parado

    mov si, Red_Square
    pop cx
    pop dx
    push dx
    push cx
    call printObj

    ;;;;
    call esquema_de_bombas1
    cmp cx, 1
    je .bomb
    ;Estou mexendo

    call getchar
    cmp al, 100
    je .right
    cmp al, 97s
    je .left
    cmp al, 115
    je .down
    cmp al, 119
    je .up
 
    jmp .continue


    ;;; Mudar a cor do quadrado onde tem bomba
    .bomb:
        mov si, DarkRed_Square
        pop cx
        pop dx
        call printObj
        
        call init1

ret   
