#include "game_features.h"

/**
* Equivalências de Coordenadas:
* Sprite no Centro da Tela: row(240) e column(320)
* Bloco do Background no Centro da Tela: row(30) e column(40)
* Fórmulas das Correspondências:
* sp_equivalent_row = (bg_row * 240) / 30;          // Corresponde de linha do background em linha do sprite
* sp_equivalent_column = (bg_column * 320) / 40;    // Corresponde de coluna do background em coluna do sprite
* bg_equivalent_row = (sp_row * 30) / 240;          // Corresponde de linha do sprite em linha do background
* bg_equivalent_column = (sp_column * 40) / 320;    // Corresponde de coluna do sprite em coluna do background
*/

/**
* Dimensões:
* Sprites: 20x20 pixels
* Margem superior: 4 blocos, rows[0:3]
* Área do Jogador 1: 24 blocos, rows[4:27]
* Margem central: 4 blocos, rows[28:31]
* Área do Jogador 2: 24 blocos, rows[32:55]
* Margem inferior: 4 blocos, rows[56:59]
*/

/**
* Posições Iniciais dos Jogadores: 
* Jogador 1 - row(15) e column (20)
* Jogador 2 - row(43) e column (20)
*/ 
int player1_row_sprite = 120;    // Posição inicial de linha do jogador 1.
int player2_row_sprite = 344;    // Posição inicial de linha do jogador 2.
int players_column_sprite = 160; // Posição inicial de coluna de ambos os jogadores.

/**
* Vetor bidimensional que armazena os valores do background,
* como: posições das nuvens e posições dos canos.
*/
int background[60][80];

/** 
* Vetores bidimensionais que armazenam os layouts dos canos:
* Uma linha desse vetor ocupa três coordenadas de linha
* e uma coluna ocupa quatro coordenadas de coluna no VGA
*/
int pipes[3][8][1] = {
    {{1},
     {0},
     {0},
     {1},
     {1},
     {1},
     {1},
     {1}},
    {{1},
     {1},
     {1},
     {0},
     {0},
     {1},
     {1},
     {1}},
    {{1},
     {1},
     {1},
     {1},
     {1},
     {0},
     {0},
     {1}}
};

// Armazenando a pontuação de cada jogador (máximo: 67 pontos):
int score_player1 = 0;
int score_player2 = 0;

// Armazena a quantidade de vidas de cada jogador:
int lives[2][1][3] = {
    {1, 1, 1}, // Jogador 1
    {1, 1, 1}  // Jogador 2
};

// Um índice que aponta para a posição atual da vida de cada jogador:
int player1_live_pointer = 2;
int player2_live_pointer = 2;

// Armazenam o estado de "game over" dos jogadores:
int player1_gameover = 0;
int player2_gameover = 0;

// Armazena os registradores dos sprites dos jogadores:
int player1_register = 20;
int player2_register = 21;

// Armazena os registradores dos sprites das vidas dos jogadores:
int heart_sp_offset = 15; // Offset do sprite de coração na memória.
// Vidas do jogador 1:
int player1_live1_register = 22;
int player1_live2_register = 23;
int player1_live3_register = 24;
// Vidas do jogador 2:
int player2_live1_register = 25;
int player2_live2_register = 26;
int player2_live3_register = 27;

// Velocidade de deslocamento dos canos, que será decrementada de acordo com os pontos:
int displacement_speed = 150;

// Níveis de jogo, no máximo 14, que serão incrementados após os canos finalizarem um deslocamento completo:
int game_level = 0;

// Sensibilidade de movimento do sprite do jogador 1, de acordo com o acelerômetro:
int accelerometerSensitivity = 1800;

// Limpando o vetor bidimensional e removendo os canos anteriores da tela:
int set_game_background(void){
    for(int row = 0; row < 60; row++){
        for(int column = 0; column < 80; column++){
            if(background[row][column] == 1){
                buffer_overflow();
                background_block_erase(row, column);
            }
            background[row][column] = 0;
        }
    }
    return 0;
}

