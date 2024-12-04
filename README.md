<div align="justify">

  <h4>Universidade Estadual de Feira de Santana  
    
<br>Discentes: 
<uL> 
  <li><a href="https://github.com/thejoseviictor">José Victor de Oliveira Correia</a></li>
  <li><a href="https://github.com/Macedoxx2000">João Victor Macedo dos Santos Lima </a></li>
  <li><a href="https://github.com/MateusAntony/MateusAntony">Mateus Antony Medeiros Carvalho </a></li>
  <li><a href="https://github.com/WesleiSantos13">Weslei Silva Santos</a></li>
</ul>

<br>Turma: 3;  
<br>Grupo: 3;  
<br>Componente: TEC499 - MI-Sistemas digitais;  
<br>Docente: Wild Freitas da Silva;  
<br>Período: 2024.2.  
</h4>  

<br>
<br>

</div>
<p align="center">
  <img src="images/title.gif" width = "600" />
  </p>
  <p align="center"><strong> </strong></p>

<h2 align="center">Game inspirado no jogo Flappy Bird, desenvolvido para o kit de desenvolvimento DE1-SoC utilizando linguagem C e Assembly </h2>  

<br>
<br>


<h2 align="justify">Introdução</h2>

  <div align="justify">
  
  No mundo da computação, seja ele dividido em software ou hardware, muitas pessoas se utilizam e aproveitam das quase infinitas possibilidades de conhecimentos e ferramentas para serem utilizadas no dia a dia de forma produtiva e eficiente para as mais diversas funcionalidades e objetivos.  

  Uma das vertentes é a área de jogos, que hoje é considerada uma gigantesca parte do entretenimento e mercado global (que faturou cerca de $187,7 bilhões em 2023) . A     cada ano que passa, o mundo dos games se torna mais avançado, em quesitos de memória, gráfico, comunicação online e armazenamento em nuvem.  

  Dessa vez, o jogo que temos como inspiração é o jogo Flappy Bird, criando e publicado no ano de 2013 pelo programador vietnamita Nguyễn Hà Đông e publicado pela empresa .GEARS Studio.

  </div>

<br>
<br>

<h2 align="justify">Descrição do projeto</h2>

  <div align="justify">
  
  O projeto PBL3 teve como objetivo a utilização dos conceitos aprendidos em arquitetura de computadores e sistemas digitais, de forma prática, para a recriação do  jogo Flappy Bird, atendendo os seguintes requisitos mínimos:   

 - O código deve ser escrito em linguagem C e a biblioteca do Processador Gráfico em Assembly;
   
 - O sistema só poderá utilizar os componentes disponíveis na placa DE1-SoC;
   
 - Deverá utilizar todas as funções implementadas na biblioteca do Processador Gráfico e no mínimo um novo sprite deve ser colocado na memória e utilizado no jogo;
   
 - Os dois jogadores devem jogar simultaneamente utilizando obrigatoriamente o acelerômetro, e adicionalmente o mouse;
   
 - A variação da velocidade no movimento deve ser refletida na ação do ator do jogo. Por exemplo, no jogo breakout a barra se move com velocidade maior se o movimento do mouse for brusco;
   
 - Informações do jogo (placar, vidas, etc.) devem na tela do jogo;
   
 - O jogo deve permitir ações do usuário através dos botões da DE1-SoC, no mínimo: a pausa, o retorno, o reinício e o término do jogo.
    * O usuário poderá parar e reiniciar o jogo em qualquer momento;
    * O usuário poderá sair do jogo em qualquer momento;

  - Pelo menos dois elementos passivos do jogo deverão se mover;
    
  - Os jogos de tabuleiro e/ou turno (xadrez, dama, etc.), tetris e jogo da forca e da velha estão vetados. Adicionalmente, cada grupo deverá desenvolver um jogo diferente dos demais.

  </div>  

<br>
<br>

