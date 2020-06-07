
#include "FuncoesJogo.h"

int main() {

    setlocale(LC_ALL, "Portuguese");
    ELEMENTO  *iniLista=NULL, *fimLista=NULL;
    ELEMENTOQ *iniList=NULL, *fimList=NULL;
    JOGADOR info_aux;
    QUESTIONS infoq_aux;
    ReadToListPlayers(&iniLista, &fimLista);
    ReadToListQ(&iniList, &fimList);
    char Passwd[100] = "asd";
    char CorrectPasswd[100];
    int attempts=3;
    int opc=0;
    int opc2=0;
    int res=0;
    int opc3=0;
    int indice=0;
    char nameremove[100];
    srand(time(NULL));

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
                                    printf("\nListar todas as perguntas e resposta\n");
                                    ReadListIn(iniList, fimList);
                                    printQuestion(iniList);
                                    break;
                                case 2:
                                    printf("\nAdicionar pergunta");
                                    infoq_aux=dadosQ();
                                    MakeQuestion(&iniList,&fimList, infoq_aux);
                                    break;
                                case 3:
                                    printf("\nRemover pergunta");
                                    printf("\nChose the indice of the question to remove:");
                                    scanf("%i", &indice);
                                    GetQuestionOut(&iniList, &fimList, indice);
                                    break;
                                case 4:
                                    printf("\n----------------------LISTING ALL THE PLAYERS----------------------------\n");
                                    ReadListInP(iniLista,fimLista);
                                    ListPlayers(iniLista);
                                    break;
                                case 5:
                                    printf("\nChose the name to remove:");
                                    fflush(stdin);
                                    scanf(" %100[^\n]s", nameremove);
                                    removePerson(&iniLista,&fimLista, nameremove);
                                    break;
                                case 6:
                                    showSizeQ(iniList);
                                    break;
                                case 7:
                                    showSizeP(iniLista);
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
                            printf("\n---------------------YOU ARE GOING TO PLAY NOW---------------------------\n");
                            InitGame(iniLista, iniList);
                            break;
                        case 2:
                            printf("\n----------------------RULES----------------------------------------------\n");
                            lerRegras();
                            break;
                        case 3:
                            printf("\n----------------------REGISTING A NEW PLAYER-----------------------------\n");
                            info_aux=dados();
                            criarJogador(&iniLista,&fimLista,info_aux);
                            break;
                        case 4:
                            printf("\n----------------------LISTING ALL THE PLAYERS----------------------------\n");
                            ReadListInP(iniLista,fimLista);
                            ListPlayers(iniLista);
                            break;
                        case 0:
                            break;
                    }
                }while(opc2!=0);
                break;
            case 0: printf("\nComeback always!\n");
                printf("\n");
                SavePlayersFile(iniLista);
                printf("\n");
                SaveQuestions(iniList);
                printf("\n");
                LimpP(&iniLista, &fimLista);
                LimpQ(&iniList, &fimList);
                break;
            default:printf("\nPlease choose a valid option");

        }


}while (opc!=0);

    return 0;
}