// Removendo todos os blocos de background, polígonos e sprites na tela:
int clean_screen(void){
    // Removendo os blocos de background:
    for(int row = 0; row < 60; row++){
        for(int column = 0; column < 80; column++){
            buffer_overflow();
            background_block_erase(row, column);
        }
    }
    // // Removendo os polígonos e sprites:
    for(int address = 0; address < 32; address++){
        buffer_overflow();
        draw_polygon(address, 0, 0, 0, COLOR_WHITE, 0);
        if(address > 0)
            set_sprite(address, 0, 0, 0, 0);
    }
    return 0;
}

/**
* Exibindo os elementos na tela:
* Correspondências dos valores no vetor bidimensional:
* 1 - Cano
* 2 - Pontos
*/
int show_background(void){
    // system("clear"); // Para o terminal (remover);
    for(int row = 0; row < 60; row++){
        for(int column = 0; column < 80; column++){ 
            // Exibindo os canos: 
            if(background[row][column] == 1){
                buffer_overflow();
                background_drawing(row, column, COLOR_GREEN);
            }
            // Exibindo os pontos:
            else if(background[row][column] == 2){
                buffer_overflow();
                background_drawing(row, column, COLOR_YELLOW);
            }
            // Exibindo as margens:
            if(row < 4 || (row >= 28 && row < 32) || row >= 56){
                // Verifica se há pontos sendo exibidos naquela posição:
                if(background[row][column] != 2){
                    buffer_overflow();
                    background_drawing(row, column, COLOR_BLACK);
                }
            }
            // printf("%i", background[row][column]); // Para o terminal (remover);
        }
        // printf("\n"); // Para o terminal (remover);
    }
    return 0;
}

// Exibe nuvens aleatórias nas áreas dos jogadores, usando polígonos:
// NÃO ESTÁ FUNCIONANDO AINDA:
int show_clouds(int column_pipe1, int column_pipe2){
    // Randomizando alguns parâmetros da nuvem 1:
    int cloud1_row_player1 = 10 + (rand() % 12); // Range usado da área do jogador 1: row[10:21]
    int cloud1_row_player2 = 38 + (rand() % 12); // Range usado da área do jogador 2: row[38:49]
    int cloud1_size = 1 + (rand() % 8);
    int cloud1_type = rand() % 2;
    // Randomizando alguns parâmetros da nuvem 2:
    int cloud2_row_player1 = 10 + (rand() % 12); // Range usado da área do jogador 1: row[10:21]
    int cloud2_row_player2 = 38 + (rand() % 12); // Range usado da área do jogador 2: row[38:49]
    int cloud2_size = 1 + (rand() % 8);
    int cloud2_type = rand() % 2;
    // Exibindo a nuvem 1 nas áreas dos jogadores:
    // if(column_pipe1 >= 10){
    //     draw_polygon(16, cloud1_row_player1, bg_column_to_sp_column(column_pipe1)-10, cloud1_size, COLOR_WHITE, cloud1_type);
    //     draw_polygon(17, cloud1_row_player2, bg_column_to_sp_column(column_pipe1)-10, cloud1_size, COLOR_WHITE, cloud1_type);
    // }
    // // Removendo a nuvem 1, se ela atingir a borda esquerda da tela:
    // else{
    //     draw_polygon(16, cloud1_row_player1, 0, 0, COLOR_WHITE, cloud1_type);
    //     draw_polygon(17, cloud1_row_player2, 0, 0, COLOR_WHITE, cloud1_type);
    // }
    // // Exibindo a nuvem 2 nas áreas dos jogadores:
    // if(column_pipe2 >= 10){
    //     draw_polygon(18, cloud2_row_player1, bg_column_to_sp_column(column_pipe2)-10, cloud2_size, COLOR_WHITE, cloud2_type);
    //     draw_polygon(19, cloud2_row_player2, bg_column_to_sp_column(column_pipe2)-10, cloud2_size, COLOR_WHITE, cloud2_type);
    // }
    // // Removendo a nuvem 2, se ela atingir a borda esquerda da tela:
    // else
    //     draw_polygon(18, cloud2_row_player1, 0, 0, COLOR_WHITE, cloud2_type);
    //     draw_polygon(19, cloud2_row_player2, 0, 0, COLOR_WHITE, cloud2_type);
    return 0;
}