<h2>Descrição de softwares, equipamentos e ferramentas utilizadas: </h2>  
<div align="justify">  

  <h3> - Kit de desenvolvimento DE1-SoC: </h3>  
  <div align="justify">  

  O kit de desenvolvimento DE1-SoC, fabricado pela empresa Terasic, é uma placa baseada no chip Intel (Altera) Cyclone V SoC FPGA 5CSEMA5F31C6 e no Processador Dual-Core ARM Cortex-A9. É frequentimente utilizada em projetos educacionais de integração entre hardware e software.

  <p align="center">
  <img src="images/DE1-SoC Layout.webp" width = "800" />
  </p>
  <p align="center"><strong>Kit de desenvolvimento DE1-SoC </strong></p>

<br>
Os periféricos da placa DE1-SoC usados no projeto foram:

* VGA Out
* Accelerometer
* HPS Gigabit Ethernet
* Buttons x4
  
  </div>

<br>
  

  <h3> - Linguagem C: </h3>  
  <div align="justify">  

  A linguagem C, criada em 1970, é uma linguagem de programação poderosa pelo seu desempenho e controle excepcional de baixo nível em hardware, manipulação direta de memória, possibilitando acesso a registros de hardware, memória e controle de periféricos. Através disso, ela tem a capacidade de ser utilizada em propositos gerais com mínimas alterações possíveis e assim permitindo um alto grau de compatibilidade. 

  </div>  

<br>
<br>
  

  <h3> - Monitor CTR DELL E773c: </h3>  
  <div align="justify">  

  O monitor utilizado no desenvolvimento do projeto é o "CTR DELL E773c" que utiliza a tecnologia de tubo de raios catódicos para projeção imagens. Possui uma tela de 16 polegadas, resolução máxima de 1280 x 1024 pixels, entrada VGA e com frequência horizontal de até 70 kHz e taxa de atualização vertical de até 160 Hz​. Proporciona um bom contraste e brilho em comparação com outros monitores CRT da período de fabricação.

  <p align="center">
  <img src="images/Monitor CTR Dell E773c.jpg" width = "400" />
  </p>
  <p align="center"><strong>Monitor CRT DELL E733c</strong></p>

  </div>  

<br>
<br>
  
  
  <h3> - Visual Studio Code: </h3>  
  <div align="justify">  

  O Visual Studio Code (VS Code) é um editor de código-fonte multiplataforma disponível para Windows, macOS e Linux e desenvolvido pela Microsoft. Oferece suporte nativo para diversas linguagens de programação, como JavaScript, TypeScript, Python, C, C++, Java, PHP, Ruby e permite a instalação de extensões para suportar mais linguagens. Além disso permite sugestões de código, documentação e programação colaborativa em tempo real, e grande capacidade de personalização para atender as preferências do programador.

<br>


  <p align="center">
  <img src="images/Visual Code Studio editor.png" width = "650" />
  </p>
  <p align="center"><strong></strong></p>

  <div align="center">
  <a href="https://code.visualstudio.com/">Visual Code Studio</a>
  </div>

  </div>  

  <h3> - Compilador GNU: </h3>  
  <div align="justify"> 

  O <a href="https://gcc.gnu.org/"> GNU Compiler Collection</a>, criado por Richard Stallman, é um conjunto de compiladores desenvolvidos pelo projeto GNU em 1987 com o objetivo de reunir o poder de compilação não só da Linguagem C, mas também C++, Objective-C, Fortran, Ada, Go e entre outros. Tem portabilidade para  Linux, macOS e Windows, alto desempenho e otimização. E por essas características, é um recurso utilizado para o desenvolvimento de projetos envolvendo a comunicação entre software e hardware.

  <h3> - Mouse Dell MO56UO: </h3>  
  <div align="justify">  

  Modelo Dell MO56UO com método de rastreamento óptico, caracterizado pela rápida e fácil transição de movimentos.

<br>


  <p align="center">
  <img src="images/Mouse Dell MO56UO.webp" width = "400" />
  </p>
  <p align="center"><strong>Mouse Dell MO56UO</strong></p>

  
</div>

<br>

<h2>Lógica de jogo</h2>  
  <div align="justify">

<div align="justify">

Nessa seção será tratada a descrição da parte gráfica, movimentação, apresentação de diagrama com a lógica de jogo e imagens oriundas de testes realizados no ambiente de desenvolvimento Laboratório de Eletrônica Digital e Sistemas (LEDS - UEFS). <br>

</div>

