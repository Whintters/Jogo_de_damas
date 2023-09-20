#include <stdio.h>
#include <stdlib.h>

// Constantes e estruturas.

typedef struct{
    int linha;
    int coluna;
    int valor;
}Peca;

typedef struct{
    Peca pecas[12];
    int cont;
    char identificador;
}Jogador;

// Assinaturas das funções.

void inicializaTabuleiro(); //Pronta.
void inicializaPeca(); //Pronta.
void dispoemPecas(); //Pronta.
void telaInicial(); //Pronta.
void selecionaJogador(); //Pronta.


void telaJogo(Jogador jogador1, Jogador jogador2); //Pronta.
void telaFinal(Jogador jogador); //Pronta.

void iniciarJogo(Jogador jogador1, Jogador jogador2); //Pronta.
void carregarJogo(char z); // Pronta.
void deletaJogoSalvo(char z); // Pronta.
void pecasCapturadas(Jogador jogador1, Jogador jogador2);//Pronta.
void sairTela();//Pronta.

void verificaMovimento(int linhaI, int colunaI, int linhaF, int colunaF, Jogador jogador1, Jogador jogador2);//Pronta.
void movePeca(int linhaI, int colunaI, int linhaF, int colunaF, Jogador jogador1, Jogador jogador2);//Pronta.

// Variáveis.

Jogador j1;
Jogador j2;

Peca tabuleiro[8][8];

int i, j, k=0, linI, linF, colI, colF, aux;
char z = 'a';

//-------------------------------------------------------------------------------------------------------------

int main()
{
    telaInicial();
}

//-------------------------------------------------------------------------------------------------------------

void telaInicial(){ // Tela inicial do jogo.

    printf("+============================================================================+\n");
    printf("|   Jogo de Damas                                                            |\n");
    printf("+============================================================================+\n");
    printf("|                                                                            |\n");
    printf("|     Menu                                                                   |\n");
    printf("|                                                                            |\n");
    printf("|          [01] Iniciar um novo jogo                                         |\n");
    printf("|          [02] Sair                                                         |\n");
    printf("|                                                                            |\n");
    printf("+============================================================================+\n");
    printf("\n");
    printf("->Escolha uma opcao: ");
    scanf("%d", &aux);
    
    printf("\n");

    switch(aux){

        case 1:
            selecionaJogador();
            break;

        case 2:
            printf("Jogo encerrado!\n");
            system("cls");
            break;

        default:
            printf("Opcao invalida, por favor, escolha novamente entre as opcoes 1 ou 2:\n");
            telaInicial();
            break;
    }
}

//-------------------------------------------------------------------------------------------------------------

void selecionaJogador(){ // Função que seleciona qual jogador começa.

    printf("+============================================================================+\n");
    printf("|      Quer comecar jogando?        1 = Sim   2 = Nao                        |\n");
    printf("+============================================================================+\n");
    printf("\n");
    printf("->Escolha uma opcao: ");
    scanf("%d", &aux);

    if(aux!=1&&aux!=2){
        printf("Entrada incorreta, por favor, digite 1 ou 2 para escolher uma das opcoes.\n");
        selecionaJogador();
    }

    printf("\n");
    inicializaPeca();

    if(aux==1){
        iniciarJogo(j1, j2);
    }
    else{
        iniciarJogo(j2, j1);
    }
}

//-------------------------------------------------------------------------------------------------------------

void iniciarJogo(Jogador jogador1, Jogador jogador2){ // Função que inicializa o tabuleiro e dispõem as peças.

    inicializaTabuleiro();
    inicializaPeca();
    dispoemPecas();
    telaJogo(jogador1, jogador2);
}

//-------------------------------------------------------------------------------------------------------------