// Exibindo as vidas dos jogadores na tela, usando o sprite de coração:
int show_lives(void){
    // Vidas do jogador 1:
    int player1_live_row = bg_row_to_sp_row(1);
    buffer_overflow();
    set_sprite(player1_live1_register, heart_sp_offset, player1_live_row, bg_column_to_sp_column(1), lives[0][0][0]);
    set_sprite(player1_live2_register, heart_sp_offset, player1_live_row, bg_column_to_sp_column(5), lives[0][0][1]);
    set_sprite(player1_live3_register, heart_sp_offset, player1_live_row, bg_column_to_sp_column(9), lives[0][0][2]);
    // Vidas do jogador 2:
    int player2_live_row = bg_row_to_sp_row(29);
    buffer_overflow();
    set_sprite(player2_live1_register, heart_sp_offset, player2_live_row, bg_column_to_sp_column(1), lives[1][0][0]);
    set_sprite(player2_live2_register, heart_sp_offset, player2_live_row, bg_column_to_sp_column(5), lives[1][0][1]);
    set_sprite(player2_live3_register, heart_sp_offset, player2_live_row, bg_column_to_sp_column(9), lives[1][0][2]);
    return 0;
}

// Posicionando e atualizando os sprites dos jogadores na tela:
int set_players(void){
    // Ativando e atualizando a posição do sprite do jogador 1:
    if(player1_gameover != 1)
        set_sprite(player1_register, 0, player1_row_sprite, players_column_sprite, 1);
    // Desativando o sprite do jogador 1, em caso de "game-over":
    else
        set_sprite(player1_register, 0, player1_row_sprite, players_column_sprite, 0);
    // Ativando e atualizando a posição do sprite do jogador 2:
    if(player2_gameover != 1)
        set_sprite(player2_register, 1, player2_row_sprite, players_column_sprite, 1);
    // Desativando o sprite do jogador 2, em caso de "game-over":
    else
        set_sprite(player2_register, 1, player2_row_sprite, players_column_sprite, 0);
    return 0;
}

