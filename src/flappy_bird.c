#include "game_features.h"  // Funções de jogabilidade do "Flappy Bird".
#include "sprites.h"        // Para criar e armazenar os sprites do "Flappy Bird".
#include <pthread.h>

int main(){
    pthread_t player1_input_thread; // Thread da movimentação do jogador 1.
    pthread_t player2_input_thread; // Thread da movimentação do jogador 2.
    physical_to_virtual();          // Mapeando os endereços do VGA.
    open_memory();                  // Abrindo a memória para o "ADXL345" e "GPIO".
    I2C0_mapping();                 // Mapeando os endereços do "I2C0".
    GPIO_mapping();                 // Mapeando os endereços do "GPIO".
    enable_I2C0_HPS();              // Habilitando a entrada do "I2C0" no multiplexador.
    setting_I2C0_ADXL345();         // Configurando o "ADXL345" no "I2C0".
    setting_ADXL345();              // Calibrando o "ADXL345".
    linux_event_file();             // Abrindo o arquivo de leitura de eventos do Linux.
    clean_screen();                 // Limpando a tela.
    background_color(COLOR_CYAN);   // Mudando a cor do background.
    flappy_bird_sprites();          // Colocando os sprites do "Flappy Bird" na memória.   
    pthread_create(&player1_input_thread, NULL, check_player1_input, NULL); // Verificando se há entradas e atualizando a posição do jogador 1.
    pthread_create(&player2_input_thread, NULL, check_player2_input, NULL); // Verificando se há entradas e atualizando a posição do jogador 2.      
    while(!(player1_gameover && player2_gameover)){
        set_pipe();
    }
    close(fd);                      // Fechando o arquivo de acesso a memória do Linux.
    close(fd_event);                // Fechando o arquivo de leitura de eventos do Linux.
    unmap_memory();                 // Removendo o endereço virtual do VGA.
    return 0;
}
