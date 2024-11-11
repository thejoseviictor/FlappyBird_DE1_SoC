// Funções relacionadas aos recursos de jogabilidade do jogo:

#ifndef GAME_FEATURES_H
#define GAME_FEATURES_H

// Chamadas das Bibliotecas:
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "vga.h"
#include "ADXL345.h"

// Variáveis que serão usadas em outras bibliotecas:
extern int player1_gameover;
extern int player2_gameover;

// Cabeçalho das Funções:
int set_game_background(void);
int clean_screen(void);
int show_background(void);
int show_clouds(int column_pipe1, int column_pipe2);
int show_lives(void);
int set_players(void);
int set_pipe(void);
int sp_row_to_bg_row(int sp_row);
int sp_column_to_bg_column(int sp_column);
int bg_row_to_sp_row(int bg_row);
int bg_column_to_sp_column(int bg_column);
int player_pipe_collision(void);
int player_ground_collision(void);
int show_score(void);
int check_player1_input(void);

#endif // GAME_FEATURES_H
