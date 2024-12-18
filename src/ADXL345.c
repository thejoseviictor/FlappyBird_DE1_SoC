// Funções para Acessar e Manipular a Memória e o Acelerômetro ADXL345 na DE1-SoC

#include "ADXL345.h"

// Declaração de Variáveis Globais:
int fd; // "fd": file descriptor;
void* I2C0_BASE_VIRTUAL; // Endereço Virtual Base do I2C0
volatile unsigned int* I2C0_DATA; // Para Escrever ou Ler em um "Slave"
volatile unsigned int* I2C0_RXFLR; // Para Verificar se Existem Dados a Receber

/*
Acessando a memória física do sistema
"fd" será "-1", caso ocorra um erro na abertura do arquivo
*/
void open_memory(void)
{
    fd = open("/dev/mem", O_RDWR | O_SYNC); // "fd": file descriptor;
    if(fd == -1)
        printf("Falha ao acessar a memória física!");
}

/*
Mapeia o endereço base do "I2C0" em endereço virtual
e salva os registradores em variáveis globais.
*/
void I2C0_mapping(void){
    size_t virtual_address_size = 4096; // Tamanho do Endereço Virtual
    // Endereços dos Registradores do Módulo "I2C0":
    off_t I2C0_BASE = 0xFFC04000; // Endereço Físico Base do I2C0
    I2C0_BASE_VIRTUAL = mmap (NULL, virtual_address_size, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, I2C0_BASE); // Endereço Virtual Base do I2C0
    I2C0_DATA = I2C0_BASE_VIRTUAL + 0x10; // Para Escrever ou Ler em um "Slave"
    I2C0_RXFLR = I2C0_BASE_VIRTUAL + 0x78; // Para Verificar se Existem Dados a Receber
}

/*
Usada para habilitar a comunicação do ADXL345 com o I2C0,
através do bloco de multiplexadores no módulo "sysmgr",
usando os pinos HPS
*/
void enable_I2C0_HPS(void)
{
    size_t virtual_address_size = 4096; // Tamanho do Endereço Virtual

    // Endereços dos Registradores do Bloco de Multiplexadores do Módulo "sysmgr":
    off_t SYSMGR = 0xFFD08000; // Endereço Físico Base do SYSMGR
    void * SYSMGR_VIRTUAL = mmap (NULL, virtual_address_size, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, SYSMGR); // Endereço Virtual Base do SYSMGR

    // Definindo os Endereços de Outros Registradores do Bloco de Multiplexadores, de Acordo com o Offset:
    volatile unsigned int * SYSMGR_GENERALIO7 = SYSMGR_VIRTUAL + 0x49C;
    volatile unsigned int * SYSMGR_GENERALIO8 = SYSMGR_VIRTUAL + 0x4A0;
    volatile unsigned int * SYSMGR_I2C0USEFPGA = SYSMGR_VIRTUAL + 0x704;

    // Selecionando os Valores das Seguintes Entradas:
    * SYSMGR_GENERALIO7 = 0x01;
    * SYSMGR_GENERALIO8 = 0x01;
    * SYSMGR_I2C0USEFPGA = 0x00;
}

