.section .data
@Para virtualização de memória:
fd:                     .asciz "/dev/mem"
fd_return:              .word 0x0
virtual_address:        .word 0x0
ALT_LWFPGASLVS_SPAN:    .word 0x1000
ALT_LWFPGASLVS_OFST:    .word 0xFF200
.EQU sys_open, 5
.EQU sys_close, 6
.EQU sys_exit, 1
.EQU sys_mmap2, 192
.EQU sys_munmap, 91
@Para barramento de dados:
.EQU DATA_A, 0x80
.EQU DATA_B, 0x70
.EQU WRFULL, 0xB0
.EQU WRREG, 0xC0

.section .text
.global physical_to_virtual
.type	physical_to_virtual,%function

.global unmap_memory
.type	unmap_memory,%function

.global background_color
.type background_color,%function

.global background_drawing
.type background_drawing,%function

.global sprite_drawing
.type sprite_drawing,%function

.global background_block_erase
.type background_block_erase,%function

.global draw_polygon
.type draw_polygon,%function

.global set_sprite
.type set_sprite,%function

.global buffer_overflow
.type buffer_overflow,%function

@Mapeando virtualmente o endereço físico:
physical_to_virtual:
    @Salvando os registradores na pilha:
    PUSH {R0, R1, R2, R3, R4, R5, R7, LR}
    @Arquivo de acesso a memória fisica do Linux
    @MOVT (16 MSB bits) e MOVW (16 LSB bits)
    MOV R7, #sys_open
    LDR R0, =fd       @pathname = "/dev/mem"
    MOVW R1, #0x1002  @flags = O_RDWR | O_SYNC
    MOVT R1, #0x0010  @flags = O_RDWR | O_SYNC
    MOV R2, #0        @mode = 0
    SVC #0
    @Salvando o valor de retorno do "open":
    LDR R4, =fd_return
    STR R0, [R4]
    LDR R4, [R4]                  @Salvando "fd" no R4
    @Mapeando virtualmente:                  
    MOV R7, #sys_mmap2
    MOV R0, #0                    @addr = NULL
    LDR R1, =ALT_LWFPGASLVS_SPAN  @length = 4096 = 0x1000
    LDR R1, [R1]
    MOV R2, #3                    @prot = PROT_READ | PROT_WRITE
    MOV R3, #1                    @flags = MAP_SHARED
    LDR R5, =ALT_LWFPGASLVS_OFST  @offset = 0xFF200
    LDR R5, [R5]
    SVC #0
    @Salvando o endereço virtual em uma variável global:
    LDR R1, =virtual_address
    STR R0, [R1]
    @Removendo os registradores da pilha e saindo da função:
    POP {R0, R1, R2, R3, R4, R5, R7, LR}
    BX LR

@Função para remover o endereço mapeado da memória e fechar o "/dev/mem"
unmap_memory:
    @Salvando os registradores na pilha:
    PUSH {R0, R1, R7, LR}
    @Removendo o endereço virtual (munmap):
    LDR R0, =virtual_address
    LDR R0, [R0]
    LDR R1, =ALT_LWFPGASLVS_SPAN @addr = 4096
    LDR R1, [R1]
    MOV R7, #sys_munmap
    SVC #0
    @Fechando o "/dev/mem":
    LDR R0, =fd_return
    LDR R0, [R0]
    MOV R7, #sys_close
    SVC #0
    @Removendo os registradores da pilha e saindo da função:
    POP {R0, R1, R7, LR}
    BX LR