<br>
    <h3>- Biblioteca gráfica em Assembly: </h3>  
  <div align="justify">  

  A exibição gráfica, que no "Projeto 1: Tetris" foi feita utilizando a linguagem C e a biblioteca "video.h", agora foi feita utilizando a linguagem Assembly para a criação de uma biblioteca própria para a visualização do jogo. Dentro dessa biblioteca, estão as seguintes funções básicas para o desenvolvimento do jogo:

<h4>  . Função "physical_to_virtual" : </h4>
  <div align="justify">

  Função responsável pelo mapeamento virtual do endereço físico, para uso geral em todos os processos gráficos necessários para a jogabilidade do Tetris. Os endereços base são colocados nos registradores R0, R1, R2, R3, R4, R5, R7 e LR, que são inicialmente salvos na pilha e após o agrupamento e retorno do endereço virtual para uma variavel global chamada "virtual_address" , são todos removidos da pilha.

  <p align="center">
  <img src="images/physical_to_virtual.png" width = "600" />
  </p>
  <p align="center"><strong>Código assembly da função "physical_to_virtual" </strong></p>

  </div>

<h4>  . Função "unmap_memory" : </h4>
  <div align="justify">

  Função responsável por remover o endereço virtual mapeado da memória e fechar o "/dev/mem". Nessa função os endereços atribuidos aos registradores R0, R1, R7 e LR, salvos na pilha, são limpos. Posteriormente o "/dev/mem" é fechado, os registradores utilizados são removidos da pilha e a função é encerrada.

  <p align="center">
  <img src="images/unmap_memory.png" width = "600" />
  </p>
  <p align="center"><strong>Código assembly da função "unmap_memory" </strong></p>
  
  </div>

   <h4>  . Função "buffer_overflow" : </h4>
  <div align="justify">

  Função responsável por analisar os buffers de "DATA_A" e "DATA_B" e evitar o overflow desses. Inicialmente ocorre o armazenamento dos registradores R0 e LR na pilha, o endereço virtual é atribuído a R0, compara-se se R0 é igual a 1 (indica overflow) e entra dentro de um looping até o valor mudar para 0 (sem overflow). Após sair do looping,os registradores são removidos da pilha e a função é encerrada.

   <p align="center">
  <img src="images/buffer_overflow.png" width = "600" />
  </p>
  <p align="center"><strong>Código assembly da função "buffer_overflow" </strong></p>

  </div>

  <h4>  . Função "background_color" : </h4>
  <div align="justify">

  Função responsável por mudar a cor do background (plano de fundo da tela). Primeiramente os registradores R0, R1, R2, R3, R9 e LR são salvos na pilha, após isso a função "buffer_overflow" analisa o buffer, o "DATA_A" e "DATA_B" são preenchidos, a cor de fundo é definido e por último os registradores são removidos da pilha e ocorre a saída da função.

  <p align="center">
  <img src="images/background_color.png" width = "600" />
  </p>
  <p align="center"><strong>Código assembly da função "background_color" </strong></p>


  <h4>  . Função "background_drawing" : </h4>
  <div align="justify">

  Função que desenha o background com uma cor definida na função "background_color" e que tem em R0, R1, R2 , respectivamente, a coordenada da linha, a coordenada da coluna e a cor. Inicialmente os registradores R0, R1, R2, R3, R4 e LR são armaznados na pilha, o buffer é analisado, as constantes são definidas, o cálculo da posição é definido por "R0 = (linha * 80) + coluna", o agrupamento e carregamnto do endreço virtual é realizado para que o background ser exibido. Por ultimo os registradores são removidos da pilha e a função é encerrada.

