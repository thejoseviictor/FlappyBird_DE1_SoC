// Funções relacionadas aos recursos de jogabilidade do jogo:

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

// Offsets dos sprites dos jogadores:
int player1_sp_offset;
int player2_sp_offset;

/**
* Array bidimensional que armazena os elementos do background,
* como bordas e posições dos pontos.
*/
int background[60][80];

// Armazenam as posições de linha dos polígonos dos canos nas áreas dos jogadores:
int pipe_rows_player1[6] = {6, 10, 14, 18, 22, 26};
int pipe_rows_player2[6] = {34, 38, 42, 46, 50, 54};

// Armazenando a pontuação de cada jogador (máximo: 67 pontos):
int score_player1 = 0;
int score_player2 = 0;

// Armazenando a quantidade de vidas de cada jogador:
int lives[2][1][3] = {
    {1, 1, 1}, // Jogador 1
    {1, 1, 1}  // Jogador 2
};

// Um índice que aponta para a posição atual da vida de cada jogador:
int player1_live_pointer = 2;
int player2_live_pointer = 2;

// Armazenam o estado de "GAMEOVER" dos jogadores:
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
int displacement_speed = 1000;

// Armazena o estado de pausa do jogo:
int on_pause = 0;

// Mantém o loop de exibição e deslocamento dos canos:
int pipe_loop = 0;

// Configurando o array bidimensional dos pontos e bordas:
int set_game_background(void){
    for(int row = 0; row < 60; row++){
        for(int column = 0; column < 80; column++){
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
            background_block_erase(row, column);
        }
    }
    // Removendo os polígonos e sprites:
    for(int address = 0; address < 32; address++){
        draw_polygon(address, 0, 0, 0, COLOR_WHITE, 0);
        if(address > 0)
            set_sprite(address, 0, 0, 0, 0);
    }
    return 0;
}

// Exibindo os pontos e bordas na tela:
int render_background(void){
    for(int row = 0; row < 60; row++){
        for(int column = 0; column < 80; column++){ 
            // Exibindo os pontos:
            if(background[row][column] == 1)
                background_drawing(row, column, COLOR_YELLOW);
            // Exibindo as bordas:
            if(row < 4 || (row >= 28 && row < 32) || row >= 56){
                // Verifica se há pontos sendo exibidos naquela posição:
                if(background[row][column] != 1)
                    background_drawing(row, column, COLOR_BLACK);
            }
        }
    }
    return 0;
}

// Exibindo as vidas dos jogadores na tela, usando o sprite de coração:
int show_lives(void){
    // Vidas do jogador 1:
    int player1_live_row = bg_row_to_sp_row(1);
    set_sprite(player1_live1_register, heart_sp_offset, player1_live_row, bg_column_to_sp_column(1), lives[0][0][0]);
    set_sprite(player1_live2_register, heart_sp_offset, player1_live_row, bg_column_to_sp_column(5), lives[0][0][1]);
    set_sprite(player1_live3_register, heart_sp_offset, player1_live_row, bg_column_to_sp_column(9), lives[0][0][2]);
    // Vidas do jogador 2:
    int player2_live_row = bg_row_to_sp_row(29);
    set_sprite(player2_live1_register, heart_sp_offset, player2_live_row, bg_column_to_sp_column(1), lives[1][0][0]);
    set_sprite(player2_live2_register, heart_sp_offset, player2_live_row, bg_column_to_sp_column(5), lives[1][0][1]);
    set_sprite(player2_live3_register, heart_sp_offset, player2_live_row, bg_column_to_sp_column(9), lives[1][0][2]);
    return 0;
}

// Posicionando e atualizando os sprites dos jogadores na tela:
int set_players(void){
    // Ativando e atualizando a posição do sprite do jogador 1:
    if(player1_gameover != 1)
        set_sprite(player1_register, player1_sp_offset, player1_row_sprite, players_column_sprite, 1);
    // Desativando o sprite do jogador 1, em caso de "GAMEOVER":
    else
        set_sprite(player1_register, player1_sp_offset, player1_row_sprite, players_column_sprite, 0);
    // Ativando e atualizando a posição do sprite do jogador 2:
    if(player2_gameover != 1)
        set_sprite(player2_register, player2_sp_offset, player2_row_sprite, players_column_sprite, 1);
    // Desativando o sprite do jogador 2, em caso de "GAMEOVER":
    else
        set_sprite(player2_register, player2_sp_offset, player2_row_sprite, players_column_sprite, 0);
    return 0;
}