void inicializaTabuleiro(){ // Função que cria o tabuleiro como uma matriz 8x8 de peças.

    for(i=0;i<8;i++){
        for(j=0;j<8;j++){

            if(i%2==0){
                if(j%2==0){
                    tabuleiro[i][j].valor = 1;
                }
                else{
                    tabuleiro[i][j].valor = 0;
                }
            }

            else{
                if(j%2==0){
                    tabuleiro[i][j].valor = 0;
                }
                else{
                    tabuleiro[i][j].valor = 1;
                }
            }

            tabuleiro[i][j].linha = i;
            tabuleiro[i][j].coluna = j;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------

void inicializaPeca(){ // Função que inicializa os jogadores com seus campos preenchidos.

    j1.cont = 0;
    j2.cont = 0;

    j1.identificador = 'b';
    j2.identificador = 'p';
}

//-------------------------------------------------------------------------------------------------------------

void dispoemPecas(){ // Função que coloca as peças no tabuleiro. Onde o jogador 1 está na parte superior e o 2 está na 
                     // parte inferior do tabuleiro.

    for(i=0;i<8;i++){
        for(j=0;j<8;j++){

            if(i<3){
                if(i%2==0){
                    if(j%2==0){
                        tabuleiro[i][j].valor = 2;
                        j1.pecas[k].linha = i;
                        j1.pecas[k].coluna = j;
                        k++;
                    }
                }
                else{
                    if(j%2!=0){
                        tabuleiro[i][j].valor = 2;
                        j1.pecas[k].linha = i;
                        j1.pecas[k].coluna = j;
                        k++;
                    }
                }
            }
            else if(i>4){
                if(i%2==0){
                    if(j%2==0){
                        tabuleiro[i][j].valor = 3;
                        j2.pecas[k].linha = i;
                        j2.pecas[k].coluna = j;
                        k++;
                    }
                }
                else{
                    if(j%2!=0){
                        tabuleiro[i][j].valor = 3;
                        j2.pecas[k].linha = i;
                        j2.pecas[k].coluna = j;
                        k++;
                    }
                }
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------

void telaJogo(Jogador jogador1, Jogador jogador2){ // Tela do jogo em si conforme slide do projeto.

    int lin=0;

    printf("+============================================================================+\n");
    printf("|   Jogo de Damas                                                            |\n");
    printf("+============================================================================+\n");
    printf("|           00     01     02     03     04     05     06     07              |\n");

    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if(j==0){
                printf("|   0%d   ", lin);
                lin++;
            }

            if(tabuleiro[i][j].valor==0){
                printf("[     ]" );
            }

            else if(tabuleiro[i][j].valor==1){
                printf("[  -  ]" );
            }

            else if(tabuleiro[i][j].valor==2){
                printf("[  b  ]" );
            }

            else if(tabuleiro[i][j].valor==3){
                printf("[  p  ]" );
            }

            else if(tabuleiro[i][j].valor==4){
                printf("[  B  ]" );
            }

            else if(tabuleiro[i][j].valor==5){
                printf("[  P  ]" );
            }

            else{
                printf("[  -  ]");
            }
        }

        printf("            |\n");
    }

    printf("|                                                                            |\n");
    printf("|                       [7] Ver pecas capturadas                             |\n");
    printf("|   [6] Fazer jogada                                  [8] Sair               |\n");
    printf("+============================================================================+\n");
    printf("|                                                                            |\n");
    printf("|                            VEZ DO JOGADOR %c                                |\n", jogador1.identificador);
    printf("|                                                                            |\n");
    printf("+============================================================================+\n");
    printf("\n");
    printf("->Escolha uma opcao: ");
    scanf("%d", &aux);

    printf("\n");

    switch(aux){

        case 6:

            printf("-> Digite o numero da linha inicial: \n");
            scanf("%d", &linI);
            printf("-> Digite o numero da coluna inicial: \n");
            scanf("%d", &colI);
            printf("-> Digite o numero da linha final: \n");
            scanf("%d", &linF);
            printf("-> Digite o numero da coluna final: \n");
            scanf("%d", &colF);

            verificaMovimento(linI, colI, linF, colF, jogador1, jogador2);
            break;

        case 7:
            pecasCapturadas(jogador1, jogador2);
            break;

        case 8:
            sairTela();
            break;

        default:
            printf("Opcao invalida, por favor, escolha novamente entre as opcoes 6, 7 ou 8:\n");
            telaJogo(jogador1, jogador2);
            break;
    }
}

//-------------------------------------------------------------------------------------------------------------

void pecasCapturadas(Jogador jogador1, Jogador jogador2){ // Função que mostra o número de peças capturadas pelo jogador.

    printf("O jogador %c capturou %d pecas: \n", jogador1.identificador, jogador1.cont);
    telaJogo(jogador1, jogador2);
}

//-------------------------------------------------------------------------------------------------------------

void sairTela(){ // Função que sai da tela do jogo e retorna a tela inicial.

    telaInicial();
}

//-------------------------------------------------------------------------------------------------------------

 // Função que verifica o movimento do jogador.

void verificaMovimento(int linhaI, int colunaI, int linhaF, int colunaF, Jogador jogador1, Jogador jogador2){

    int aux1=0;
    int aux2=0;
    
    aux = linhaI - colunaI;

    if(jogador1.identificador=='b'&&(tabuleiro[linhaI][colunaI].valor==3||tabuleiro[linhaI][colunaI].valor==5)){
        printf("Movimento invalido!\n");
        printf("Peca pertencente a outro jogador\n");
        telaJogo(jogador1, jogador2);
    }

    else if (jogador1.identificador=='p'&&(tabuleiro[linhaI][colunaI].valor==2||tabuleiro[linhaI][colunaI].valor==4)){
        printf("Movimento invalido!\n");
        printf("Peca pertencente a outro jogador\n");
        telaJogo(jogador1, jogador2);
    }

    else if(linhaI>7||linhaI<0||linhaF>7||linhaF<0||colunaI>7||colunaI<0||colunaF>7||colunaF<0){
        printf("Movimento invalido!\n");
        telaJogo(jogador1, jogador2);
    }

    else if(tabuleiro[linhaF][colunaF].valor!=1||tabuleiro[linhaI][colunaI].valor==0||tabuleiro[linhaI][colunaI].valor==1){
        printf("Movimento invalido!\n");
        telaJogo(jogador1, jogador2);
    }

    else if(linhaI==linhaF||colunaI==colunaF){
        printf("Movimento invalido!\n");
        telaJogo(jogador1, jogador2);
    }

    else if(tabuleiro[linhaI][colunaI].valor==2){

        //cima direita:
        if((linhaI>linhaF&&colunaI<colunaF)){
            if(tabuleiro[linhaI-1][colunaI+1].valor==2||tabuleiro[linhaI-1][colunaI+1].valor==4){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }
            else if(tabuleiro[linhaI-1][colunaI+1].valor==1){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }
            else if((tabuleiro[linhaI-1][colunaI+1].valor==3||tabuleiro[linhaI-1][colunaI+1].valor==5)&&(linhaF<linhaI-2||colunaF>colunaI+2)){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }
        }

        //cima esquerda:
        if((linhaI>linhaF&&colunaI>colunaF)){
            if(tabuleiro[linhaI-1][colunaI-1].valor==2||tabuleiro[linhaI-1][colunaI-1].valor==4){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }
            else if(tabuleiro[linhaI-1][colunaI-1].valor==1){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }
            else if((tabuleiro[linhaI-1][colunaI-1].valor==3||tabuleiro[linhaI-1][colunaI-1].valor==5)&&(linhaF<linhaI-2||colunaF<colunaI-2)){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }
        }

        //baixo direita:
        if((linhaI<linhaF&&colunaI<colunaF)){
            if(tabuleiro[linhaI+1][colunaI+1].valor==2||tabuleiro[linhaI+1][colunaI+1].valor==4){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }
            else if(tabuleiro[linhaI+1][colunaI+1].valor==1&&(linhaF>linhaI+1||colunaF>colunaI+1)){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }
            else if((tabuleiro[linhaI+1][colunaI+1].valor==3||tabuleiro[linhaI+1][colunaI+1].valor==5)&&(linhaF>linhaI+2||colunaF>colunaI+2)){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }
        }

        //baixo esquerda:
        if((linhaI<linhaF&&colunaI>colunaF)){
            if(tabuleiro[linhaI+1][colunaI-1].valor==2||tabuleiro[linhaI+1][colunaI-1].valor==4){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }
            else if(tabuleiro[linhaI+1][colunaI-1].valor==1&&(linhaF>linhaI+1||colunaF<colunaI-1)){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }
            else if((tabuleiro[linhaI+1][colunaI-1].valor==3||tabuleiro[linhaI+1][colunaI-1].valor==5)&&(linhaF>linhaI+2||colunaF<colunaI-2)){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }
        }
    }

    else if(tabuleiro[linhaI][colunaI].valor==3){

        //baixo direita:
        if((linhaI<linhaF&&colunaI<colunaF)){
            if(tabuleiro[linhaI+1][colunaI+1].valor==3||tabuleiro[linhaI+1][colunaI+1].valor==5){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }
            else if(tabuleiro[linhaI+1][colunaI+1].valor==1){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }
            else if((tabuleiro[linhaI+1][colunaI+1].valor==2||tabuleiro[linhaI+1][colunaI+1].valor==4)&&(linhaF>linhaI+2||colunaF>colunaI+2)){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }
        }

        //baixo esquerda:
        if((linhaI<linhaF&&colunaI>colunaF)){
            if(tabuleiro[linhaI+1][colunaI-1].valor==3||tabuleiro[linhaI+1][colunaI-1].valor==5){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }
            else if(tabuleiro[linhaI+1][colunaI-1].valor==1){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }
            else if((tabuleiro[linhaI+1][colunaI-1].valor==2||tabuleiro[linhaI+1][colunaI-1].valor==4)&&(linhaF>linhaI+2||colunaF<colunaI-2)){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }
        }

        //cima direita:
        if((linhaI>linhaF&&colunaI<colunaF)){
            if(tabuleiro[linhaI-1][colunaI+1].valor==3||tabuleiro[linhaI-1][colunaI+1].valor==5){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }
            else if(tabuleiro[linhaI-1][colunaI+1].valor==1&&(linhaF<linhaI-1||colunaF>colunaI+1)){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }
            else if((tabuleiro[linhaI-1][colunaI+1].valor==2||tabuleiro[linhaI-1][colunaI+1].valor==4)&&(linhaF<linhaI-2||colunaF>colunaI+2)){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }
        }

        //cima esquerda:
        if((linhaI>linhaF&&colunaI>colunaF)){
            if(tabuleiro[linhaI-1][colunaI-1].valor==3||tabuleiro[linhaI-1][colunaI-1].valor==5){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }
            else if(tabuleiro[linhaI-1][colunaI-1].valor==1&&(linhaF<linhaI-1||colunaF<colunaI-1)){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }
            else if((tabuleiro[linhaI-1][colunaI-1].valor==2||tabuleiro[linhaI-1][colunaI-1].valor==4)&&(linhaF<linhaI-2||colunaF<colunaI-2)){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }
        }
    }

    else if(tabuleiro[linhaI][colunaI].valor==4){ // Verifica condição da dama do jogador 1.

        //baixo direita:
        if(linhaI<linhaF&&colunaI<colunaF){
            for(i=linhaI;i<linhaF;i++){
                for(j=colunaI;j<colunaF;j++){
                    if((i-j==aux)&&(tabuleiro[i][j].valor==3||tabuleiro[i][j].valor==5)){
                        aux1++;
                    }
                    if((i-j==aux)&&(tabuleiro[i][j].valor==2||tabuleiro[i][j].valor==4)){
                        aux2++;
                    }
                }
            }

            if(aux1>1||aux2!=1){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }

            aux1 = 0;
            aux2 = 0;
        }

        //cima direita:
        if(linhaI>linhaF&&colunaI<colunaF){
            for(i=linhaI;i>linhaF;i--){
                for(j=colunaI;j<colunaF;j++){
                    if((i-j==aux)&&(tabuleiro[i][j].valor==3||tabuleiro[i][j].valor==5)){
                        aux1++;
                    }
                    if((i-j==aux)&&(tabuleiro[i][j].valor==2||tabuleiro[i][j].valor==4)){
                        aux2++;
                    }
                }
                aux = aux - 2;
            }

            if(aux1>1||aux2!=1){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }

            aux1 = 0;
            aux2 = 0;
        }

        //cima esquerda:
        if(linhaI>linhaF&&colunaI>colunaF){
            for(i=linhaI;i>linhaF;i--){
                for(j=colunaI;j>colunaF;j--){
                    if((i-j==aux)&&(tabuleiro[i][j].valor==3||tabuleiro[i][j].valor==5)){
                        aux1++;
                    }
                    if((i-j==aux)&&(tabuleiro[i][j].valor==2||tabuleiro[i][j].valor==4)){
                        aux2++;
                    }
                }
            }

            if(aux1>1||aux2!=1){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }

            aux1 = 0;
            aux2 = 0;
        }

        //baixo esquerda:
        if(linhaI<linhaF&&colunaI>colunaF){
            for(i=linhaI;i<linhaF;i++){
                for(j=colunaI;j>colunaF;j--){
                    if((i-j==aux)&&(tabuleiro[i][j].valor==3||tabuleiro[i][j].valor==5)){
                        aux1++;
                    }
                    if((i-j==aux)&&(tabuleiro[i][j].valor==2||tabuleiro[i][j].valor==4)){
                        aux2++;
                    }
                }
                aux = aux + 2;
            }

            if(aux1>1||aux2!=1){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }

            aux1 = 0;
            aux2 = 0;
        }
    }

    else if(tabuleiro[linhaI][colunaI].valor==5){ // Verifica condição da dama do jogador 2.

        //baixo direita:
        if(linhaI<linhaF&&colunaI<colunaF){
            for(i=linhaI;i<linhaF;i++){
                for(j=colunaI;j<colunaF;j++){
                    if((i-j==aux)&&(tabuleiro[i][j].valor==2||tabuleiro[i][j].valor==4)){
                        aux1++;
                    }
                    if((i-j==aux)&&(tabuleiro[i][j].valor==3||tabuleiro[i][j].valor==5)){
                        aux2++;
                    }
                }
            }

            if(aux1>1||aux2!=1){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }

            aux1 = 0;
            aux2 = 0;
        }

        //cima direita:
        if(linhaI>linhaF&&colunaI<colunaF){
            for(i=linhaI;i>linhaF;i--){
                for(j=colunaI;j<colunaF;j++){
                    if((i-j==aux)&&(tabuleiro[i][j].valor==2||tabuleiro[i][j].valor==4)){
                        aux1++;
                    }
                    if((i-j==aux)&&(tabuleiro[i][j].valor==3||tabuleiro[i][j].valor==5)){
                        aux2++;
                    }
                }
                aux = aux - 2;
            }

            if(aux1>1||aux2!=1){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }

            aux1 = 0;
            aux2 = 0;
        }

        //cima esquerda:
        if(linhaI>linhaF&&colunaI>colunaF){
            for(i=linhaI;i>linhaF;i--){
                for(j=colunaI;j>colunaF;j--){
                    if((i-j==aux)&&(tabuleiro[i][j].valor==2||tabuleiro[i][j].valor==4)){
                        aux1++;
                    }
                    if((i-j==aux)&&(tabuleiro[i][j].valor==3||tabuleiro[i][j].valor==5)){
                        aux2++;
                    }
                }
            }

            if(aux1>1||aux2!=1){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }

            aux1 = 0;
            aux2 = 0;
        }

        //baixo esquerda:
        if(linhaI<linhaF&&colunaI>colunaF){
            for(i=linhaI;i<linhaF;i++){
                for(j=colunaI;j>colunaF;j--){
                    if((i-j==aux)&&(tabuleiro[i][j].valor==2||tabuleiro[i][j].valor==4)){
                        aux1++;
                    }
                    if((i-j==aux)&&(tabuleiro[i][j].valor==3||tabuleiro[i][j].valor==5)){
                        aux2++;
                    }
                }
                aux = aux + 2;
            }

            if(aux1>1||aux2!=1){
                printf("Movimento invalido!\n");
                telaJogo(jogador1, jogador2);
            }

            aux1 = 0;
            aux2 = 0;
        }
    }

    movePeca(linI, colI, linF, colF, jogador1, jogador2);
}

//-------------------------------------------------------------------------------------------------------------

// Função que move a peça do jogador.

void movePeca(int linhaI, int colunaI, int linhaF, int colunaF, Jogador jogador1, Jogador jogador2){

    int aux = linhaI - colunaI;

    //baixo direita:

    if(linhaI<linhaF&&colunaI<colunaF){

        if(tabuleiro[linhaI][colunaI].valor==2||tabuleiro[linhaI][colunaI].valor==3){
            if(tabuleiro[linhaI+1][colunaI+1].valor==1){
                tabuleiro[linhaF][colunaF].valor = tabuleiro[linhaI][colunaI].valor;
                tabuleiro[linhaI][colunaI].valor = 1;
            }

            else{
                tabuleiro[linhaF][colunaF].valor = tabuleiro[linhaI][colunaI].valor;
                tabuleiro[linhaI][colunaI].valor = 1;
                tabuleiro[linhaI+1][colunaI+1].valor = 1;
                jogador1.cont++;
            }
        }

        else if(tabuleiro[linhaI][colunaI].valor==4||tabuleiro[linhaI][colunaI].valor==5){

            for(i=linhaI;i<linhaF;i++){
                for(j=colunaI;j<colunaF;j++){
                    if((i-j==aux)&&(tabuleiro[i][j].valor==3||tabuleiro[i][j].valor==5)&&tabuleiro[linhaI][colunaI].valor==4){
                        tabuleiro[linhaF][colunaF].valor = tabuleiro[linhaI][colunaI].valor;
                        tabuleiro[linhaI][colunaI].valor = 1;
                        tabuleiro[i][j].valor = 1;
                        jogador1.cont++;
                    }
                    else if((i-j==aux)&&(tabuleiro[i][j].valor==2||tabuleiro[i][j].valor==4)&&tabuleiro[linhaI][colunaI].valor==5){
                        tabuleiro[linhaF][colunaF].valor = tabuleiro[linhaI][colunaI].valor;
                        tabuleiro[linhaI][colunaI].valor = 1;
                        tabuleiro[i][j].valor = 1;
                        jogador1.cont++;
                    }
                }
            }

            if(tabuleiro[linhaF][colunaF].valor==1){
                tabuleiro[linhaF][colunaF].valor = tabuleiro[linhaI][colunaI].valor;
                tabuleiro[linhaI][colunaI].valor = 1;
            }
        }

    }

    //cima direita:

    else if(linhaI>linhaF&&colunaI<colunaF){

        if(tabuleiro[linhaI][colunaI].valor==2||tabuleiro[linhaI][colunaI].valor==3){
            if(tabuleiro[linhaI-1][colunaI+1].valor==1){
                tabuleiro[linhaF][colunaF].valor = tabuleiro[linhaI][colunaI].valor;
                tabuleiro[linhaI][colunaI].valor = 1;
            }

            else{
                tabuleiro[linhaF][colunaF].valor = tabuleiro[linhaI][colunaI].valor;
                tabuleiro[linhaI][colunaI].valor = 1;
                tabuleiro[linhaI-1][colunaI+1].valor = 1;
                jogador1.cont++;
            }
        }

        else if(tabuleiro[linhaI][colunaI].valor==4||tabuleiro[linhaI][colunaI].valor==5){

            for(i=linhaI;i>linhaF;i--){
                for(j=colunaI;j<colunaF;j++){
                    if((i-j==aux)&&(tabuleiro[i][j].valor==3||tabuleiro[i][j].valor==5)&&tabuleiro[linhaI][colunaI].valor==4){
                        tabuleiro[linhaF][colunaF].valor = tabuleiro[linhaI][colunaI].valor;
                        tabuleiro[linhaI][colunaI].valor = 1;
                        tabuleiro[i][j].valor = 1;
                        jogador1.cont++;
                    }
                    else if((i-j==aux)&&(tabuleiro[i][j].valor==2||tabuleiro[i][j].valor==4)&&tabuleiro[linhaI][colunaI].valor==5){
                        tabuleiro[linhaF][colunaF].valor = tabuleiro[linhaI][colunaI].valor;
                        tabuleiro[linhaI][colunaI].valor = 1;
                        tabuleiro[i][j].valor = 1;
                        jogador1.cont++;
                    }
                }
                aux = aux - 2;
            }

            if(tabuleiro[linhaF][colunaF].valor==1){
                tabuleiro[linhaF][colunaF].valor = tabuleiro[linhaI][colunaI].valor;
                tabuleiro[linhaI][colunaI].valor = 1;
            }
        }
    }

    //cima esquerda:

    else if(linhaI>linhaF&&colunaI>colunaF){

        if(tabuleiro[linhaI][colunaI].valor==2||tabuleiro[linhaI][colunaI].valor==3){
            if(tabuleiro[linhaI-1][colunaI-1].valor==1){
                tabuleiro[linhaF][colunaF].valor = tabuleiro[linhaI][colunaI].valor;
                tabuleiro[linhaI][colunaI].valor = 1;
            }

            else{
                tabuleiro[linhaF][colunaF].valor = tabuleiro[linhaI][colunaI].valor;
                tabuleiro[linhaI][colunaI].valor = 1;
                tabuleiro[linhaI-1][colunaI-1].valor = 1;
                jogador1.cont++;
            }
        }

        else if(tabuleiro[linhaI][colunaI].valor==4||tabuleiro[linhaI][colunaI].valor==5){

            for(i=linhaI;i>linhaF;i--){
                for(j=colunaI;j>colunaF;j--){
                    if((i-j==aux)&&(tabuleiro[i][j].valor==3||tabuleiro[i][j].valor==5)&&tabuleiro[linhaI][colunaI].valor==4){
                        tabuleiro[linhaF][colunaF].valor = tabuleiro[linhaI][colunaI].valor;
                        tabuleiro[linhaI][colunaI].valor = 1;
                        tabuleiro[i][j].valor = 1;
                        jogador1.cont++;
                    }
                    else if((i-j==aux)&&(tabuleiro[i][j].valor==2||tabuleiro[i][j].valor==4)&&tabuleiro[linhaI][colunaI].valor==5){
                        tabuleiro[linhaF][colunaF].valor = tabuleiro[linhaI][colunaI].valor;
                        tabuleiro[linhaI][colunaI].valor = 1;
                        tabuleiro[i][j].valor = 1;
                        jogador1.cont++;
                    }
                }
            }

            if(tabuleiro[linhaF][colunaF].valor==1){
                tabuleiro[linhaF][colunaF].valor = tabuleiro[linhaI][colunaI].valor;
                tabuleiro[linhaI][colunaI].valor = 1;
            }
        }
    }

    //baixo esquerda:

    else if(linhaI<linhaF&&colunaI>colunaF){

        if(tabuleiro[linhaI][colunaI].valor==2||tabuleiro[linhaI][colunaI].valor==3){
            if(tabuleiro[linhaI+1][colunaI-1].valor==1){
                tabuleiro[linhaF][colunaF].valor = tabuleiro[linhaI][colunaI].valor;
                tabuleiro[linhaI][colunaI].valor = 1;
            }

            else{
                tabuleiro[linhaF][colunaF].valor = tabuleiro[linhaI][colunaI].valor;
                tabuleiro[linhaI][colunaI].valor = 1;
                tabuleiro[linhaI+1][colunaI-1].valor = 1;
                jogador1.cont++;
            }
        }

        else if(tabuleiro[linhaI][colunaI].valor==4||tabuleiro[linhaI][colunaI].valor==5){

            for(i=linhaI;i<linhaF;i++){
                for(j=colunaI;j>colunaF;j--){
                    if((i-j==aux)&&(tabuleiro[i][j].valor==3||tabuleiro[i][j].valor==5)&&tabuleiro[linhaI][colunaI].valor==4){
                        tabuleiro[linhaF][colunaF].valor = tabuleiro[linhaI][colunaI].valor;
                        tabuleiro[linhaI][colunaI].valor = 1;
                        tabuleiro[i][j].valor = 1;
                        jogador1.cont++;
                    }
                    else if((i-j==aux)&&(tabuleiro[i][j].valor==2||tabuleiro[i][j].valor==4)&&tabuleiro[linhaI][colunaI].valor==5){
                        tabuleiro[linhaF][colunaF].valor = tabuleiro[linhaI][colunaI].valor;
                        tabuleiro[linhaI][colunaI].valor = 1;
                        tabuleiro[i][j].valor = 1;
                        jogador1.cont++;
                    }
                }
                aux = aux + 2;
            }

            if(tabuleiro[linhaF][colunaF].valor==1){
                tabuleiro[linhaF][colunaF].valor = tabuleiro[linhaI][colunaI].valor;
                tabuleiro[linhaI][colunaI].valor = 1;
            }
        }
    }

    if(jogador1.identificador=='b'&&linhaF==7){
        tabuleiro[linhaF][colunaF].valor = 4;
    }
    else if(jogador1.identificador=='p'&&linhaF==0){
        tabuleiro[linhaF][colunaF].valor = 5;
    }

    if(jogador1.cont==12){
        telaFinal(jogador1);
    }
    else if (jogador2.cont==12){
        telaFinal(jogador2);
    }

    telaJogo(jogador2, jogador1);
}

//-------------------------------------------------------------------------------------------------------------

void telaFinal(Jogador jogador){ // tela final mostrando quem ganhou.

    printf("+============================================================================+\n");
    printf("|   Jogo de Damas                                                            |\n");
    printf("+============================================================================+\n");
    printf("|                                                                            |\n");
    printf("|                         O JOGADOR %c GANHOU!                                |\n", jogador.identificador);
    printf("|                                                                            |\n");
    printf("+============================================================================+\n");
    printf("\n");
    telaInicial();
}

//-------------------------------------------------------------------------------------------------------------