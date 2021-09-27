#include "menu.h"

void menuPrincipal(char* arquivoPlacar, char* arquivoLog)
{
    inicializaTabelaPokemons();
    char opcao[10];
    char nome[20];
    Jogador *jogador = NULL;
    FILE *log = fopen(arquivoLog, "w");
    int contadorPartidas = 1;
    do
    {
        system("clear");
        imprimeMenuPrincipal();
        scanf("%s", opcao); 
        switch(atoi(opcao))
        {
        case 1:
            printf("Digite seu nome:\n");
            do
            {
                scanf("%s", nome);     
            }while(verificaNome(nome) != 1);
            if(jogador == NULL)
                jogador = criaJogador(nome);
            menuIniciais(jogador);
            menuBatalha(jogador, contadorPartidas, log, arquivoPlacar);
            contadorPartidas++;
            if(jogador != NULL)
            {
                destroiJogador(jogador); 
                jogador = NULL;
            }
            break;

        case 2:
            system("clear");
            imprimePlacar(arquivoPlacar);
            break;

        case 3:
            break;
        }
    }while(atoi(opcao) != 3);
    fclose(log);
}

void imprimeMenuPrincipal()
{
    printf("                                  ,'\\                          \n");
    printf("    _.----.        ____         ,'  _\\   ___    ___     ____       \n");
    printf("_,-'       `.     |    |  /`.   \\,-'    |   \\  /   |   |    \\  |`. \n");
    printf("\\      __    \\    '-.  | /   `.  ___    |    \\/    |   '-.   \\ |  |\n");
    printf(" \\.    \\ \\   |  __  |  |/    ,','_  `.  |          | __  |    \\|  |\n");
    printf("   \\    \\/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |\n");
    printf("    \\     ,-'/  /   \\    ,'   | \\/ / ,`.|         /  /   \\  |     |\n");
    printf("     \\    \\ |   \\_/  |   `-.  \\    `'  /|  |    ||   \\_/  | |\\    |\n");
    printf("      \\    \\ \\      /       `-.`.___,-' |  |\\  /| \\      /  | |   |\n");
    printf("       \\    \\ `.__,'|  |`-._    `|      |__| \\/ |  `.__,'|  | |   |\n");
    printf("        \\_.-'       |__|    `-._ |              '-.|     '-.| |   |\n");
    printf("                                `'                            '-._|\n\n");
    printf("1 - Jogar\n2 - Ranking\n3 - Sair\n");
}

void menuIniciais(Jogador *jogador)
{
    ListaPokemon *iniciais = NULL;
    ListaPokemon *celulaAtual;

    iniciais = iniciaLista(selecionaPokemon('P')); 
    celulaAtual = iniciais;

    celulaAtual = inserePokemon(celulaAtual, selecionaPokemon('C'));
    celulaAtual = inserePokemon(celulaAtual, selecionaPokemon('B'));
    celulaAtual = inserePokemon(celulaAtual, selecionaPokemon('V'));
    celulaAtual = inserePokemon(celulaAtual, selecionaPokemon('S'));
    celulaAtual = inserePokemon(celulaAtual, selecionaPokemon('M'));

    escolherIniciais(jogador, iniciais);
}