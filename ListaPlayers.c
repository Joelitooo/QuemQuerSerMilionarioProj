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
    printf("\nIntroduza a sua localidade\nLocalidade:");
    scanf(" %100[^\n]s", aux.localidade);
    printf("\nIntroduza o seu ano de escolaridade(nº)\nAno:");
    scanf("%i", &aux.anodeescolaridade);
    return aux;

}
void criarJogador(ELEMENTO **iniListaUser,ELEMENTO **fimListaUser, JOGADOR aux_info){
    ELEMENTO *novo=NULL;
    novo=(ELEMENTO *)calloc(1,sizeof(ELEMENTO));

    if(novo==NULL){
        printf("Erro ao alocar memória\n");
        return ;
    }
    novo->info=aux_info;
    novo->seguinte=NULL;
    novo->anterior=NULL;
    if(*iniListaUser==NULL){
        *fimListaUser=novo;
        *iniListaUser=novo;
    }
    else{
        novo->seguinte=*fimListaUser;
        (*iniListaUser)->anterior=novo;
        *iniListaUser=novo;
    }
    //(*totregistos)+=1;


}


void ReadPlayers(ELEMENTO **iniLista, ELEMENTO **fimLista){

    FILE *fo=NULL;
    //ELEMENTO *novo=NULL;
    fo=fopen("jogadoresResgitados.dat","rb");
    if(fo==NULL) {
        fo = fopen("jogadoresResgitados.dat", "wb");
        fclose(fo);
        fo = fopen("jogadoresResgitados.dat", "rb");
    }
    JOGADOR aux;

    while (1){
        fread(&aux, sizeof(JOGADOR), 1, fo);
        if(aux.nome == NULL || aux.nome == ' ') {
            break;
        }
        //printf("Nome: %s \nIdade: %i \nLocalidade: %s \nAno de escolaridade: %i\n", aux.nome, aux.idade, aux.localidade,aux.anodeescolaridade);
        criarJogador(iniLista, fimLista, aux);
        if(feof(fo)){
            break;
        }

    }

    fclose(fo);

}

void ListPlayers(ELEMENTO *iniList){
    ELEMENTO *aux=NULL;
    for(aux=iniList;aux!=NULL;aux=aux->seguinte){
        printf("Nome: %s \nIdade: %i \nLocalidade: %s \nAno de escolaridade: %i\n", aux->info.nome, aux->info.idade, aux->info.localidade,aux->info.anodeescolaridade);
        }
}

void SavePlayersFile(ELEMENTO *iniLista, int totregistos){
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