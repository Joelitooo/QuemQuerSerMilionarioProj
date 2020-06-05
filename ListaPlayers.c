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
    foq=fopen("Jogadores.dat","rb");

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
        printf("\nERRORRRRR");
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
    ELEMENTO *aux;
    FILE *fin=NULL;
    aux=iniLista;
    fin=fopen("jogadoresResgitados.dat","wb");
    if (fin==NULL){
        printf("\nError opening the file!");
        return ;
    }

    for(aux=iniLista;aux!=NULL;aux=aux->seguinte){
        fwrite(&(aux->info), sizeof(JOGADOR),1,fin);
    }

    printf("Ficheiro criado com sucesso\n");

    fclose(fin);

}
void readPlayers(ELEMENTO **iniList, ELEMENTO **fimList){

    FILE *foq=NULL;
    JOGADOR *aux=NULL;
    foq=fopen("registedPlayers.dat","rb");

    if(foq==NULL){
        foq=fopen("registedPlayers.dat","wb");
        fclose(foq);
        foq=fopen("registedPlayers.dat","rb");
    }


    while (1){
        fread(aux, sizeof(QUESTIONS), 1, foq);
        if (aux==NULL) break;
        criarJogador(iniList, fimList, *aux);
        if(feof(foq)){
            break;
        }

    }

    fclose(foq);
}

int removePerson(ELEMENTO **iniListaPerguntaEscolhida, ELEMENTO **fimListaPerguntaEscolhida, char nome[]){
    ELEMENTO *aux=NULL;

    aux=*iniListaPerguntaEscolhida;
    while(aux!=NULL && strcmp((aux->info.nome), nome)!=0){
        aux=aux->seguinte;
    }
    if(aux==NULL){
        printf("That name does not exist\n");
        return -1;
    }
    if(aux->anterior==NULL){
        *iniListaPerguntaEscolhida=aux->seguinte;
        if(*iniListaPerguntaEscolhida!=NULL){
            (*iniListaPerguntaEscolhida)->anterior=NULL;
            aux->seguinte->anterior=*iniListaPerguntaEscolhida;
        }
    }
    else{
        aux->anterior->seguinte=aux->seguinte;
    }
    if(aux->seguinte==NULL){
        *fimListaPerguntaEscolhida=aux->anterior;
        if(*fimListaPerguntaEscolhida!=NULL){
            (*fimListaPerguntaEscolhida)->seguinte=NULL;
        }
    }
    else{
        aux->seguinte->anterior=aux->anterior;
    }
    free(aux);
    return 0;
}





















