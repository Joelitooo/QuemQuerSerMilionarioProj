//
// Created by Joel on 04/06/2020.
//
#include "FuncoesJogo.h"


void LimpQ(ELEMENTOQ **inilista, ELEMENTOQ **fimlista){
    ELEMENTOQ *aux, *temp;

    aux=*inilista;
    while(aux!=NULL){
        temp=aux->seguinte;
        free(aux);
        aux=temp;
    }
    *inilista=NULL;
    *fimlista=NULL;
    free(temp);

}

QUESTIONS dadosQ(){

    QUESTIONS aux;
    printf("\nQuestion:");
    scanf(" %100[^\n]s", aux.mainquestion);
    printf("\nOption1:");
    scanf(" %100[^\n]s",aux.option1);
    printf("\nOption2:");
    scanf(" %100[^\n]s",aux.option2);
    printf("\nOption3:");
    scanf(" %100[^\n]s", aux.option3);
    printf("\nOption4:");
    scanf(" %100[^\n]s", aux.option4);
    printf("\ncorrectoption:");
    scanf(" %100[^\n]s",aux.correctoption);
    printf("\nLevel of dificulty:");
    scanf("%d", &aux.dificulty);
    return aux;

}



void MakeQuestion(ELEMENTOQ **iniListaQuestion,ELEMENTOQ **fimListaQuestion, QUESTIONS aux_info) {
    ELEMENTOQ *novo = NULL;
    novo = (ELEMENTOQ *) calloc(1, sizeof(ELEMENTOQ));

    if (novo == NULL) {
        printf("Erro ao alocar memória\n");
        return ;
    }
    novo->infoq = aux_info;
    novo->anterior = NULL;
    novo->seguinte = NULL;
    if (*fimListaQuestion == NULL) {
        *iniListaQuestion = novo;
        *fimListaQuestion = novo;
    } else {
        novo->anterior = *fimListaQuestion;
        (*fimListaQuestion)->seguinte = novo;
        *fimListaQuestion = novo;
    }

}

void SaveQuestions(ELEMENTOQ *inilist){
    ELEMENTOQ *aux=NULL;
    FILE *finq=NULL;


    finq=fopen("Perguntas.dat","wb");
    if (finq==NULL){
        printf("\nError opening the file!");
        return ;
    }

    for(aux=inilist;aux!=NULL;aux=aux->seguinte){
        fwrite(&(aux->infoq), sizeof(QUESTIONS),10,finq);
    }

    printf("Ficheiro criado com sucesso\n");

    fclose(finq);

}

void ReadQuestions(ELEMENTOQ **iniList, ELEMENTOQ **fimList){

    FILE *foq=NULL;
    QUESTIONS aux;
    foq=fopen("Perguntas.dat","rb");

    if(foq==NULL){
        foq=fopen("Perguntas.dat","wb");
        fclose(foq);
        foq=fopen("Perguntas.dat","rb");
    }


    while (1){
        fread(&aux, sizeof(QUESTIONS), 1, foq);
        MakeQuestion(iniList, fimList, aux);
        if(feof(foq)){
            break;
        }

    }

    fclose(foq);

}

void printQuestion(ELEMENTOQ *iniList){

    printf("\nlalalalla");
    ELEMENTOQ *aux=NULL;
    for(aux=iniList;aux!=NULL;aux=aux->seguinte){
        printf("\nQuestion: %s \nAnswer options: %s\n%s\n%s\n%s\nCorrect Option:%s\nDificulty:%i\n", aux->infoq.mainquestion, aux->infoq.option1, aux->infoq.option2,aux->infoq.option3, aux->infoq.option4, aux->infoq.correctoption,aux->infoq.dificulty);

    }

}

