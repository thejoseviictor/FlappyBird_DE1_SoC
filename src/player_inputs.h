// Funções relacionadas as entradas de movimentação dos jogadores:

#ifndef PLAYER_INPUTS_H
#define PLAYER_INPUTS_H

// Chamadas das Bibliotecas:
#include "ADXL345.h"
#include "game_features.h"
#include "linux/input.h"

// Variáveis que serão usadas em outras bibliotecas:
extern int fd_event;

// Cabeçalho das Funções:
void* check_buttons(void* arg);
void linux_event_file(void);
void read_mouse_axis(void);
void* check_player1_input(void* arg);
void* check_player2_input(void* arg);

#endif // PLAYER_INPUTS_H
