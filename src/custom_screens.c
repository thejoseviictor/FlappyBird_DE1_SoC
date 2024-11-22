// Funções relacionadas as telas personalizadas do jogo:

#include "custom_screens.h"

// Texto "GAMEOVER":
int game_over_screen[6][31] = {
    {1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0},
    {1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0 ,1, 1, 1, 0, 1, 0, 1}
};

// Exibindo o texto "GAMEOVER" nas áreas jogáveis:
int show_gameover_screen(void){
    int screen_row_player1 = 9;  // Linha inicial do "GAMEOVER" do jogador 1.
    int screen_row_player2 = 37; // Linha inicial do "GAMEOVER" do jogador 2.
    int screen_column = 9;       // Coluna inicial do "GAMEOVER" de ambos os jogadores.
    // "Upscaling" do texto "GAMEOVER":
    for(int row = 0; row < 6; row++){
        for(int row_increment = 0; row_increment < 2; row_increment++){
            for(int column = 0; column < 31; column++){
                for(int column_increment = 0; column_increment < 3; column_increment++){
                    if(game_over_screen[row][column] == 1){
                        // Área jogável do jogador 1:
                        if(player1_gameover){
                            buffer_overflow();
                            background_drawing(row+screen_row_player1+row_increment, column+screen_column+column_increment, COLOR_ORANGE);
                        }
                        // Área jogável do jogador 2:
                        if(player2_gameover){
                            buffer_overflow();
                            background_drawing(row+screen_row_player2+row_increment, column+screen_column+column_increment, COLOR_ORANGE);
                        }
                    }
                }
                screen_column += 1; // Próximo conjunto de colunas.
            }
            screen_column = 9;      // Restaurando a posição da coluna inicial.
        }
        screen_row_player1 += 1;    // Próximo conjunto de linhas da área do jogador 1.
        screen_row_player2 += 1;    // Próximo conjunto de linhas da área do jogador 2.
    }
    return 0;
}
