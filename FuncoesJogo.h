#include <limits.h>
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
    int scorei;

}JOGADOR;

typedef struct question{

    int indice;
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

typedef enum gameStatus { ONGOING, AJUDA1, AJUDA2, AJUDA3, AJUDA4, ENDED }GAMESTATUS;


int MainMenu();
int MainSubMenu();
int AdminMenu();
JOGADOR dados();
QUESTIONS dadosQ();
void criarJogador(ELEMENTO **iniLista, ELEMENTO **fimLista, JOGADOR info_aux);

int MakeQuestion(ELEMENTOQ **iniList, ELEMENTOQ **endList, QUESTIONS aux_info);
void SavePlayersFile(ELEMENTO *iniLista) ;
int removePerson(ELEMENTO **iniLista, ELEMENTO **fimLista, char nome[]);
void SaveQuestions(ELEMENTOQ *inilist);
void ReadToListQ(ELEMENTOQ **iniList, ELEMENTOQ **endList);
int  ReadToListPlayers(ELEMENTO **iniList, ELEMENTO **fimList);
void GetQuestionOut(ELEMENTOQ **iniList, ELEMENTOQ **fimList, int indice);

int lerRegras();
void printQuestion(ELEMENTOQ *iniList);
void LimpP(ELEMENTO **inilista, ELEMENTO **fimlista);
void LimpQ(ELEMENTOQ **inilista, ELEMENTOQ **fimlista);
void ListPlayers(ELEMENTO *iniLista);
int getSizeListQ(ELEMENTOQ *iniList);
void showSizeQ(ELEMENTOQ *iniList);
int getSizeListP(ELEMENTO *iniLista);
void showSizeP(ELEMENTO *iniLista);
ELEMENTOQ *ReadListIn(ELEMENTOQ *iniList, ELEMENTOQ *fimList);
ELEMENTOQ *ObterPergunta(ELEMENTOQ *iniListaQ, int escala);
ELEMENTO  *ReadListInP(ELEMENTO *iniLista, ELEMENTO *fimLista);
void InitGame(ELEMENTO *iniLista, ELEMENTOQ *iniListaQ);
GAMESTATUS FazerPergunta(ELEMENTOQ *pergunta, int ajudas[4], int ajuda);

#endif //QUEMQUERSERMILIONARIOPROJ_FUNCOESJOGO_H
