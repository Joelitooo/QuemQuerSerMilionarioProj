//
// Created by Joel on 02/05/2020.
//

#include "FuncoesJogo.h"



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++MENUS++++++++++++++++++++++++++++++++++++++++++++++++++++
int MainMenu(){
    int opc=0;
    printf("\n------------------Are you the ADMIN or a USER----------------------\n");
    printf("\nADMIN - 1");
    printf("\nUSER - 2");
    printf("\nEXIT-0\n");
    scanf("%i", &opc);
    return opc;

}


int MainSubMenu() {
    int opc2 = 0;
    printf("\n------------------------------------------------------------------------------------------------------------\n");
    printf("\n1-Play\n2-Watch Rules\n3-Register a new Player\n4-Listar os jogadores existentes\n0-BACK\n");
    printf("\n------------------------------------------------------------------------------------------------------------\n");
    scanf("%i", &opc2);

    return opc2;
}

int AdminMenu(){

    int opc3=0 ;
    printf("\n-------------------------------------------");
    printf("\n------YOU ARE ACESSING ADMIN RIGHTS--------\n");
    printf("\n1-Listar as perguntas e respostas");
    printf("\n2-Adicionar uma pergunta");
    printf("\n3-Remover uma pergunta");
    printf("\n4-Listar Jogadores");
    printf("\n5-Remover Jogador");
    printf("\n6-Ver tamanho da Lista de perguntas");
    printf("\n7-Ver tamanho da Lista de jogadores");
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
        printf("\nOut of memory\n");
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

ELEMENTOQ *ObterPergunta(ELEMENTOQ *iniListaQ, int escala) {
    int nPerguntas = 0, nPergunta;
    ELEMENTOQ *pergunta, *perguntaAux;
    perguntaAux = iniListaQ;

    while(perguntaAux!=NULL) {
        nPerguntas++;
        perguntaAux=perguntaAux->seguinte;
    }
    do {
        nPergunta = (rand() % nPerguntas);
        pergunta = iniListaQ;
        while (nPergunta > 0) {
            pergunta = pergunta->seguinte;
            nPergunta--;
        }
    }while (pergunta->infoq.dificulty != escala+1);
    return pergunta;
}

void InitGame(ELEMENTO *iniLista, ELEMENTOQ *iniListaQ) {
    int score = 0, escala = 0, iEscala = 0;
    char opCont[10];
    int ajudas[4]={1,1,1,0};
    ELEMENTO *jogador = LoginPlayer(iniLista);
    if(jogador == NULL) {
        printf("Player does not exist.");
        return;
    }
    int escalaDinheiro[3][5] = {{ 25, 50, 125, 250, 500 }, {750, 1500, 2500, 5000, 10000}, {16000, 32000, 64000, 125000, 250000}};
    printf("Welcome %s\n", jogador->info.nome);
    while(1) {
        ELEMENTOQ *pergunta = ObterPergunta(iniListaQ, escala);
        printf("\n----------------------------------------------------------------------------------\n");
        printf("Score: %i\tMoney: %i\n", score, escalaDinheiro[escala][iEscala]);
        printf("\n----------------------------------------------------------------------------------\n");
        GAMESTATUS gameStatus = FazerPergunta(pergunta, ajudas, 0);
        if(gameStatus == AJUDA1) {
            gameStatus = FazerPergunta(pergunta, ajudas, 1);
        } else if(gameStatus == AJUDA2) {
            gameStatus = FazerPergunta(pergunta, ajudas, 2);
        } else if(gameStatus == AJUDA3) {
            gameStatus = FazerPergunta(pergunta, ajudas, 3);
        } else if(gameStatus == AJUDA4) {
            pergunta = ObterPergunta(iniListaQ, escala);
            gameStatus = FazerPergunta(pergunta, ajudas, 0);
        }
        if(gameStatus == ONGOING) {
            score+=pergunta->infoq.dificulty;
            if(++iEscala == 5) {
                iEscala = 0;
                escala++;
                if (escala==3){
                    printf("You won the max prize\n");
                } else if(escala == 1) {
                    ajudas[3] = 1;
                }
                printf("\nDo you wish to continue?\n(Y/N)\n");
                scanf(" %100[^\n]s", opCont);
                if (strcmp(opCont, "N")==0){
                    break;
                }
            }
        } else {
            if (jogador->info.highscore==NULL) {
                printf("\nYour highscore is %i", score);
                jogador->info.highscore = score;
            } else if (jogador->info.highscore<score){
                printf("\nYour highscore is %i", score);
                jogador->info.highscore=score;
            } else{
                printf("\nYour score was %i\nYour highscore stays the same: %i", score, jogador->info.highscore);
            }
            break;
        }
    }
}

GAMESTATUS FazerPergunta(ELEMENTOQ *pergunta, int ajudas[4], int ajuda) {
    char opcao[100], opContH[10], opcaoAjudas[10], opContJ[10];

    if(ajuda == 0) {

        printf("Question: %s\nPossible Answers:\nA- %s\nB- %s\nC- %s\nD- %s\n",
               pergunta->infoq.mainquestion,
               pergunta->infoq.option1,
               pergunta->infoq.option2,
               pergunta->infoq.option3,
               pergunta->infoq.option4);

        printf("\nDo you need to use a HELP?\n(Y/N)\n");
        scanf(" %100[^\n]s", opContH);
        if (strcmp(opContH, "Y") == 0 && (ajudas[0] == 1 || ajudas[1] == 1 || ajudas[2] == 1 || ajudas[3] == 1)) {
            printf("Avaliable Helps:\n");
            if (ajudas[0] == 1) {
                printf("1- 50/50\n");
            }
            if (ajudas[1] == 1) {
                printf("2- Phone Call\n");
            }
            if (ajudas[2] == 1) {
                printf("3- Audience's help\n");
            }
            if (ajudas[3] == 1) {
                printf("4- Change question\n");
            }

            scanf(" %100[^\n]s", opcaoAjudas);

            if (strcmp(opcaoAjudas, "1") == 0 && ajudas[0] == 1) {
                ajudas[0] = 0;
                return AJUDA1;
            } else if (strcmp(opcaoAjudas, "2") == 0 && ajudas[1] == 1) {
                ajudas[1] = 0;
                return AJUDA2;
            } else if (strcmp(opcaoAjudas, "3") == 0 && ajudas[2] == 1) {
                ajudas[2] = 0;
                return AJUDA3;
            } else if (strcmp(opcaoAjudas, "4") == 0 && ajudas[3] == 1) {
                ajudas[3] = 0;
                return AJUDA4;
            }

        } else if (strcmp(opContH, "Y") == 0) {
            printf("You have no more helps.");
        } else {

        }
    } else {
        char perguntaOption1[1000], perguntaOption2[1000], respostaDoManel[1000], publico[1000];
        int respostasPublico[4];
        switch(ajuda) {
            case 1:
                if(rand()%2 == 0) {
                    strcpy(perguntaOption1, pergunta->infoq.correctoption);
                    do {
                        switch(rand()%4) {
                            case 0:
                                strcpy(perguntaOption2, pergunta->infoq.option1);
                                break;
                            case 1:
                                strcpy(perguntaOption2, pergunta->infoq.option2);
                                break;
                            case 2:
                                strcpy(perguntaOption2, pergunta->infoq.option3);
                                break;
                            case 3:
                                strcpy(perguntaOption2, pergunta->infoq.option4);
                                break;
                        }
                    } while(strcmp(perguntaOption1, perguntaOption2) == 0);
                } else {
                    strcpy(perguntaOption2, pergunta->infoq.correctoption);
                    do {
                        switch(rand()%4) {
                            case 0:
                                strcpy(perguntaOption1, pergunta->infoq.option1);
                                break;
                            case 1:
                                strcpy(perguntaOption1, pergunta->infoq.option2);
                                break;
                            case 2:
                                strcpy(perguntaOption1, pergunta->infoq.option3);
                                break;
                            case 3:
                                strcpy(perguntaOption1, pergunta->infoq.option4);
                                break;
                        }
                    } while(strcmp(perguntaOption1, perguntaOption2) == 0);
                }
                printf("Question: %s\nPossible Answers:\nA- %s\nB- %s\n",
                       pergunta->infoq.mainquestion,
                       perguntaOption1,
                       perguntaOption2);
                break;
            case 2:
                if(rand()%10<7) {
                    strcpy(respostaDoManel, pergunta->infoq.correctoption);
                } else {
                    do{
                        switch(rand()%4) {
                            case 0:
                                strcpy(respostaDoManel, pergunta->infoq.option1);
                                break;
                            case 1:
                                strcpy(respostaDoManel, pergunta->infoq.option2);
                                break;
                            case 2:
                                strcpy(respostaDoManel, pergunta->infoq.option3);
                                break;
                            case 3:
                                strcpy(respostaDoManel, pergunta->infoq.option4);
                                break;
                        }
                    } while(strcmp(respostaDoManel, pergunta->infoq.correctoption) == 0);
                }
                printf("\nYou called Manel, he answered: %s\n", respostaDoManel);
                break;
            case 3:
                for(int i = 0; i < 100; i++) {
                    if(rand()%100 < 90) {
                        strcpy(&publico[i], pergunta->infoq.correctoption);
                    } else {
                        do{
                            switch(rand()%4) {
                                case 0:
                                    strcpy(&publico[i], pergunta->infoq.option1);
                                    break;
                                case 1:
                                    strcpy(&publico[i], pergunta->infoq.option2);
                                    break;
                                case 2:
                                    strcpy(&publico[i], pergunta->infoq.option3);
                                    break;
                                case 3:
                                    strcpy(&publico[i], pergunta->infoq.option4);
                                    break;
                            }
                        } while(strcmp(&publico[i], pergunta->infoq.correctoption) == 0);
                    }
                }

                for(int i = 0;i < 100; i++) {
                    if(strcmp(&publico[i], pergunta->infoq.option1) == 0) {
                        respostasPublico[0]++;
                    } else if(strcmp(&publico[i], pergunta->infoq.option2) == 0) {
                        respostasPublico[1]++;
                    } else if(strcmp(&publico[i], pergunta->infoq.option3) == 0) {
                        respostasPublico[2]++;
                    } else if(strcmp(&publico[i], pergunta->infoq.option4) == 0) {
                        respostasPublico[3]++;
                    }
                }

                printf("Audience answers:\nOption 1: %s: %i\nOption 2: %s: %i\nOption 3: %s: %i\nOption 4: %s: %i\n",
                        pergunta->infoq.option1, respostasPublico[0],
                        pergunta->infoq.option2, respostasPublico[1],
                        pergunta->infoq.option3, respostasPublico[2],
                        pergunta->infoq.option4, respostasPublico[3]);

                break;
        }
    }

    printf("\n\nAnswer:");
    timer_t comeco= time(0);
    scanf(" %100[^\n]s", opcao);
    if (strcmp(opcao, (pergunta->infoq.correctoption)) == 0 ){

        if (time(0)-comeco > 30){
            printf("\nTime over\n");
            return ENDED;
        }
        printf("Correct Answer!\n");
        printf("\nDo you wish to continue playing?\n(Y/N)\n");
        scanf(" %100[^\n]s", opContJ);
        if (strcmp(opContJ, "N")==0){
            return ENDED;
        }
        return ONGOING;

    } else {
        printf("Incorrect Answer! Get sad :(");
        printf("\nThe correct answer was: %s \n", pergunta->infoq.correctoption);
        printf("\n_______________________________________________________________\n");

        return ENDED;
    }

}
