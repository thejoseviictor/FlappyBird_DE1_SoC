#include "game_features.h"  // Funções de jogabilidade do "Flappy Bird".

int main(){
    physical_to_virtual();        // Mapeando os endereços do VGA.
    open_memory();                // Abrindo a memória para o acelerômetro.
    I2C0_mapping();               // Mapeando os endereços do "I2C0".
    enable_I2C0_HPS();            // Habilitando a entrada do "I2C0" no multiplexador.
    setting_I2C0_ADXL345();       // Configurando o "ADXL345" no "I2C0".
    setting_ADXL345();            // Calibrando o "ADXL345".
    clean_screen();               // Limpando a tela.
    background_color(COLOR_CYAN); // Mudando a cor do background.
    while(!(player1_gameover && player2_gameover)){
        set_pipe();
    }
    return 0;
}
