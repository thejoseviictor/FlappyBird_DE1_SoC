// Funções relacionadas as entradas de movimentação dos jogadores:

#include "player_inputs.h"

// Arquivo que acessa os eventos de entrada do Linux:
int fd_event;

// Armazena o valor do eixo Y do mouse:
int mouse_y_axis = 0;

// Para finalizar o processo do jogo:
bool game_exit = false;

// Armazenando as cores do background e "GAMEOVER":
int bg_color = COLOR_CYAN;
int game_over_color = COLOR_ORANGE;

// Verificando os botões "KEY" como entradas que alteram o fluxo do jogo:
void* check_buttons(void* arg){
    while(!game_exit){
        // Pausando o jogo ao pressionar o botão 2 (KEY1):
        if(read_keys() == 2)
            on_pause = 1;
        // Retomando o jogo ao pressionar o botão 1 (KEY0):
        if(read_keys() == 1)
            on_pause = 0;
        // Reiniciando o jogo ao pressionar o botão 3 (KEY2):
        if(read_keys() == 3){
            // Restaurando o "GAMEOVER":
            player1_gameover = 0;
            player2_gameover = 0;
            // Reposicionando os "sprites" dos jogadores:
            player1_row_sprite = 120;
            player2_row_sprite = 344;
            set_players();
            // Resetando os pontos dos jogadores:
            score_player1 = 0;
            score_player2 = 0;
            // Resetando as vidas dos jogadores:
            for(int selected_player = 0; selected_player < 2; selected_player++){
                for(int selected_live = 0; selected_live < 3; selected_live++){
                    lives[selected_player][0][selected_live] = 1;
                }
            }
            player1_live_pointer = 2;  // Resetando o ponteiro do índice das vidas do jogador 1.
            player2_live_pointer = 2;  // Resetando o ponteiro do índice das vidas do jogador 2.
            displacement_speed = 1000; // Resetando a velocidade de deslocamento dos canos.
            pipe_loop = 0;             // Reiniciando o "loop" de deslocamento dos canos.
            clean_screen();            // Limpando a tela.
            set_game_background();     // Limpando o array bidimensional da pontuação.
            render_background();       // Renderizando as bordas e a pontuação novamente.
            // Invertendo as cores do background e "GAMEOVER":
            if(bg_color == COLOR_CYAN){
                bg_color = COLOR_ORANGE;      // Salvando o valor da nova cor do background.
                background_color(bg_color);   // Alterando a cor do background.
                game_over_color = COLOR_CYAN; // Alterando a cor do "GAMEOVER".
            }
            else{
                bg_color = COLOR_CYAN;
                background_color(bg_color);
                game_over_color = COLOR_ORANGE; // Alterando a cor do "GAMEOVER".
            }
        }
        // Forçando a saída do jogo ao pressionar o botão 4 (KEY3):
        if(read_keys() == 4){
            game_exit = true;
            player1_gameover = 1;
            player2_gameover = 1;
        }
    }
    return NULL;
}

// Abrindo o arquivo que dá acesso aos eventos de entrada no Linux:
void linux_event_file(void){
    fd_event = open("/dev/input/event0", O_RDONLY); // Devemos descobrir o endereço do evento do mouse.
    if(fd_event == -1)
        printf("Falha ao acessar os dispositivos de entrada!");
}

// Lendo o evento do Linux que armazena o valor do eixo Y do mouse:
void read_mouse_axis(void){
    struct input_event event; // Criando uma variável do tipo "input_event".
    // Lendo o evento e armazenando o seu valor:
    ssize_t n = read(fd_event, &event, sizeof(struct input_event));
    if(n == sizeof(struct input_event)){
        if(event.type == EV_REL && event.code == REL_Y){
            mouse_y_axis = event.value;
        }
    }
}

// O movimento horizontal do eixo X do acelerômetro, será convertido para movimento vertical do jogador 1.
void* check_player1_input(void* arg){
    int16_t last_x = read_x(); // Vai armazenar o valor de eixo X no estado anterior.
    while(!game_exit){
        int16_t x_axis = read_x(); // Lendo o valor do eixo X do acelerômetro "ADXL345".
        /**
        * Convertendo a coordenada de linha do sprite para coordenada de linha do background,
        * para verificar se houve colisão com as margens verticais da área do jogador 1.
        */
        int player1_bg_row = sp_row_to_bg_row(player1_row_sprite + (x_axis / 10));
        // Verificando se não saiu da área jogável:
        if(player1_bg_row >= 4 && player1_bg_row < 26 && x_axis != last_x && (x_axis < -10 || x_axis > 10)){
            player1_row_sprite += x_axis / 10; // Atualizando o valor de linha do sprite;
            set_players();                     // Atualizando as posições dos sprites dos jogadores.
        }
        last_x = x_axis;   // Salvando o valor do eixo X neste estado.
        while(on_pause){}  // Estado de pausa do jogo.
    }
    return NULL;
}

// O jogador 2 irá se movimentar de acordo com os eventos do eixo vertical Y do mouse.
void* check_player2_input(void* arg){
    while(!game_exit){
        read_mouse_axis(); // Atualizando o valor do eixo Y do mouse.
        /**
        * Convertendo a coordenada de linha do sprite para coordenada de linha do background,
        * para verificar se houve colisão com as margens verticais da área do jogador 2.
        */
        int player2_bg_row = sp_row_to_bg_row(player2_row_sprite + mouse_y_axis); 
        // Movimentando o sprite do jogador 2, de acordo com as medições do eixo Y:    
        if(player2_bg_row >= 32 && player2_bg_row < 54){
            player2_row_sprite += mouse_y_axis;
            set_players(); // Atualizando as posições dos sprites dos jogadores.
        }
        while(on_pause){}  // Estado de pausa do jogo.
    }
    return NULL;
}