@Função para mudar a cor do plano de fundo (Instrução WBR):
@Parâmetros:
@R0 = Cor
background_color:
    @Salvando os registradores na pilha:
    PUSH {R0, R1, R2, R3, R9, LR}
    @Montando a instrução:
    MOV R1, R0               @Salvando o parâmetro de cor em outro registrador
    LDR R0, =virtual_address @Carregando o endereço virtual
    LDR R0, [R0]
    @Enviado os dados da instrução:
    MOV R2, #0               @Salvado a constante "0" no R2
    MOV R3, #1               @Salvando a constante "1" no R3
    STR R2, [R0, #WRREG]     @Desativando o sinal de "start"
    STR R2, [R0, #DATA_A]    @opcode(0000) e registrador R9 (1001) para "DATA_A"
    STR R1, [R0, #DATA_B]    @Valor de cor do parâmetro, que foi armazenado em R1, para "DATA_B"
    STR R3, [R0, #WRREG]     @Sinal de "start"
    STR R2, [R0, #WRREG]     @Desativando o sinal de "start"
    @Removendo os registradores da pilha e saindo da função:
    POP {R0, R1, R2, R3, R9, LR}
    BX LR

@Função para preencher áreas do background (Instrução WBM):
@Pequenos blocos de 8x8 pixels, com endereços de memória correspondes
@Quantidade de Blocos: 80 Horizontais e 60 Verticais
@Expressão do Endereço de 12 bits: (linha * 80) + coluna
@Parâmetros:
@R0 = Coordenada da linha
@R1 = Coordenada da coluna
@R2 = Cor
background_drawing:
    @Salvando os registradores na pilha:
    PUSH {R0, R1, R2, R3, R4, LR}
    @Calculando o endereço do bloco:
    MOV R3, #80              @Constante "80"
    MUL R0, R0, R3           @R0 = linha * 80
    ADD R0, R0, R1           @R0 = (linha * 80) + coluna
    @Montando a instrução:
    LSL R0, #4               @Deslocando o endereço do bloco em 4 bits
    MOV R1, #2               @opcode(0010)
    ADD R1, R1, R0           @Concatenando o "opcode" e o endereço de memória do bloco
    @Carregando o endereço virtual:
    LDR R0, =virtual_address
    LDR R0, [R0]
    @Enviado os dados da instrução:
    MOV R3, #0               @Salvado a constante "0"
    MOV R4, #1               @Salvando a constante "1"
    STR R3, [R0, #WRREG]     @Desativando o sinal de "start"
    STR R1, [R0, #DATA_A]    @Enviando o "opcode" e o endereço de memória do bloco para o "DATA_A"
    STR R2, [R0, #DATA_B]    @Cor para "DATA_B"
    STR R4, [R0, #WRREG]     @Sinal de "start"
    STR R3, [R0, #WRREG]     @Desativando o sinal de "start"
    @Removendo os registradores da pilha e saindo da função:
    POP {R0, R1, R2, R3, R4, LR}
    BX LR

@Função de escrita na memória dos sprites (Instrução WSM):
@Quantidade máxima de sprites: 32
@Dimensões máximas de um sprite: 20x20 pixels
@Quantidade de posições em pixels: 20 de linha e 640 de coluna
@Expressão do endereço de 14 bits do pixel: (linha * 640) + coluna
@Parâmetros:
@R0 = Coordenada da linha
@R1 = Coordenada da coluna
@R2 = Cor
sprite_drawing:
    @Salvando os registradores na pilha:
    PUSH {R0, R1, R2, R3, R4, LR}
    @Calculando o endereço do bloco:
    MOV R3, #20              @Constante "20"
    MUL R0, R0, R3           @R0 = linha * 20
    ADD R0, R0, R1           @R0 = (linha * 20) + coluna
    @Montando a instrução:
    LSL R0, #4               @Deslocando o endereço do bloco em 4 bits
    MOV R1, #1               @opcode(0001)
    ADD R1, R1, R0           @Concatenando o "opcode" e o endereço de memória do bloco
    @Carregando o endereço virtual:
    LDR R0, =virtual_address
    LDR R0, [R0]
    @Enviado os dados da instrução:
    MOV R3, #0               @Salvado a constante "0"
    MOV R4, #1               @Salvando a constante "1"
    STR R3, [R0, #WRREG]     @Desativando o sinal de "start"
    STR R1, [R0, #DATA_A]    @Enviando o "opcode" e o endereço de memória do bloco para o "DATA_A"
    STR R2, [R0, #DATA_B]    @Cor para "DATA_B"
    STR R4, [R0, #WRREG]     @Sinal de "start"
    STR R3, [R0, #WRREG]     @Desativando o sinal de "start"
    @Removendo os registradores da pilha e saindo da função:
    POP {R0, R1, R2, R3, R4, LR}
    BX LR

@Função para resetar um bloco na memória do background (Instrução WBM):
@O bloco será preenchido com a cor base do background, polı́gono ou sprite.
@Parâmetros:
@R0 = Coordenada da linha
@R1 = Coordenada da coluna
background_block_erase:
    @Salvando os registradores na pilha:
    PUSH {R0, R1, R2, R3, R4, LR}
    @Calculando o endereço do bloco:
    MOV R3, #80              @Constante "80"
    MUL R0, R0, R3           @R0 = linha * 80
    ADD R0, R0, R1           @R0 = (linha * 80) + coluna
    @Montando a instrução:
    LSL R0, #4               @Deslocando o endereço do bloco em 4 bits
    MOV R1, #2               @opcode(0010)
    ADD R1, R1, R0           @Concatenando o "opcode" e o endereço de memória do bloco
    MOVW R2, #510            @Valor RGB para resetar o bloco
    @Carregando o endereço virtual:
    LDR R0, =virtual_address
    LDR R0, [R0]
    @Enviado os dados da instrução:
    MOV R3, #0               @Salvado a constante "0"
    MOV R4, #1               @Salvando a constante "1"
    STR R3, [R0, #WRREG]     @Desativando o sinal de "start"
    STR R1, [R0, #DATA_A]    @Enviando o "opcode" e o endereço de memória do bloco para o "DATA_A"
    STR R2, [R0, #DATA_B]    @Cor de "reset" para "DATA_B"
    STR R4, [R0, #WRREG]     @Sinal de "start"
    STR R3, [R0, #WRREG]     @Desativando o sinal de "start"
    @Removendo os registradores da pilha e saindo da função:
    POP {R0, R1, R2, R3, R4, LR}
    BX LR

@Função para desenhar um polígono (Instrução DP):
@Parâmetros (A partir de R4, os parâmetros vão para a pilha):
@R0 = Endereço do Polígono (De 0 a 31)
@R1 = Coordenada de Referência da Linha (Máximo 480)
@R2 = Coordenada de Referência da Coluna (Máximo 640)
@R3 = Tamanho
@R4 = Cor
@R5 = Tipo: Quadrado ou Triângulo
draw_polygon:
    @Salvando os registradores na pilha:
    PUSH {R4, R5, R7, LR}
    LDR R4, [SP, #16]       @Lendo "cor" na pilha
    LDR R5, [SP, #20]       @Lendo "tipo" na pilha
    @Montando a instrução:
    LSL R0, #4              @Deslocando o endereço em 4 bits
    MOV R7, #3              @opcode(0011)
    ADD R7, R7, R0          @Somando "opcode" e "endereço do polígono"
    LSL R1, #9              @Deslocando o "linha" em 9 bits
    LSL R3, #18             @Deslocando o "tamanho" em 18 bits
    LSL R4, #22             @Deslocando o "cor" em 22 bits
    LSL R5, #31             @Deslocando o "tipo" em 31 bits
    ADD R1, R1, R2          @Concatenando "coluna" e "linha"
    ADD R1, R1, R3          @Concatenando "coluna", "linha" e "tamanho"
    ADD R1, R1, R4          @Concatenando "coluna", "linha", "tamanho" e "cor"
    ADD R1, R1, R5          @Concatenando "coluna", "linha", "tamanho", "cor" e "tipo"
    @Carregando o endereço virtual:
    LDR R0, =virtual_address
    LDR R0, [R0]
    @Enviado os dados da instrução:
    MOV R2, #0              @Salvado a constante "0"
    MOV R3, #1              @Salvando a constante "1"
    STR R2, [R0, #WRREG]    @Desativando o sinal de start
    STR R7, [R0, #DATA_A]   @"opcode" e "endereço" para "DATA_A"
    STR R1, [R0, #DATA_B]   @"coluna", "linha", "tamanho", "cor" e "tipo" para "DATA_B"
    STR R3, [R0, #WRREG]    @Sinal de start
    STR R2, [R0, #WRREG]    @Desativando o sinal de start
    @Removendo os registradores da pilha e saindo da função:
    POP {R4, R5, R7, LR}
    BX LR

@Função para configurar um sprite (Instrução WBR - 0000):
@Parâmetros (A partir de R4, os parâmetros vão para a pilha):
@R0 = Registrador R1-R31 (00001 - 11111)
@R1 = Offset (9 bits) (Máximo: 511)
@R2 = Coordenada da Linha (10 bits) (Máximo: 480)
@R3 = Coordenada da Coluna (10 bits) (Máximo: 640)
@R4 = sp (0 - Desabilitado; 1 - Habilitado)
set_sprite:
    @Salvando os registradores na pilha:
    PUSH {R4, LR}
    LDR R4, [SP, #8]       @Lendo "sp" na pilha
    @Montando a instrução:
    LSL R2, #9             @Deslocando o "linha" em 9 bits
    LSL R3, #19            @Deslocando o "coluna" em 19 bits
    LSL R4, #29            @Deslocando o "sp" em 29 bits
    ADD R1, R1, R2         @Concatenando "offset" e "coluna"
    ADD R1, R1, R3         @Concatenando "offset", "coluna" e "linha"
    ADD R1, R1, R4         @Concatenando "offset", "coluna", "linha" e "sp"
    MOV R2, R0             @Salvando o parâmetro "registrador"
    LSL R2, #4             @Deslocando "registrador" em 4 bits
    @Carregando o endereço virtual:
    LDR R0, =virtual_address
    LDR R0, [R0]
    @Enviado os dados da instrução:
    MOV R3, #0             @Salvado a constante "0"
    MOV R4, #1             @Salvando a constante "1"
    STR R3, [R0, #WRREG]   @Desativando o sinal de "start"
    STR R2, [R0, #DATA_A]  @"opcode: 0000" e "registrador" para "DATA_A"
    STR R1, [R0, #DATA_B]  @"offset", "coluna", "linha", "sp"
    STR R4, [R0, #WRREG]   @Sinal de "start"
    STR R3, [R0, #WRREG]   @Desativando o sinal de "start"
    @Removendo os registradores da pilha e saindo da função:
    POP {R4, LR}
    BX LR

@Desvio que previne o overflow do buffer de "DATA_A" e "DATA_B":
buffer_overflow:
    LDR R0, =virtual_address
    LDR R0, [R0]
    LDR R0, [R0, #WRFULL]
    CMP R0, #1
    BEQ buffer_overflow
    BX LR