void setting_I2C0_ADXL345(void)
{
    // Endereços dos Registradores do Módulo "I2C0":
    volatile unsigned int * I2C0_CONTROL = I2C0_BASE_VIRTUAL + 0x00; // Para ativar o modo "Master"
    volatile unsigned int * I2C0_TARGET = I2C0_BASE_VIRTUAL + 0x04; // Para selecionar o "Slave"
    volatile unsigned int * I2C0_ENABLE = I2C0_BASE_VIRTUAL + 0x6C; // Para ativar e desativar o I2C0
    volatile unsigned int * I2C0_ENABLE_STATUS = I2C0_BASE_VIRTUAL + 0x9C; // Para verificar se há alguma transmissão ativa

    /*
    Encerrando transmissões ativas e desativando o I2C0,
    para permitir a modificação dos registradores "ic_con"
    e "ic_tar":
    */
    * I2C0_ENABLE = 0x02;

    /*
    Analisa o bit 0, "activity", do registrador "ic_status",
    para verificar se há alguma atividade no I2C0. Então, só
    irá sair do loop quando essa possível atividade terminar.
    */
    while (((* I2C0_ENABLE_STATUS) & 0x1) == 1){}

    /*
    Configuração do registrador "ic_con":
        Modo "Slave" Desligado;
        "Restart Master" Ligado;
        Endereço de 7-bits para o Master;
        Endereço de 7-bits para o Slave;
        Modo de Alta Velocidade;
        Modo "Master" Ligado.
    */
    * I2C0_CONTROL = 0x65;

    // Selecionando o endereço base do ADXL345 no registrador "ic_tar":
    * I2C0_TARGET = 0x53;

    // Ativando o módulo "I2C0":
    * I2C0_ENABLE = 0x01;

    // Verificando se o módulo "I2C0" foi ativado:
    while (((* I2C0_ENABLE_STATUS) & 0x1) == 0){}
}

/*
Configurações iniciais dos sensores do ADXL345:
No Registrador BW_RATE - 0x2C:
	Modo de Operação: Normal
	Rate: Taxa de Dados de Saída: 100 Hz | Largura de Banda: 50 Hz
	Configuração Resultante: 0x0A
No Registrador POWER_CTL - 0x2D:
	Medição: Habilitada
	Frequência de Leitura: 8Hz (8 vezes por segundo 125ms)
	Configuração Resultante: 0x08
No Registrador DATA_FORMAT - 0x31:
	Modo de Resolução: Alta
	Intervalo de Aceleração (G-Range): +-4g.
	Configuração Resultante: 0x01
*/
void setting_ADXL345(void)
{
    // Configurando o THRESH_ACT:
    * I2C0_DATA = THRESH_ACT + 0x400;
    * I2C0_DATA = 0x0F;

    // Configurando o THRESH_INACT:
    * I2C0_DATA = THRESH_INACT + 0x400;
    * I2C0_DATA = 0x0F;

    // Configurando o TIME_INACT:
    * I2C0_DATA = TIME_INACT + 0x400;
    * I2C0_DATA = 0x02;

    // Configurando o ACT_INACT_CTL:
    * I2C0_DATA = ACT_INACT_CTL + 0x400;
    * I2C0_DATA = 0xFF;

    // Configurando o INT_ENABLE:
    * I2C0_DATA = INT_ENABLE + 0x400;
    * I2C0_DATA = 0x04 | 0x02;

    // Configurando o BW_RATE:
    * I2C0_DATA = BW_RATE + 0x400;
    * I2C0_DATA = 0x0A;

    // Configurando o POWER_CTL:
    * I2C0_DATA = POWER_CTL + 0x400;
    * I2C0_DATA = 0x08;

    // Configurando o DATA_FORMAT:
    * I2C0_DATA = DATA_FORMAT + 0x400;
    * I2C0_DATA = 0x01;
}

// Ler e retornar valores do Eixo X do ADXL345:
int16_t read_x(void)
{
    // Lendo os dados do byte menos significativo do Eixo X:
    * I2C0_DATA = DATAX0 + 0x400;
    * I2C0_DATA = 0x100; // "0x100", envia "1" no bit "8", "cmd", do registrador, ativando a leitura.
    while (* I2C0_RXFLR == 0) {} // Mantém no loop, enquanto o buffer do registrador "ic_rxflr" estiver vazio.
    uint8_t LSB_EixoX = * I2C0_DATA;
    
    // Lendo os dados do byte mais significativo do Eixo X:
    * I2C0_DATA = DATAX1 + 0x400;
    * I2C0_DATA = 0x100;
    while (* I2C0_RXFLR == 0) {}
    uint8_t MSB_EixoX = * I2C0_DATA;
    
    // Armazenando os dois bytes do Eixo X em um inteiro de 16 bits
    // Primeiro o Byte Mais Signficativo e Depois o Byte Menos Significativo
    int16_t EixoX = (MSB_EixoX << 8) | LSB_EixoX;

    return EixoX; // Retornando o valor de leitura do Eixo X
}
