
#include "FuncoesJogo.h"

int main() {
    int opc=0;
    int opc2=0;


    setlocale(LC_ALL, "Portuguese");
    ELEMENTO  *iniLista=NULL, *fimLista=NULL;
    ELEMENTOQ *iniList=NULL, *fimList=NULL;
    JOGADOR info_aux;
    int totregistos=0;
    FILE *fin=NULL;
    ELEMENTO *aux=NULL;
    QUESTIONS infoq_aux;
    ReadPlayers(&iniLista, &fimLista);
    char Passwd[100] = "09292147asd";
    char CorrectPasswd[100];
    int attempts=3;
    int res=0;
    int opc3=0;
    char nameremove[100];


    do{
        opc=MainMenu();
        switch (opc){
            case 1:do{
                    printf("\nPlease insert password:");

                    scanf(" %100[^\n]s", CorrectPasswd);
                    res = (strcmp(Passwd,CorrectPasswd)!=0);

                    if (res!=0){
                        printf("\nPassword incorrect. You still have %i tries" , attempts);
                        attempts--;
                    } else{
                        do{
                            opc3 = AdminMenu();
                            switch (opc3) {
                                case 1:
                                    printf("\nListar todas as perguntas e resposta");
                                    ReadListIn(iniList,fimList);
                                    printQuestion(iniList);
                                    break;
                                case 2:
                                    printf("\nRemover pergunta");
                                    break;
                                case 3:
                                    printf("\nAdicionar pergunta");
                                    infoq_aux=dadosQ();
                                    printf("\nI am here");
                                    MakeQuestion(&iniList,&fimList, infoq_aux);
                                    printf("\ni am here");
                                    SaveQuestions(iniList);
                                    printf("\nI am here");
                                    break;
                                case 4:
                                    printf("\nRemover historico");
                                    break;
                                case 5:
                                    printf("\nChose the name to remove:");
                                    fflush(stdin);
                                    scanf(" %100[^\n]s", nameremove);
                                    removePerson(&iniLista,&fimLista, nameremove);
                                    break;
                                    case 6:
                                        showSizeQ(iniList);
                                case 0:
                                    break;

                            }
                        }while (opc3!=0);
                    }

                }while (res!=0 && attempts>0);
                break;
            case 2:do {
                    opc2 = MainSubMenu();
                    switch(opc2){
                        case 1:
                            printf("\nUr going to play now.\n");
                            InitGame(iniLista, iniList);
                            break;
                        case 112:
                            printf("\nUr going to watch the rules\n");
                            lerRegras();
                            break;
                        case 3:
                            printf("\nUr going to watch the best 10 players");
                            break;
                        case 4:
                            printf("\nUr going to regist a new player");
                            info_aux=dados();
                            printf("\nI am here");
                            criarJogador(&iniLista,&fimLista,info_aux);
                            break;
                        case 5:
                            printf("\nListagem de todos os jogadores registados\n");
                            ReadListInP(iniLista,fimLista);
                            ListPlayers(iniLista);
                            break;
                        case 0:
                            break;
                    }
                }while(opc2!=0);
                break;
            case 0: printf("\nVolte sempre\n");
                printf("\n");
                SavePlayersFile(iniLista, totregistos);
                printf("\n");
                LimpP(&iniLista, &fimLista);
                LimpQ(&iniList, &fimList);
                break;
            default:printf("\nPor favor escolha uma opção válida");

        }


}while (opc!=0);

    return 0;
}