/**
* Lógica para colocar os canos na matriz e deslocá-los
* linha repete 3 vezes
* coluna repete 4 vezes
*/
int set_pipe(void){
    int select_pipe1 = rand() % 3; // Seleciona o cano que será exibido
    int select_pipe2 = rand() % 3; // Seleciona o cano que será exibido
    int row_player1 = 4;           // Armazena o início das linhas da área jogável do jogador 1 no VGA.
    int row_player2 = 32;          // Armazena o início das linhas da área jogável do jogador 2 no VGA.
    int column_pipe1 = 79;         // Armazena o início das colunas da área jogável do jogador 1 no VGA.
    int column_pipe2 = 79;         // Armazena o início das colunas da área jogável do jogador 2 no VGA.
    int in_loop = 1;               // Se mantém no loop até os canos terminarem de se deslocar.
    int enable_pipe2 = 0;          // Permite desenhar o cano 2, quando houver uma margem de 49 blocos de distância do cano 1.
    int wait_next_pipe_player1 = 0;// Lembra que já houve colisão com um cano específico, quando o jogador 1 colide com o seu bloco no background.
    int wait_next_pipe_player2 = 0;// Lembra que já houve colisão com um cano específico, quando o jogador 2 colide com o seu bloco no background.
    while(in_loop){
        // Limpando o vetor bidimensional e removendo os canos anteriores da tela:
        if(in_loop != 0)
            set_game_background();
        // Percorrendo o vetor bidimensional dos canos, e imprimindo eles na tela com uma escala maior:
        for(int pipe_row = 0; pipe_row < 8; pipe_row++){
            for(int row_increment = 0; row_increment < 3; row_increment++){
                for(int column_increment = 0; column_increment < 4; column_increment++){
                    // Exibindo o cano 1 em uma escala maior:
                    if(pipes[select_pipe1][pipe_row][0] == 1 && column_pipe1 != -1 && (column_pipe1+column_increment < 80)){
                        background[row_player1+row_increment][column_pipe1+column_increment] = 1;
                        background[row_player2+row_increment][column_pipe1+column_increment] = 1;
                    }
                    // Margem de 40 blocos, para habilitar o cano 2:
                    if(column_pipe1 < 40)
                        enable_pipe2 = 1;
                    // Exibindo o cano 2 em uma escala maior:
                    if(enable_pipe2 && pipes[select_pipe2][pipe_row][0] == 1 && column_pipe2 != -1 && (column_pipe2+column_increment < 80)){
                        background[row_player1+row_increment][column_pipe2+column_increment] = 1;
                        background[row_player2+row_increment][column_pipe2+column_increment] = 1;
                    }
                }
            }
            // Pula para o início da próxima linha na tela, respeitando a área jogável de cada player:
            if(row_player1 <= 25)
                row_player1 += 3;
            if(row_player2 <= 53)
                row_player2 += 3;
        }
        show_background();                 // Exibindo os novos canos na tela.
        usleep(displacement_speed * 1000); // Tempo de deslocamento dos canos.
        row_player1 = 4;                   // Resetando o valor de início das linhas do jogador 1 no VGA.
        row_player2 = 32;                  // Resetando o valor de início das linhas do jogador 2 no VGA.
        // Decrementa a vida dos jogadores, se houver colisão com um cano:
        if(player_pipe_collision() == 1 || player_pipe_collision() == 3)
            if(player1_live_pointer != -1 && wait_next_pipe_player1 == 0){
                lives[0][0][player1_live_pointer] = 0; // Removendo uma vida.
                player1_live_pointer--;                // Decrementando o índice da vida.
                wait_next_pipe_player1 = 4;            // Incrementado para esperar o próximo cano.
            }
        if(player_pipe_collision() == 2 || player_pipe_collision() == 3)
            if(player2_live_pointer != -1 && wait_next_pipe_player2 == 0){
                lives[1][0][player2_live_pointer] = 0; // Removendo uma vida.
                player2_live_pointer--;                // Decrementando o índice da vida.
                wait_next_pipe_player2 = 4;            // Incrementado para esperar o próximo cano.
            }
        // Declarando o "game over" dos jogadores e removendo os seus sprites, caso haja colisão com o chão ou ao zerar todas as vidas:
        if(player_ground_collision() == 1 || lives[0][0][0] == 0)
            player1_gameover = 1;
        if(player_ground_collision() == 2 || lives[1][0][0] == 0)
            player2_gameover = 1;
        // Incrementando os pontos dos jogadores ao passar por um cano, exceto quando houve colisão:
        if((column_pipe1 == 18 || column_pipe2 == 18) && !player1_gameover && wait_next_pipe_player1 == 0 && score_player1 < 67)
            score_player1++;
        if((column_pipe1 == 18 || column_pipe2 == 18) && !player2_gameover && wait_next_pipe_player2 == 0 && score_player1 < 67)
            score_player2++;
        // Deslocando as colunas para a esquerda:
        if(column_pipe1 != -1)
            column_pipe1--;    // Deslocando a coluna do cano 1 para a esquerda.
        if(enable_pipe2)
            column_pipe2--;    // Deslocando a coluna do cano 2 para a esquerda.
        // Usados para evitar que os jogadores colidam mais de uma vez com o mesmo cano:
        if(wait_next_pipe_player1 >= 1)
            wait_next_pipe_player1--; // Decrementa a cada deslocamento, até o cano ultrapassar o jogador 1.
        if(wait_next_pipe_player2 >= 1)
            wait_next_pipe_player2--; // Decrementa a cada deslocamento, até o cano ultrapassar o jogador 2.
        /**
        * Condições de saída da função: 
        * O cano 2 alcançou a borda esquerda da tela.
        * Ou "game_over" de ambos os jogadores.
        */ 
        if(column_pipe2 == -1 || (player1_gameover && player2_gameover)){
            in_loop = 0;                  // Desativa o loop de deslocamento dos canos.
            if(game_level < 14)
                game_level++;             // Incrementa o nível de jogo.
            if(displacement_speed != 10)
                displacement_speed -= 10; // Decrementa o tempo de deslocamento dos canos.
        }
        // Exibindo a pontuação na tela:
        if(score_player1 > 0 || score_player2 > 0)
            show_score();
        show_clouds(column_pipe1, column_pipe2); // Exibindo as nuvens.
        show_lives();                            // Exibindo as vidas dos jogadores.
        check_player1_input();                   // Verificando se há entradas do jogador 1.
        set_players();                           // Atualizando as posições dos jogadores.
        show_background();
    }
    return 0;
}

