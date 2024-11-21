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
#include "GPIO.h"
#include "player_inputs.h"

// Variáveis que serão usadas em outras bibliotecas:
extern int player1_sp_offset;
extern int player2_sp_offset;
extern int player1_gameover;
extern int player2_gameover;
extern int player1_row_sprite;
extern int player2_row_sprite;
extern int score_player1;
extern int score_player2;
extern int lives[2][1][3];
extern int displacement_speed;
extern int in_loop;
extern int on_pause;

// Cabeçalho das Funções:
int set_game_background(void);
int clean_screen(void);
int show_background(void);
void* show_clouds(void* arg);
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

#endif // GAME_FEATURES_H
