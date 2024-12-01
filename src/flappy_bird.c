#include "game_features.h"  // Funções de jogabilidade do "Flappy Bird".
#include "sprites.h"        // Para criar e armazenar os sprites do "Flappy Bird".
#include <pthread.h>        // Para criar threads.

int main(){
    pthread_t player1_input_thread; // Thread da movimentação do jogador 1.
    pthread_t player2_input_thread; // Thread da movimentação do jogador 2.
    pthread_t keys_thread;          // Thread dos botões que alteram o estado do jogo.
    pthread_t sprite_animation;     // Thread de animação dos sprites.
    pthread_t score_thread;         // Thread que exibe a pontuação na tela.
    pthread_t clouds_thread;        // Thread das nuvens.
    physical_to_virtual();          // Mapeando os endereços do VGA.
    open_memory();                  // Abrindo a memória para o "ADXL345" e "GPIO".
    I2C0_mapping();                 // Mapeando os endereços do "I2C0".
    GPIO_mapping();                 // Mapeando os endereços do "GPIO".
    enable_I2C0_HPS();              // Habilitando a entrada do "I2C0" no multiplexador.
    setting_I2C0_ADXL345();         // Configurando o "ADXL345" no "I2C0".
    setting_ADXL345();              // Calibrando o "ADXL345".
    linux_event_file();             // Abrindo o arquivo de leitura de eventos do Linux.
    clean_screen();                 // Limpando a tela.
    background_color(bg_color);     // Mudando a cor do background.
    flappy_bird_sprites();          // Colocando os sprites do "Flappy Bird" na memória.  
    set_players();                  // Exibindo os sprites dos jogadores. 
    pthread_create(&player1_input_thread, NULL, check_player1_input, NULL); // Verificando se há entradas e atualizando a posição do jogador 1.
    pthread_create(&player2_input_thread, NULL, check_player2_input, NULL); // Verificando se há entradas e atualizando a posição do jogador 2.
    pthread_create(&keys_thread, NULL, check_buttons, NULL);                // Verificando os botões "KEY" como entradas que alteram o fluxo do jogo.
    pthread_create(&sprite_animation, NULL, sp_animation, NULL);            // Animando os sprites.
    pthread_create(&score_thread, NULL, show_score, NULL);                  // Exibindo a pontuação na tela.
    pthread_create(&clouds_thread, NULL, render_clouds, NULL);              // Renderizando as nuvens na tela.
    while(!game_exit){
        // Exibição e deslocamento dos canos na tela:
        while(!(player1_gameover && player2_gameover))
            set_pipe();
    }
    show_gameover_screen();          // Exibindo a tela "GAMEOVER", ao sair do jogo.
    set_players();                   // Removendo os sprites dos jogadores, ao sair do jogo.
    close(fd);                       // Fechando o arquivo de acesso a memória do Linux.
    close(fd_event);                 // Fechando o arquivo de leitura de eventos do Linux.
    unmap_memory();                  // Removendo o endereço virtual do VGA.
    return 0;
}
