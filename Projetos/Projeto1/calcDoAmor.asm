calc:
    
    call _clear
    mov dh, 0
    mov dl, 0
    xor cx, cx, ;soma dos caracteres
    call print_title
    mov dh, 15
    mov dl, 15
    mov ax, titulo11
    call print_string
    .loopStart:
        call getchar
        cmp al, 13
        jne .loopStart
    call _clear
    xor ax, ax
    xor dx, dx
    mov ax, nome1
    xor si, si
    call print_string
    mov dl, 16
    xor bx, bx
    mov bx, 0
    
    .input1Loop:
        call getchar
        cmp al, 13
        je .afterInput1
        mov byte[si], al
        cmp bx, 3
        jb .insertN1
       
        .continueInput:
        xor ah, ah
        add cx, ax
        xor ax, ax
        mov ax, si
        call print_string
        add dl, 1
        jmp .input1Loop
    .insertN1:
        mov byte[pessoa1 + bx], al
        add bx, 1
        jmp .continueInput
    
    .afterInput1:
        mov dh, 2
        mov dl, 0
        mov ax, nome2
        call print_string
        mov dl, 41
        xor bx, bx
        mov bx, 0
    
    .input2Loop:
        call getchar
        cmp al, 13
        je .afterInput2
        mov byte[si], al
        cmp bx, 3
        jb .insertN2

        .continueInput2
        xor ah, ah
        add cx, ax
        xor ax, ax
        mov ax, si
        call print_string
        add dl, 1
        jmp .input2Loop
    .insertN2:
        mov byte[pessoa2 + bx], al
        add bx, 1
        jmp .continueInput2
    
    .afterInput2:
        mov ax, cx
        mov bl, 101
        div bl
        mov al, ah
        xor ah, ah
        mov di, string
        call tostring
        mov dh, 5
        mov dl, 0
        mov ax, afinidade
        call print_string
        mov dl, 24
        mov ax, string
        call print_string
        mov ax, percent
        mov dl, 27
        call print_string
        
        call getchar
        call print_heart
        mov dh, 3
        mov dl, 18
        mov ax, pessoa1
        
        call print_string
        mov dl, 38
        mov ax, pessoa2
        call print_string

        mov dh, 7
        mov dl, 28
        mov ax, string
        
        call print_string
        mov ax, percent
        mov dl, 30
        call print_string
        call getchar
        cmp al, 27
        je menuLoop
        jmp calc
