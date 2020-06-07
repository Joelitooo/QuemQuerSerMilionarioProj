#include <limits.h>
//
// Created by Joel on 04/06/2020.
//

#include "FuncoesJogo.h"


void LimpP(ELEMENTO **inilista, ELEMENTO **fimlista){
    ELEMENTO *aux, *temp;

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

JOGADOR dados(){
    JOGADOR aux;
    printf("\nIntroduza o seu primeiro e ultimo nome\nNome:");
    scanf(" %100[^\n]s", aux.nome);
    printf("\nSua idade por favor\nIdade:");
    scanf("%i", &aux.idade);
    return aux;

}
void criarJogador(ELEMENTO **iniLista,ELEMENTO **fimLista, JOGADOR aux_info){
    ELEMENTO *novo = NULL;
    novo = (ELEMENTO *) calloc(1, sizeof(ELEMENTO));

    if (novo == NULL) {
        printf("Erro ao alocar memória\n");
        return ;
    }
    novo->info = aux_info;
    novo->anterior = NULL;
    novo->seguinte = NULL;
    if (*iniLista == NULL) {
        *fimLista = novo;
        *iniLista = novo;
    } else {
        novo->seguinte = *iniLista;
        (*iniLista)->anterior = novo;
        *iniLista = novo;
    }

}

ELEMENTO *ReadNextFromFileP(ELEMENTO *iniLista, FILE *foq){

        if(iniLista == NULL){
            iniLista = malloc(sizeof(ELEMENTO));
            fread(iniLista, sizeof(ELEMENTO),1, foq);
            iniLista->seguinte=NULL;
            iniLista->anterior=NULL;

        } else{
            ELEMENTO  *indexPLayer = iniLista;
            ELEMENTO *newPlayer = malloc(sizeof(ELEMENTO));
            while (indexPLayer->seguinte != NULL){
                indexPLayer = indexPLayer->seguinte;
            }
            fread(newPlayer, sizeof(ELEMENTO),1,foq);
            indexPLayer->seguinte=newPlayer;
            newPlayer->seguinte=NULL;
            newPlayer->anterior=indexPLayer;

        }
        return iniLista;
    }


ELEMENTO *ReadListInP(ELEMENTO *iniLista, ELEMENTO *fimLista) {

    FILE *foq;
    foq=fopen("registedPlayers.dat","rb");

    if (foq!=NULL){

        //LimpQ(iniList, fimList);
        iniLista=NULL;
        fseek(foq, 0 ,SEEK_END);
        long filesize = ftell(foq);
        rewind(foq);

        int EntriesNum = (int)(filesize/ (sizeof(ELEMENTO)));
        printf("\nNumber of entries: %d\n", EntriesNum);

        int loop = 0;
        for (loop=0; loop <EntriesNum; loop++){
            fseek(foq, (sizeof(ELEMENTO) *loop), SEEK_SET);
            iniLista = ReadNextFromFileP(iniLista, foq);

        }

    } else{
        printf("\nThe file does not exist\n");
    }

}


void ListPlayers(ELEMENTO *iniLista){

    ELEMENTO *aux= iniLista;

    int count = 0;

    ELEMENTO *ahead = NULL;
    ELEMENTO *behind = NULL;

    while(aux != NULL) {
        count++;

        ahead = aux->seguinte;
        behind = aux->anterior;

        printf("\nName: %s \nAge: %d\n",
               aux->info.nome,
               aux->info.idade,

               (ahead == NULL) ? "None" : ahead->info.nome,
               (behind == NULL) ? "None" : behind->info.nome);

        aux = aux->seguinte;
        ahead = NULL;
        behind = NULL;
    }
    printf("Total Players:%d\n",count);
}

void SavePlayersFile(ELEMENTO *iniLista){
    ELEMENTO *aux=NULL;
    FILE *fin=NULL;

    fin=fopen("registedPlayers.dat","wb");
    if (fin==NULL){
        printf("\nError opening the file!");
        return ;
    }

    for(aux=iniLista;aux!=NULL;aux=aux->seguinte){
        fwrite(&(aux->info), sizeof(JOGADOR),1,fin);
    }

    printf("\nFile for players wrote with success \n");

    fclose(fin);

}
int ReadToListPlayers(ELEMENTO **iniList, ELEMENTO **fimList){


    FILE *foq=NULL;
    JOGADOR aux;
    foq=fopen("registedPlayers.dat","rb");

    if(foq==NULL){
    return -1;
    }

    while (1){
        fread(&aux, sizeof(aux), 1, foq);
        criarJogador(iniList, fimList, aux);
        if(feof(foq)){
            break;
        }

    }
    fclose(foq);
}

int removePerson(ELEMENTO **iniLista, ELEMENTO **fimLista, char nome[]){
    ELEMENTO *aux=NULL;

    aux=*iniLista;
    while(aux!=NULL && strcmp((aux->info.nome), nome)!=0){
        aux=aux->seguinte;
    }
    if(aux==NULL){
        printf("That name does not exist\n");
        return -1;
    }
    if(aux->anterior==NULL){
        *iniLista=aux->seguinte;
        if(*iniLista != NULL){
            (*iniLista)->anterior=NULL;
            aux->seguinte->anterior=*iniLista;
        }
    }
    else{
        aux->anterior->seguinte=aux->seguinte;
    }
    if(aux->seguinte==NULL){
        *fimLista=aux->anterior;
        if(*fimLista != NULL){
            (*fimLista)->seguinte=NULL;
        }
    }
    else{
        aux->seguinte->anterior=aux->anterior;
    }
    free(aux);
    return 0;
}

int getSizeListP(ELEMENTO *iniLista){

    if (iniLista==NULL){ return 0;}
    return (1+getSizeListP(iniLista->seguinte));
}

void showSizeP(ELEMENTO *iniLista) {
    size_t listSizep = getSizeListP(iniLista);
    printf("\nThe size of the double linked list is: %i", listSizep);
}














