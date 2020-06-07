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
    printf("\nIndice da Questao:");
    scanf("%i", &aux.indice);
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



int MakeQuestion(ELEMENTOQ **iniList, ELEMENTOQ **endList, QUESTIONS aux_info) {
    ELEMENTOQ *novo = NULL;
    novo = (ELEMENTOQ *) calloc(1, sizeof(ELEMENTOQ));

    if (novo == NULL) {
        printf("Erro ao alocar memória\n");
        return -1;
    }
    novo->infoq = aux_info;
    novo->anterior = NULL;
    novo->seguinte = NULL;
    if (*iniList == NULL) {
        *endList = novo;
        *iniList = novo;
    }
    else {
        novo->seguinte = *iniList;
        (*iniList)->anterior = novo;
        *iniList = novo;
    }
    return 0;
}

void SaveQuestions(ELEMENTOQ *inilist){

    FILE *finq;
    ELEMENTOQ *aux=NULL;


    finq=fopen("Perguntas.dat","wb");
    if (finq!=NULL){


        for (aux=inilist; aux != NULL; aux=aux->seguinte){
            fwrite(&(aux->infoq), sizeof(QUESTIONS),1 ,finq);
        }
        fclose(finq);


        /*
        ELEMENTOQ *sQuestion = inilist;
        ELEMENTOQ *holdNext =NULL;
        ELEMENTOQ *holdPrevious =NULL;

        while (sQuestion != NULL){
            holdNext= sQuestion->seguinte;
            holdPrevious= sQuestion->anterior;

            sQuestion->seguinte=NULL;
            sQuestion->anterior=NULL;

            fseek(finq,0, SEEK_END);

            fwrite(sQuestion, sizeof(ELEMENTOQ),1, finq);

            printf("\nWrinting %s to file\n", sQuestion->infoq.mainquestion);

            sQuestion->seguinte = holdNext;
            sQuestion->anterior = holdPrevious;

            holdNext=NULL;
            holdPrevious=NULL;

            sQuestion = sQuestion->seguinte;

        }
        fclose(finq);
        finq=NULL;*/
    } else{
        printf("\nError opening the file!");
        return ;
    }

    printf("File for Questions wrote with success\n");


}

ELEMENTOQ *ReadNextFromFile(ELEMENTOQ *iniList, FILE *foq){

    if(iniList == NULL){
        iniList = malloc(sizeof(ELEMENTOQ));
        fread(iniList, sizeof(ELEMENTOQ),1, foq);
        iniList->seguinte=NULL;
        iniList->anterior=NULL;

    } else{
        ELEMENTOQ  *indexQues = iniList;
        ELEMENTOQ *newQues = malloc(sizeof(ELEMENTOQ));
        while (indexQues->seguinte!= NULL){
            indexQues = indexQues->seguinte;
        }
        fread(newQues, sizeof(ELEMENTOQ),1,foq);
        indexQues->seguinte=newQues;
        newQues->seguinte=NULL;
        newQues->anterior=indexQues;

        }
    return iniList;
}

ELEMENTOQ *ReadListIn(ELEMENTOQ *iniList, ELEMENTOQ *fimList){

    FILE *foq;
    foq=fopen("Perguntas.dat","rb");

    if (foq!=NULL){

        iniList=NULL;
        fseek(foq, 0 ,SEEK_END);
        long filesize = ftell(foq);
        rewind(foq);

        int EntriesNum = (int)(filesize/ (sizeof(ELEMENTOQ)));
        printf("\nNumber of entries: %d\n", EntriesNum);

        for (int loop=0; loop <EntriesNum; loop++){
            fseek(foq, (sizeof(ELEMENTOQ) *loop), SEEK_SET);
            iniList = ReadNextFromFile(iniList, foq);
        }

    } else{
        printf("\nERRORRRRR\n");
    }

}

void ReadToListQ(ELEMENTOQ **iniList, ELEMENTOQ **endList){

    FILE *fy;
    QUESTIONS question;
    fy=fopen("Perguntas.dat", "rb");

    if(fy != NULL){
        /*fy=fopen("Perguntas.dat", "wb");
        fclose(fy);
        fy=fopen("Perguntas.dat", "rb");*/

        while (1){
            fread(&question, sizeof(question), 1, fy);
            //if (aux==NULL){ break;}
            MakeQuestion(iniList, endList, question);
            if(feof(fy)){
                break;
            }

        }

    } else{
        printf("\nFILE DOES NOT EXIST YET");
    }


    fclose(fy);

}


void printQuestion(ELEMENTOQ *iniList){


    ELEMENTOQ *aux= iniList;

    int count = 0;

    ELEMENTOQ *ahead = NULL;
    ELEMENTOQ *behind = NULL;

    while(aux != NULL) {
        count++;

        ahead = aux->seguinte;
        behind = aux->anterior;

        printf("\nIndice %d\nQuestion: %s \nAnswer options: %s\n%s\n%s\n%s\nCorrect Option:%s\nDificulty:%i\n",
                aux->infoq.indice,
                aux->infoq.mainquestion,
                aux->infoq.option1,
                aux->infoq.option2,
                aux->infoq.option3,
                aux->infoq.option4,
                aux->infoq.correctoption,
                aux->infoq.dificulty,

               (ahead == NULL) ? "None" : ahead->infoq.mainquestion,
               (behind == NULL) ? "None" : behind->infoq.mainquestion);

        aux = aux->seguinte;
        ahead = NULL;
        behind = NULL;
    }
    printf("Total Questions:%d\n",count);


/*
    for(aux=iniList;aux!=NULL;aux=aux->seguinte){
        printf("\nIndice: %i \nQuestion: %s \nAnswer options: %s\n%s\n%s\n%s\nCorrect Option:%s\nDificulty:%i\n",
                aux->infoq.indice,
                aux->infoq.mainquestion,
                aux->infoq.option1,
                aux->infoq.option2,
                aux->infoq.option3,
                aux->infoq.option4,
                aux->infoq.correctoption,
                aux->infoq.dificulty);

    }
*/
}



void GetQuestionOut(ELEMENTOQ **iniList, ELEMENTOQ **fimList, int indice){

    ELEMENTOQ *aux=NULL;

    aux=(*iniList);
    while(aux!=NULL && aux->infoq.indice!=indice){
        aux=aux->seguinte;
    }
    if(aux==NULL){
        printf("\nIndice not found");
        return;
    }
    if (aux->anterior==NULL){
        *iniList=aux->seguinte;
        if (*iniList!=NULL){
            (*iniList)->anterior=NULL;
            aux->seguinte->anterior=*iniList;
        }

    } else {
        aux->anterior->seguinte=aux->seguinte;
    }
    if(aux->seguinte==NULL){
        *fimList=aux->anterior;
        if(*fimList!=NULL){
            (*fimList)->seguinte=NULL;
        }
    } else{
        aux->seguinte->anterior=aux->anterior;
    }

    free(aux);

}

int getSizeListQ(ELEMENTOQ *iniList){

    if (iniList==NULL){ return 0;}
    return (1+getSizeListQ(iniList->seguinte));
}

void showSizeQ(ELEMENTOQ *iniList){
    size_t listSize = getSizeListQ(iniList);
    printf("\nThe size of the double linked list is: %i", listSize);

}










