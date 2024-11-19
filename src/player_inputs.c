// Funções relacionadas as entradas de movimentação dos jogadores:

#include "player_inputs.h"

// Sensibilidade de movimento do sprite do jogador 1:
float accelerometerSensitivity = 0.005;

// Arquivo que acessa os eventos de entrada do Linux:
int fd_event;

// Armazena o valor do eixo Y do mouse:
int mouse_y_axis = 0;

/**
* Lendo a saída do eixo X do acelerômetro:
* O movimento horizontal do eixo X, será convertido para movimento vertical do jogador 1.
*/
void* check_player1_input(void* arg){
    while(!player1_gameover){
        int16_t x_axis = read_x(); // Lendo o valor do eixo X do acelerômetro "ADXL345".
        /**
        * Convertendo a coordenada de linha do sprite para coordenada de linha do background,
        * para verificar se houve colisão com as margens verticais da área do jogador 1.
        */
        int player1_bg_row = sp_row_to_bg_row(player1_row_sprite);
        // Movimentando o sprite do jogador 1, de acordo com as medições do eixo X: 
        player1_bg_row += x_axis * accelerometerSensitivity;       // Incrementando a coordenada de linha.
        // Verificando se não saiu da área jogável:
        if(player1_bg_row >= 4 && player1_bg_row < 27 && (x_axis > 200 || x_axis < -200))
            player1_row_sprite = bg_row_to_sp_row(player1_bg_row); // Atualizando o valor de linha do sprite;
        usleep(100 * 1000);
    }
    return NULL;
}

// Verificando os botões "KEY" como entradas que alteram o fluxo do jogo:
// CORRIGIR
void check_buttons(void){
    // Pausando o jogo ao pressionar o botão 2 (KEY1) e retomando ao pressionar botão 1 (KEY0):
    // if(read_keys() == 2){
    //     int on_pause = 1;
    //     while(on_pause){
    //         if(read_keys() == 1)
    //             on_pause = 0;
    //     }
    // }
    // // Reiniciando o jogo ao pressionar o botão 3 (KEY2):
    // if(read_keys() == 3){
    //     clean_screen(); // Limpando a tela.
    //     // Reposicionando os "sprites" dos jogadores:
    //     player1_row_sprite = 120;
    //     player2_row_sprite = 344;
    //     set_players();
    //     // Resetando e exibindo os pontos dos jogadores:
    //     score_player1 = 0;
    //     score_player2 = 0;
    //     show_score();
    //     // Resetando e exibindo as vidas dos jogadores:
    //     for(int selected_player = 0; selected_player < 2; selected_player++){
    //         for(int selected_live = 0; selected_live < 3; selected_live++){
    //             lives[selected_player][0][selected_live] = 1;
    //         }
    //     }
    //     show_lives();
    //     displacement_speed = 150; // Resetando a velocidade de deslocamento dos canos.
    //     //in_loop = 0;              // Reiniciando o "loop" de deslocamento dos canos.
    // }
    // // Forçando a saída do jogo ao pressionar o botão 4 (KEY3):
    // if(read_keys() == 4){
    //     player1_gameover = 1;
    //     player2_gameover = 1;
    //     //in_loop = 0;
    // }
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

// Movimentando o sprite do jogador 2, de acordo com as leituras do eixo Y do mouse:
void* check_player2_input(void* arg){
    while(!player2_gameover){
        read_mouse_axis(); // Atualizando o valor do eixo Y do mouse.
        /**
        * Convertendo a coordenada de linha do sprite para coordenada de linha do background,
        * para verificar se houve colisão com as margens verticais da área do jogador 2.
        */
        int player2_bg_row = sp_row_to_bg_row(player2_row_sprite + mouse_y_axis); 
        // Movimentando o sprite do jogador 2, de acordo com as medições do eixo Y:    
        if(player2_bg_row >= 32 && player2_bg_row < 53)
            player2_row_sprite += mouse_y_axis;
    }
    return NULL;
}