// Converte a coordenada de linha do sprite/polígono para a coordenada de linha correspondente no background:
int sp_row_to_bg_row(int sp_row){
    return ((sp_row * 30) / 240);
}

// Converte a coordenada de coluna do sprite/polígono para a coordenada de coluna correspondente no background:
int sp_column_to_bg_column(int sp_column){
    return ((sp_column * 40) / 320);
}

// Converte a coordenada de linha do background para a coordenada de linha correspondente no sprite/polígono:
int bg_row_to_sp_row(int bg_row){
    return ((bg_row * 240) / 30);
}

// Converte a coordenada de coluna do background para a coordenada de coluna correspondente no sprite/polígono:
int bg_column_to_sp_column(int bg_column){
    return ((bg_column * 320) / 40);
}

/*
* Verifica se há um cano no bloco a direita dos jogadores.
* Se sim, haverá colisão.
*/
int player_pipe_collision(void){
    int player1_collision = 0;    // Armazena o valor da colisão do jogador 1;
    int player2_collision = 0;    // Armazena o valor da colisão do jogador 2;
    if(background[sp_row_to_bg_row(player1_row_sprite)][sp_column_to_bg_column(players_column_sprite)+1] == 1)
        player1_collision = 1;    // Atualiza o valor da colisão do jogador 1;
    if(background[sp_row_to_bg_row(player2_row_sprite)][sp_column_to_bg_column(players_column_sprite)+1] == 1)
        player2_collision = 2;    // Atualiza o valor da colisão do jogador 2;
    if(player1_collision == 1 && player2_collision == 0)
        return player1_collision; // Apenas o jogador 1 colidiu com o cano;
    else if(player1_collision == 0 && player2_collision == 2)
        return player2_collision; // Apenas o jogador 2 colidiu com o cano;
    else if(player1_collision == 1 && player2_collision == 2)
        return 3;                 // Ambos os jogadores colidiram com os canos;
    else
        return 0;                 // Nenhum dos jogadores colidiu com algum cano;
}

// Verifica se os jogadores atingiram o "chão" de suas respectivas áreas jogáveis:
int player_ground_collision(void){
    int player1_collision = 0;    // Armazena o valor da colisão do jogador 1;
    int player2_collision = 0;    // Armazena o valor da colisão do jogador 2;
    if(sp_row_to_bg_row(player1_row_sprite) >= 27) // Coordenadas do "chão" da área jogável do jogador 1
        player1_collision = 1;    // Atualiza o valor da colisão do jogador 1;
    if(sp_row_to_bg_row(player2_row_sprite) >= 55) // Coordenadas do "chão" da área jogável do jogador 2
        player2_collision = 2;    // Atualiza o valor da colisão do jogador 2;
    if(player1_collision == 1 && player2_collision == 0)
        return player1_collision; // Apenas o jogador 1 colidiu com o "chão";
    else if(player1_collision == 0 && player2_collision == 2)
        return player2_collision; // Apenas o jogador 2 colidiu com o "chão";
    else if(player1_collision == 1 && player2_collision == 2)
        return 3;                 // Ambos os jogadores colidiram com o seus "chãos";
    else
        return 0;                 // Nenhum dos jogadores colidiu com algum "chão";
}

