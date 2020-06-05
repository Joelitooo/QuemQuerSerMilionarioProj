//
// Created by Joel on 02/05/2020.
//

#ifndef QUEMQUERSERMILIONARIOPROJ_FUNCOESJOGO_H
#define QUEMQUERSERMILIONARIOPROJ_FUNCOESJOGO_H

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "conio.h"
#include <string.h>
#include <locale.h>
#include <time.h>
#include <unistd.h>

typedef struct user{

    char nome[100];
    int idade;

}JOGADOR;

typedef struct question{

    char mainquestion[10000];
    char option1[10000];
    char option2[10000];
    char option3[10000];
    char option4[10000];
    char correctoption[1000];
    int dificulty;

}QUESTIONS;

typedef struct elem{
    JOGADOR info;
    struct elem *seguinte;
    struct elem *anterior;
}ELEMENTO;

typedef struct elemq{
    QUESTIONS infoq;
    struct elemq *seguinte;
    struct elemq *anterior;
}ELEMENTOQ;

typedef enum gameStatus { ONGOING, ENDED }GAMESTATUS;


int MainMenu();
int MainSubMenu();
int AdminMenu();
JOGADOR dados();
QUESTIONS dadosQ();
void criarJogador(ELEMENTO **iniLista, ELEMENTO **fimLista, JOGADOR info_aux);
void ReadPlayers(ELEMENTO **iniLista, ELEMENTO **fimLista);
void MakeQuestion(ELEMENTOQ **iniList, ELEMENTOQ **endList, QUESTIONS aux_info);
void SavePlayersFile(ELEMENTO *iniLista, int totregistos);
int removePerson(ELEMENTO **iniListaPerguntaEscolhida, ELEMENTO **fimListaPerguntaEscolhida, char nome[]);
void SaveQuestions(ELEMENTOQ *inilist);

int lerRegras();
void printQuestion(ELEMENTOQ *iniList);
void LimpP(ELEMENTO **inilista, ELEMENTO **fimlista);
void LimpQ(ELEMENTOQ **inilista, ELEMENTOQ **fimlista);
void ListPlayers(ELEMENTO *iniList);
int getSizeListQ(ELEMENTOQ *iniList);
void showSizeQ(ELEMENTOQ *iniList);
ELEMENTOQ *ReadListIn(ELEMENTOQ *iniList, ELEMENTOQ *fimList);


ELEMENTOQ *ObterPergunta(ELEMENTOQ *iniListaQ);
void InitGame(ELEMENTO *iniLista, ELEMENTOQ *iniListaQ);
GAMESTATUS FazerPergunta(ELEMENTOQ *pergunta);

#endif //QUEMQUERSERMILIONARIOPROJ_FUNCOESJOGO_H
