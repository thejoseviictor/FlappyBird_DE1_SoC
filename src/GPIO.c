// Funções relacionadas aos componentes de entrada, ligados ao GPIO da DE1-SoC

#include "GPIO.h"

// Declaração de Variáveis Globais:
void* GPIO_VIRTUAL;
volatile unsigned int* KEYS_BASE;

// Virtualizando o Endereço Físico do "GPIO":
int GPIO_mapping(void){
    size_t GPIO0_SPAN = 4096;
    off_t GPIO0_OFST = 0xff200000;
    GPIO_VIRTUAL = mmap(NULL, GPIO0_SPAN, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO0_OFST);
    KEYS_BASE = GPIO_VIRTUAL + 0x0;  // Botões (KEYS).
    return 0;
}

/**
* Lê e retorna os valores lógicos dos botões:
* 15 (0xF) - Botões Desligados - Return 0
* 14 (0xE) - KEY0 - Botão 0 Pressionado - Return 1
* 13 (0xD) - KEY1 - Botão 1 Pressionado - Return 2
* 11 (0xB) - KEY2 - Botão 2 Pressionado - Return 3
* 07 (0x7) - KEY3 - Botão 3 Pressionado - Return 4
*/
int read_keys(void){
    int key_state;
    if (*KEYS_BASE == 0xF)
        key_state = 0;  // Nenhum botão está pressionado.
    else if (*KEYS_BASE == 0xE)
        key_state = 1;  // O botão (KEY0) está pressionado.
    else if (*KEYS_BASE == 0xD)
        key_state = 2;  // O botão (KEY1) está pressionado.
    else if (*KEYS_BASE == 0xB)
        key_state = 3;  // O botão (KEY2) está pressionado.
    else if (*KEYS_BASE == 0x7)
        key_state = 4;  // O botão (KEY3) está pressionado.
    else
        key_state = 0; // Se mais de um botão estiver pressionado.
    return key_state;
}