// Exibe os pontos dos jogadores em pontos do vetor bidimensional, que será exibido na tela.
int show_score(void){
    // Só será possível exibir "34" pontos em uma linha, então pontuações maiores
    // que "34" serão armazenadas em duas variáveis e exibidas em duas linhas.
    if(score_player1 > 34 || score_player2 > 34){
        // Declarando as variáveis que irão armazenar as metades:
        int score_player1_fhalf = 0;
        int score_player1_shalf = 0;
        int score_player2_fhalf = 0;
        int score_player2_shalf = 0;
        // Alterando os valores das variáveis que armazenam as metades:
        if(score_player1 > 34){
            score_player1_fhalf = 34;
            score_player1_shalf = score_player1 - 34;
        }
        if(score_player2 > 34){
            score_player2_fhalf = 34;
            score_player2_shalf = score_player2 - 34;
        }
        // Exibindo a primeira metade dos pontos:
        for(int column = 13; column < 80; column++){
            if(column % 2 == 1){
                // Pontos do jogador 1:
                if(score_player1_fhalf != 0){
                    background[1][column] = 2; // Os pontos serão armazenados com o valor "2" no vetor bidimensional.
                    score_player1_fhalf--;     // Decrementando a variável temporária dos pontos.
                }
                // Pontos do jogador 2:
                if(score_player2_fhalf != 0){
                    background[29][column] = 2; // Os pontos serão armazenados com o valor "2" no vetor bidimensional.
                    score_player2_fhalf--;      // Decrementando a variável temporária dos pontos.
                }
            }
            // Indica que todos os pontos já foram exibidos, forçando a saída do "for".
            if(score_player1_fhalf == 0 && score_player2_fhalf == 0)
                column = 80;
        }
        // Exibindo a segunda metade dos pontos:
        for(int column = 13; column < 80; column++){
            if(column % 2 == 0){
                // Pontos do jogador 1:
                if(score_player1_shalf != 0){
                    background[2][column] = 2; // Os pontos serão armazenados com o valor "2" no vetor bidimensional.
                    score_player1_shalf--;     // Decrementando a variável temporária dos pontos.
                }
                // Pontos do jogador 2:
                if(score_player2_shalf != 0){
                    background[30][column] = 2; // Os pontos serão armazenados com o valor "2" no vetor bidimensional.
                    score_player2_shalf--;      // Decrementando a variável temporária dos pontos.
                }
            }
            // Indica que todos os pontos já foram exibidos, forçando a saída do "for".
            if(score_player1_shalf == 0 && score_player2_shalf == 0)
                column = 80;
        }
    }
    // Uma pontuação menor ou igual a "34" será exibida em uma linha da tela:
    else{
        // Os "temps" serão decrementados para evitar que o "for" exiba mais pontos do que o necessário na tela.
        int score_temp1 = score_player1; 
        int score_temp2 = score_player2;
        // Percorrendo as colunas e exibindo os pontos:
        for(int column = 13; column < 80; column++){
            if(column % 2 == 1){
                // Pontos do jogador 1:
                if(score_temp1 != 0){
                    background[1][column] = 2; // Os pontos serão armazenados com o valor "2" no vetor bidimensional.
                    score_temp1--;             // Decrementando a variável temporária dos pontos.
                }
                // Pontos do jogador 2:
                if(score_temp2 != 0){
                    background[29][column] = 2; // Os pontos serão armazenados com o valor "2" no vetor bidimensional.
                    score_temp2--;             // Decrementando a variável temporária dos pontos.
                }
            }
            // Indica que todos os pontos já foram exibidos, forçando a saída do "for".
            if(score_temp1 == 0 && score_temp2 == 0)
                column = 80;
        }
    }
    return 0;
}

// Lê a entrada do eixo X do acelerômetro, que corresponde ao movimento vertical do jogador 1:
// NÃO ESTÁ FUNCIONANDO AINDA:
int check_player1_input(void){
    int16_t x_axis = read_x(); // Lendo o valor do eixo X do acelerômetro ADXL345.
    printf("Eixo X: %i\n", x_axis);
    // Convertendo a coordenada de linha do sprite para coordenada de linha de background:
    int player1_bg_row = sp_row_to_bg_row(player1_row_sprite);
    // Movimenta dinâmicamente o sprite no sentido norte, para valores do eixo X maiores que 100:
    if(x_axis > 100 && player1_bg_row > 4)
        // Verificando o limite superior:
        if((player1_bg_row -= x_axis/accelerometerSensitivity) > 4)
            player1_row_sprite = bg_row_to_sp_row(player1_bg_row); // Atualizando a posição do jogador 1.
    // Movimenta dinâmicamente o sprite no sentido sul, para valores do eixo X menores que 100:
    else if(x_axis < -100 && player1_bg_row < 28)
        // Verificando o limite inferior:
        if((player1_bg_row += x_axis/accelerometerSensitivity) < 28)
            player1_row_sprite = bg_row_to_sp_row(player1_bg_row); // Atualizando a posição do jogador 1.
    return 0;
}
