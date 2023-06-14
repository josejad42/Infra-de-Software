org 0x7e00
jmp 0x0000:start

data:
  palavra db "insira as data ai meu dog: ", 0
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

    .main:
      mov si, palavra
      call prints
      call endl
        
      xor cx, cx
      xor bx, bx
      xor dx, dx
      .loop3:
        call getchar
        call putchar
        inc cx

        cmp al, '-'
        je .soma
        sub al, 48
        add dl, al
        cmp cx, 10
        je .soma
        jmp .loop3

      .soma:
        cmp dl, 10
        jb .somafinal

        .soma1:
          sub dl, 10
          add dh, 1
          cmp dl, 10
          jae .soma1
          add dl, dh
          add bl, dl
          xor dx, dx
          
          cmp cx, 10
          je .fim
          jmp .loop3
        
        .somafinal:
          add bl, dl
          xor dx, dx

          cmp cx, 10
          je .fim
          jmp .loop3
        
        

      .fim:
        call endl
        
        .loop4:
          cmp bl, 10
          jb .final
          
          .soma2:
            sub bl, 10
            add bh, 1
            cmp bl, 10
            jae .soma2

            add bl, bh
            jmp .final

        
        .final:
          mov bh, 0
          cmp bl, 10
          jae .soma2
          
          mov al, bl
          add al, 48
          call putchar
          call endl
          jmp .main
        


        



      

    

jmp $