<p align="center">
  <img src="images/background_drawing.png" width = "600" />
  </p>
  <p align="center"><strong>Código assembly da função "background_drawing" </strong></p>
  </div>

  <h4>  . Função "background_block_erase" : </h4>
  <div align="justify">

  Função que realiza o apagamento do background e que segue a mesma lógica da função "background_drawing", com a diferença que a cor definida é a mesma cor base do background, para assim as exibições serem encobertas e o processo de limpeza seja realizado.

  <p align="center">
  <img src="images/background_block_erase.png" width = "600" />
  </p>
  <p align="center"><strong>Código assembly da função "background_block_erase" </strong></p>

  </div>

  <h4>  . Função "draw_polygon" : </h4>
  <div align="justify">

  Função responsável por deesenhar polígonos. Os registradores utilizados são o R0(Endereço do Polígono), R1(Coordenada de Referência da Linha), R2(Coordenada de Referência da Coluna), R3(Tamanho), R4(Cor), R5(Tipo d polígono: Quadrado ou Triângulo), R7 e LR, a partir de R4 os registradores são armazenados na pilha. Após isso o buffer é analisado e as informações são agrupadas para assim definir as características do polígono, o endereço virtual é passado e o polígono é exibido. Ao final, os registradores(R4, R5, R7 e LR) são removidos da pilha e a função é encerrada.

   <p align="center">
  <img src="images/draw_polygon.png" width = "600" />
  </p>
  <p align="center"><strong>Código assembly da função "draw_polygon" </strong></p>

  </div>

  <h4>  . Função "set_sprite" : </h4>
  <div align="justify">

  Função que define as informações caracteristicas do sprite e ao final o exibe, segue uma lógica parecida com a função "draw_polygon". De início, armazena os registradores R4 e LR na pilha, após isso o buffer é analisado e há o agrupamento das informações definidas nos registradores R0,R1, R2, R3 e R4 e exibe o sprite. Ao final, os registradores são removidos da pilha e a função é encerrada.

  <p align="center">
  <img src="images/set_sprite.png" width = "600" />
  </p>
  <p align="center"><strong>Código assembly da função ""set_sprite" </strong></p>

  </div>

  <h4>  . Função "sprite_drawing" : </h4>
  <div align="justify">

  Função responsável por guardar os novos sprites na memória. Cada sprite tem dimensão de 20x20 pixels e deve ser colocado no espaço disponível na mémoria para sprites.

  <p align="center">
  <img src="images/sprite_drawing.png" width = "600" />
  </p>
  <p align="center"><strong>Código assembly da função "sprite_drawing" </strong></p>

  </div>

  
<br>
<br>

<h3>- Sprites e animação</h3>  
  <div align="justify">

<div align="justify">

Os novos sprites foram desenvolvidos na resolução máxima de “20x20” pixels, cada sprite ocupará um offset específico na memória. Sendo assim, os offsets possíveis seguem o intervalo de “1” até “31”, totalizando o limite de “31” sprites.
A memória de sprites tem as seguintes dimensões: “640” linhas por “20” colunas. Portanto, o offset de um sprite define a sua posição de linha na memória. Por exemplo, o sprite com offset “4” terá as suas linhas seguindo o intervalo de “80” até “99”. O cálculo da linha inicial do sprite segue a seguinte equação: 0 + (offset * 20), e o da linha final: linha inicial + 20. Além disso, todos os sprites na memória têm as mesmas coordenadas de coluna, seguindo o intervalo de “0” até “19”.
Com base no que foi dito, é possível desenhar um sprite específico usando um array bidimensional “20x20”, contendo em suas posições os valores das cores de cada pixel.
Por fim, esse array bidimensional será enviado como parâmetro da função “sprite_drawing”. Nela o cálculo da posição de memória, com 14 bits, seguirá a seguinte equação: (linha * 20) + coluna.<br>

As funções responsáveis pelo armazenamento, exibição e animação dos sprites estão no arquivo "sprites.c" e são as descritas abaixo:

<strong>int sprite_builder(int offset, const int sprite_array[20][20]);</strong><br>
Função responsável por modular os sprites .
Os sprites são escritos verticalmente, percorrendo e modulando o sprite bidimensionalemnte.

<strong>int flappy_bird_sprites(void);</strong><br>
Função responsável por guardar os 4 sprites modulados para o jogo na memória.

<strong>void* sp_animation(void* arg);</strong><br>
Função responsável pela animação dos sprites dos jogadores 1 e 2, simulando animação de voo para o jogo "Flappy Bird".
A animação tem 3 FPS (frames per second).

</div>

 <p align="center">
  <img src="images/player1.gif" width = "480" />
  </p>
  <p align="center"><strong>Sprite do jogador 1.</strong></p>

