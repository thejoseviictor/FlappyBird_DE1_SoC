// Para criar e armazenar os sprites do "Flappy Bird":

#ifndef SPRITES_H
#define SPRITES_H

// Chamadas das Bibliotecas:
#include "game_features.h"
#include "vga.h"

// Cabeçalho das Funções:
int sprite_builder(int offset, const int sprite_array[20][20]);
int flappy_bird_sprites(void);
void* sp_animation(void* arg);

#endif // SPRITES_H
