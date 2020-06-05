//
// Created by Joel on 02/05/2020.
//

#include "FuncoesJogo.h"



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++MENUS++++++++++++++++++++++++++++++++++++++++++++++++++++
int MainMenu(){
    int opc=0;
    printf("\nAre you the ADMIN or a USER");
    printf("\nADMIN - 1");
    printf("\nUSER - 2");
    printf("\nEXIT-0\n");
    scanf("%i", &opc);
    return opc;

}


int MainSubMenu() {
    int opc2 = 0;


    printf("\nPlay-1\nWatch Rules-112\nList the Best 10 Players-2\nRegister a new Player-4\nListar os jogadores existentes-5\nBack-0\n");
    scanf("%i", &opc2);

    return opc2;
}

int AdminMenu(){

    int opc3=0 ;
    printf("\n-------------------------------------------");
    printf("\n------YOU ARE ACESSING ADMIN RIGHTS--------\n");
    printf("\n1-Listar as perguntas e respostas");
    printf("\n2-Remover uma pergunta");
    printf("\n3-Adicionar uma pergunta");
    printf("\n4-Reset no historico");
    printf("\n5-Remover Jogador");
    printf("\n0 - SAIR");
    printf("\n--------------------------------------------\n");
    scanf("%i", &opc3);

    return opc3;

}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++LER REGRAS+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


int lerRegras(){

    int i=0;

    FILE *fout=fopen ("rules.txt", "r");
    if(fout==NULL){
        printf("\nOut of memory");
        return -1;
    }
     char output[256];

    for (i=1; fgets(output, sizeof(output), fout) != NULL; i++){

        printf("%02d: %s", i, output);

    }
fclose(fout);

    return 0;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++ Game Engine +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

ELEMENTO *LoginPlayer(ELEMENTO *iniLista) {

    char nomeJogador[2], nomeComparacao[2];
    int i = 0;

    printf("Introduza o nome do jogador: ");
    scanf(" %100[^\n]s", nomeJogador);
    ELEMENTO *tempJogador;

    tempJogador = iniLista;

    while(tempJogador!=NULL) {
        nomeComparacao[0] = tempJogador->info.nome[0];
        for(int i = 1; i<strlen(tempJogador->info.nome); i++) {
            if(tempJogador->info.nome[i] == ' ') {
                nomeComparacao[1] = tempJogador->info.nome[i+1];
                break;
            }
        }

        if(nomeJogador[0] == nomeComparacao[0] && nomeComparacao[1] == nomeJogador[1]) {
            break;
        }

        tempJogador=tempJogador->seguinte;
    }

    return tempJogador;
}

ELEMENTOQ *ObterPergunta(ELEMENTOQ *iniListaQ) {
    int nPerguntas = 0, nPergunta;
    ELEMENTOQ *pergunta, *perguntaAux;
    perguntaAux = iniListaQ;

    while(perguntaAux!=NULL) {
        nPerguntas++;
        perguntaAux=perguntaAux->seguinte;
    }
    srand(time(NULL)/3600);
    nPergunta =(rand() % nPerguntas-1)+1;
    pergunta = iniListaQ;
    while(nPergunta>0) {
        pergunta=pergunta->seguinte;
        nPergunta--;
    }

    return pergunta;
}

void InitGame(ELEMENTO *iniLista, ELEMENTOQ *iniListaQ) {
    int score = 0, escala = 0, iEscala = 0;
    ELEMENTO *jogador = LoginPlayer(iniLista);
    if(jogador == NULL) {
        printf("O jogador não existe.");
        return;
    }
    int escalaDinheiro[3][5] = {{ 25, 50, 125, 250, 500 }, {750, 1500, 2500, 5000, 10000}, {16000, 32000, 64000, 125000, 250000}};
    printf("Bem vindo %s\n", jogador->info.nome);
    while(1) {
        ELEMENTOQ *pergunta = ObterPergunta(iniListaQ);
        printf("Score: %i\tMoney: %i\n", score, escalaDinheiro[escala][iEscala]);
        GAMESTATUS gameStatus = FazerPergunta(pergunta);
        if(gameStatus == ONGOING) {
            score+=pergunta->infoq.dificulty;
            if(++iEscala == 5) {
                iEscala = 0;
                escala++;
            }
        } else {
            break;
        }
    }
}

GAMESTATUS FazerPergunta(ELEMENTOQ *pergunta) {
    char opcao[100];
    printf("Question: %s\nPossible Answers:\nA- %s\nB- %s\nC- %s\nD- %s\nAnswer:", pergunta->infoq.mainquestion, pergunta->infoq.option1, pergunta->infoq.option2, pergunta->infoq.option3, pergunta->infoq.option4);
    scanf(" %100[^\n]s", opcao);

    if(opcao == pergunta->infoq.correctoption) {
        return ONGOING;
    } else {
        return ENDED;
    }
}