<br>
  
  <p align="center">
  <img src="/images/player2.gif" alt="Tela de início do jogo" width="480"/>
  <br>
  <em>Sprite do jogador 2.</em>
</p>

<br>


<h3>- Funcionalidades de controle: Pausa, continuar, reiniciar e encerrar: </h3>
  <div align="justify">

  A placa DE1-SoC tem 4 botões, nomeados de KEY0, KEY1, KEY2 E KEY3 (no sentido direita para a esquerda). Assim como os displays de 7 segmentos, os botões também seguem a lógica "negativa", e quando ele é pressionado retorna 0 e quando não é retorna 1. O conjunto de 4 bits(0x1111) define quais botões são pressionados no momento.

<p align="center">
  <img src="/images/button.png" alt="Conexões entre os LEDs e o Cyclone V SoC FPGA
ogo" width="600"/>
  <br>
  <em>Conexões entre os LEDs e o Cyclone V SoC FPGA
.</em>
</p>

Abaixo há a relação binária-hexadcimal entre as saídas dos botões ao estarem ou não pressionados:
<br>

<div align="center">
  
  | Botão | Binário ( Lógica negativa) | Hexadecimal |
|:---------------: |:-------------------:| :--------------:|
| Nenhum botão pressionado | 1111 | F |
| 0 | 1110 | E |
| 1 | 1101 | D |
| 2 | 1011 | B |
| 3 | 0111 | 7 |

</div>

No projeto 3 esses periféricos, definidos na função "check_buttons" do arquivo "player_inputs.c" foram usados para criar as lógicas de pausa, continuar, reiniciar e encerrar a jogabilidade no jogo Flappy bird e foram escritas em linguagem C. Abaixo seguem a correspondência entre os botões e suas respectivas funções:

<div align="center">
  
  | Botão | Função | 
|:---------------: |:-------------------:|
| KEY0 | Continuar jogo | 
| KEY1 | Pausa do jogo |
| KEY2 | Reiniciar o jogo |
| KEY3 | Encerrar o jogo |

</div>

<br>
  </div>

  <h3>- Movimentação dos jogadores: </h3>
  <div align="justify">

  A lógica de movimentação dos jogadores foi pensada utilizando os sensores de força G do acelerômetro ADXL345, presente no FPGA DE1-SoC Cyclone V para a movimentação do jogador 1 e os sensores de deslocamento de um mouse qualquer foram utilizadas para a movimentação do jogador 2.<br>

  O ADXL345 possui três eixo (X, Y, Z) com alta resolução de medição, porém apenas o eixo X foi usado, permitindo a movimentação das peças no sentido vertical.<br>

  A comunicação entre o acelerômetro e o Cyclone V é feita através do serial I2C0, usando o HPS.<br>

  Para conectar o I2C0 ao ADXL345 é preciso modificar as entradas do bloco de multiplexadores (Pin Mux). Definindo a entrada "1" nos registradores "GENERALIO7/GENERALIO8" e "0" no "I2C0USEFPGA".<br>

  Antes de instanciar as funções do acelerômetro, é preciso mapear os endereços físicos base do "I2C0" e "SYSMGR" em endereços virtuais. E, em seguida, mapear os registradores restantes através da soma do endereço virtual base com o seu offset.<br>

  Desse modo, a lógica de movimentação usando o acelerômetro ADXL345 conta com as seguintes funções:<br>

  <strong> int open_memory(void);</strong><br>
  Acessa a memória física do sistema linux, através do diretório "/dev/mem", e retorna "-1", caso ocorra um erro na abertura do arquivo de memória<br>

  <strong> void enable_I2C0_HPS(int);</strong><br>
  Recebe como entrada o inteiro usando na função "open_memory".<br>
  Habilita a comunicação do ADXL345 com o I2C0, através do bloco de multiplexadores no módulo "sysmgr", usando os pinos HPS.<br>

  <strong>void setting_I2C0_ADXL345(void *);</strong><br>
  Recebe como entrada o endereço virtual base do "I2C0".<br>
  Inicia a comunicação I2C0 e seleciona o "ADXL345" como slave/target.<br>

  <strong>void setting_ADXL345(volatile unsigned int *);</strong><br>
  Recebe como entrada o endereço do registrador "I2C0_DATA".<br>
  Realiza as calibragens e configurações iniciais dos sensores do ADXL345, com base nas calibragens do "FPGA Academy".<br>

  <strong>int16_t lerEixoX(volatile unsigned int *, volatile unsigned int *);</strong><br>
  Recebe como entradas os endereços dos registradores "I2C0_DATA" e "I2C0_RXFLR".<br>
  Lê e retorna os valores de medição do eixo X em um inteiro de 16 bits com sinal.<br>

  Diante do exposto, a função principal faz a leitura do valor do eixo x, para valores maiores do que "+100g" o sprite do jogador 1 se moverá para cima, para valores menores do que "-100g" o sprite se moverá para baixo.

  O mouse possui dois eixos de medição (X, Y), porém apenas o eixo Y foi usado, permitindo a movimentação do sprite do jogador 2 no sentido vertical.<br>

  Do mesmo modo, a lógica de movimentação usando o mouse conta com as seguintes funções:<br>

 <strong>void linux_event_file(void)</strong><br>
 Responsável por abrir o arquivo de eventos de entradas no Linux. Assim é possível obteer os valores de movimentação do mouse.<br>
 
 <strong>void read_mouse_axis(void)</strong><br>
 Lê e armazena os valores da coordenada Y do mouse, utilizada na lógica de movimentação do jogador 2.<br>
 
 <strong>void* check_player2_input(void* arg)</strong><br>
 Função responsável por tratar a movimentação do jogador 2.<br>
 Conferindo também o estado de colisão e atualizando a posição de sprites.<br>
  
