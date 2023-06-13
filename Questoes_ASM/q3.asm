org 0x7e00
jmp 0x0000:start

data:
  palavra db "insira x, y, z e w em ordem(sem dar espaco entre eles)", 0
  par db "par", 0
  impar db "impar", 0
	;Dados do projeto...

putchar:
  mov ah, 0x0e
  int 10h
  ret

getchar:
  mov ah, 0x00
  int 16h
  ret

delchar:
  mov al, 0x08          ; backspace
  call putchar
  mov al, ' '
  call putchar
  mov al, 0x08          ; backspace
  call putchar
  ret

endl:
  mov al, 0x0a          ; line feed
  call putchar
  mov al, 0x0d          ; carriage return
  call putchar
  ret


prints:             ; mov si, string
  .loop:
    lodsb           ; bota character em al 
    cmp al, 0
    je .endloop
    call putchar
    jmp .loop
  .endloop:
  ret




start:
    xor ax, ax
    mov ds, ax
    mov es, ax
    
    mov ah, 0
    mov al, 00h     ; iniciando modo de video
    int 10h

    mov si, palavra
    call prints
    call endl

    xor bx, bx
    call getchar
    call putchar
    sub al, 48
    mov dl, al
    

    call getchar
    call putchar
    sub al, 48
    mov dh, al

    call getchar
    call putchar
    sub al, 48
    mov cl, al

    call getchar
    call putchar
    sub al, 48
    mov ch, al
    call endl

    xor ax, ax
    mov al, cl
    mul ch          ; x * y
    add bx, ax

    xor ax, ax
    mov al, cl
    mul ch        ; z * w
    add bx, ax

    xor ax, ax
    mov al, dl
    div cl        ; x/z
    mov ah, 0
    sub bx, ax

    xor ax, ax
    mov al, ch
    div dh        ; w/y
    mov ah, 0
    add bx, ax

    xor ax, ax
    mov ax, bx
    mov bl, 2
    div bl

    cmp ah, 0
    je .pr
    mov si, impar
    call prints
    call endl
    jmp .fim

    .pr:
      mov si, par
      call prints
      call endl
      jmp .fim

    .fim:












   










    

jmp $