// Renderizando as nuvens na tela:
void* render_clouds(void* arg){
    while(!game_exit){
        for(int cloud_column = 500; cloud_column >= 0; cloud_column--){
            // Desenhando duas nuvens, uma em cada área de jogo:
            if(cloud_column != 0){
                if(!player1_gameover)
                    draw_polygon(3, 110, cloud_column, 3, COLOR_WHITE, 0); // Registrador 3, na área do jogador 1.
                if(!player2_gameover)
                    draw_polygon(4, 334, cloud_column, 3, COLOR_WHITE, 0); // Registrador 4, na área do jogador 2.
            }
            // Removendo as nuvens, quando ambas chegarem na borda oeste:
            else{
                draw_polygon(3, 0, 0, 0, COLOR_WHITE, 0);
                draw_polygon(4, 0, 0, 0, COLOR_WHITE, 0);
            }
            usleep(1000); // Tempo de deslocamento das nuvens.
        }
    }
    return NULL;
}

/**
* Lógica para exibir e deslocar os canos usando polígonos (30x30):
* Cada cano terá cinco polígonos.
* A maioria da lógica do jogo depende dos canos.
*/
int set_pipe(void){
    int pipe_disabled_row = rand() % 6;  // Seleciona o índice da linha que será desativada nos canos.
    int pipe_column = 500;               // Coluna inicial dos canos.
    int pipe_draw_row = 6;               // Linha inicial do desenho do primeiro polígono, de cima para baixo.
    pipe_loop = 1;                       // Ativando o loop de deslocamento dos canos.
    // Desenhando e deslocando os canos, além das lógicas dependentes:
    while(pipe_loop && pipe_column >= 0){
        // Desenhando os canos nas áreas de ambos os jogadores:
        if(pipe_column >= 0){
            pipe_draw_row = 6; // Resetando a linha inicial do primeiro polígono.
            // Percorrendo os endereços dos polígonos dos canos, de 5 até 14.
            for(int address = 5; address < 15; address++){
                // Exibindo os canos:
                if(pipe_column != 0){
                    // Verificando o intervalo do endereço e o estado do "GAMEOVER", e desenhando o cano na área do jogador 1:
                    if(address <= 9 && !player1_gameover){
                        // Se não for uma posição desativada, desenhe o polígono nessa posição de linha:
                        if(pipe_draw_row != pipe_rows_player1[pipe_disabled_row])
                            draw_polygon(address, bg_row_to_sp_row(pipe_draw_row), pipe_column, 2, COLOR_GREEN, 0);
                        // Se for uma posição desativada, desenhe o polígono na posição de linha + 4;
                        else{
                            pipe_draw_row += 4; // Incrementando a linha, para a linha do próximo polígono.
                            draw_polygon(address, bg_row_to_sp_row(pipe_draw_row), pipe_column, 2, COLOR_GREEN, 0);
                        }
                        // Incrementando a linha, para a linha do próximo polígono:
                        pipe_draw_row += 4; 
                    }
                    // Verificando o intervalo do endereço e o estado do "GAMEOVER", e desenhando o cano na área do jogador 2:
                    if(address >= 10 && !player2_gameover){
                        if(pipe_draw_row != pipe_rows_player2[pipe_disabled_row])
                            draw_polygon(address, bg_row_to_sp_row(pipe_draw_row), pipe_column, 2, COLOR_GREEN, 0);
                        else{
                            pipe_draw_row += 4;
                            draw_polygon(address, bg_row_to_sp_row(pipe_draw_row), pipe_column, 2, COLOR_GREEN, 0);
                        }
                        pipe_draw_row += 4; 
                    }
                    // Pulando para a linha inicial do cano na área do jogador 2:
                    if(address+1 == 10)
                        pipe_draw_row = 34;
                }
                // Removendo os canos ao chegarem na sua última posição de coluna:
                else
                    draw_polygon(address, 0, 0, 0, COLOR_GREEN, 0);
            }
            pipe_column -= 5; // Decrementando suas colunas e deslocando os canos para a esquerda.
        }
        // Decrementa a vida dos jogadores, se houver colisão com os canos:
        int pipe_collision_state = player_pipe_collision(pipe_column, pipe_disabled_row);
        if(pipe_collision_state == 1 || pipe_collision_state == 3) // Colisão do jogador 1
            if(player1_live_pointer != -1){
                lives[0][0][player1_live_pointer] = 0; // Removendo uma vida.
                player1_live_pointer--;                // Decrementando o índice da vida.
            }
        if(pipe_collision_state == 2 || pipe_collision_state == 3) // Colisão do jogador 2
            if(player2_live_pointer != -1){
                lives[1][0][player2_live_pointer] = 0; // Removendo uma vida.
                player2_live_pointer--;                // Decrementando o índice da vida.
            }
        // Incrementando os pontos dos jogadores ao passar por um cano, exceto quando houver colisão:
        if(players_column_sprite+25 == pipe_column){
            if(!player1_gameover && (pipe_collision_state != 1 && pipe_collision_state != 3) && score_player1 < 67)
                score_player1++;
            if(!player2_gameover && (pipe_collision_state != 2 && pipe_collision_state != 3) && score_player2 < 67)
                score_player2++;
        }
        // Declarando o "GAMEOVER" do jogador 1 e removendo o seu sprite, ao zerar todas as vidas:
        if(lives[0][0][0] == 0)
            player1_gameover = 1;
        // Declarando o "GAMEOVER" do jogador 2 e removendo o seu sprite, ao zerar todas as vidas:
        if(lives[1][0][0] == 0)
            player2_gameover = 1;
        // Incrementando a velocidade no último laço e encerrando o jogo se houver "GAMEOVER" de ambos os jogadores:
        if(pipe_column == -1 || (player1_gameover && player2_gameover)){
            pipe_loop = 0; // Desativa o loop de deslocamento dos canos.
            if(displacement_speed > 50)
                displacement_speed -= 50; // Decrementa o tempo de deslocamento dos canos.
        }
        show_lives();                // Exibindo os sprites das vidas dos jogadores.
        while(on_pause){}            // Estado de pausa do jogo.
        usleep(displacement_speed);  // Tempo de deslocamento dos canos.
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
* Verifica se há um espaço vazio na coluna do sprite + 25.
* Se não, e houver uma parte do cano, haverá colisão.
*/
int player_pipe_collision(int pipe_column, int pipe_disabled_row){
    int player1_collision = 0; // Armazena o valor da colisão do jogador 1;
    int player2_collision = 0; // Armazena o valor da colisão do jogador 2;
    // Verificando a colisão dos jogadores com os canos:
    if(players_column_sprite+25 == pipe_column){
        // Colisão do jogador 1, com o cano:
        int polygon_dis_upper_boundary_pl1 = bg_row_to_sp_row(pipe_rows_player1[pipe_disabled_row]) - 15; // Borda superior do polígono desativado.
        int polygon_dis_lower_boundary_pl1 = polygon_dis_upper_boundary_pl1 + 30;                         // Borda inferior do polígono desativado.
        // Verificando se o jogador 1 está fora dos limites do polígono desativado:
        if(player1_row_sprite < polygon_dis_upper_boundary_pl1-1 || player1_row_sprite > polygon_dis_lower_boundary_pl1)
            player1_collision = 1; // O jogador 1 colidiu com o cano;
        // Colisão do jogador 2, com o cano:
        int polygon_dis_upper_boundary_pl2 = bg_row_to_sp_row(pipe_rows_player2[pipe_disabled_row]) - 15; // Borda superior do polígono desativado.
        int polygon_dis_lower_boundary_pl2 = polygon_dis_upper_boundary_pl2 + 30;                         // Borda inferior do polígono desativado.
        // Verificando se o jogador 2 está fora dos limites do polígono desativado:
        if(player2_row_sprite < polygon_dis_upper_boundary_pl2-1 || player2_row_sprite > polygon_dis_lower_boundary_pl2)
            player2_collision = 2; // O jogador 2 colidiu com o cano;
    }
    // Verificando a quantidade de colisões e fazendo o retorno:
    if(player1_collision == 1 && player2_collision == 0)
        return player1_collision; // Apenas o jogador 1 colidiu com o cano;
    else if(player1_collision == 0 && player2_collision == 2)
        return player2_collision; // Apenas o jogador 2 colidiu com o cano;
    else if(player1_collision == 1 && player2_collision == 2)
        return 3;                 // Ambos os jogadores colidiram com os canos;
    else
        return 0;                 // Nenhum dos jogadores colidiu com algum cano;
}

// Exibe os pontos dos jogadores em pontos do array bidimensional, que será exibido na tela:
void* show_score_and_gameover(void* arg){
    while(!game_exit){
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
                        background[1][column] = 1; // Os pontos serão armazenados com o valor "1" no array bidimensional.
                        score_player1_fhalf--;     // Decrementando a variável temporária dos pontos.
                    }
                    // Pontos do jogador 2:
                    if(score_player2_fhalf != 0){
                        background[29][column] = 1; // Os pontos serão armazenados com o valor "1" no array bidimensional.
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
                        background[2][column] = 1; // Os pontos serão armazenados com o valor "1" no array bidimensional.
                        score_player1_shalf--;     // Decrementando a variável temporária dos pontos.
                    }
                    // Pontos do jogador 2:
                    if(score_player2_shalf != 0){
                        background[30][column] = 1; // Os pontos serão armazenados com o valor "1" no array bidimensional.
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
                        background[1][column] = 1; // Os pontos serão armazenados com o valor "1" no array bidimensional.
                        score_temp1--;             // Decrementando a variável temporária dos pontos.
                    }
                    // Pontos do jogador 2:
                    if(score_temp2 != 0){
                        background[29][column] = 1; // Os pontos serão armazenados com o valor "1" no array bidimensional.
                        score_temp2--;             // Decrementando a variável temporária dos pontos.
                    }
                }
                // Indica que todos os pontos já foram exibidos, forçando a saída do "for".
                if(score_temp1 == 0 && score_temp2 == 0)
                    column = 80;
            }
        }
        render_background();      // Exibindo as pontuações na tela.
        show_gameover_screen(); // Exibindo "GAMEOVER" na tela.
    }
    return NULL;
}