</div>

<br>
<br>

</div>

<br>

<p align="center">
  <img src="images/game.gif" width = "650" />
  </p>
  <p align="center"><strong>Demonstração de funcionamento do jogo.</strong></p>

  </div>  
  
<br>

<h2>Conclusões</h2>
<div align="justify">

  Como ponto final, foi possível, através dos conhecimentos adquiridos, a recriação do jogo Flappy Bird utilizando a placa DE1-SoC e os seus respectivos periféricos.<br>
  Todos os requisitos foram cumpridos, em destaque o desenvolvidmento da biblioteca gráfica e suas respectivas funções em linguagem Assembly, a criação de novos sprites, desenvolvimento de cenário e ambientação estática e móvel, pontuação  contagem de vidas utilizando o background da placa, movimentação simultânea de jogadores usando o acelerômetro ADXL345 e entradas do mouse, e por fim, as funcionalidades de controle de jogo utilizando os botões da placa. <br>
  Não houve gestão de tempo suficiente para implementar funcionalidades a mais.<br>

</div>

<br>

<h2>Referências</h2>
<div align="justify">

WIJMAN, Tom. New free report: Explore the global games market in 2023. [S. l.], 8 ago. 2023. Disponível em: https://newzoo.com/resources/blog/explore-the-global-games-market-in-2023<br>. Acesso em: 25 set. 2024. <br>  

INTEL CORPORATION. Cyclone V HPS Register Address Map and Definitions. [S. l.], 2012. Disponível em: https://www.intel.com/content/www/us/en/programmable/hps/cyclone-v/hps.html. Acesso em: 20 set. 2024.<br>  

FPGACADEMY. Lab 7 - Using the ADXL345 Accelerometer. [S. l.], 2021. Disponível em: https://fpgacademy.org/courses.html. Acesso em: 6 set. 2024.<br>  

ROSS, Matt. Dell E773c. [S. l.], 30 ago. 2024. Disponível em: https://crtdatabase.com/crts/dell/dell-e773c. Acesso em: 25 set. 2024.<br>  

INTEL CORPORATION. FPGAcademy Boards. [S. l.], 2021. Disponível em: https://fpgacademy.org/boards.html. Acesso em: 6 set. 2024. <br>

LEDS - LABORATÓRIO DE ELETRÔNICA DIGITAL E SISTEMAS. Recursos. [S. l.], 2022. Disponível em: https://sites.google.com/uefs.br/ltec3-leds. Acesso em: 28 ago. 2024. <br>

</div>
