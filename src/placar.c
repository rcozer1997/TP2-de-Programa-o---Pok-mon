#include "placar.h"

struct listaPlacar
{
    char *nome;
    int pontuacao;
    struct listaPlacar *prox;
};

void resultadoPlacar(Jogador *jogador, char *arquivoPlacar)
{
    ListaPlacar *listaPlacar = criaListaPlacar(arquivoPlacar);
    listaPlacar = inserePlacar(jogador, listaPlacar);
    imprimeListaPlacarArquivo(listaPlacar, arquivoPlacar);

    destroiListaPlacar(listaPlacar);
}

ListaPlacar *criaListaPlacar(char *arquivoPlacar)
{
    ListaPlacar *listaPlacar;
    ListaPlacar *celulaAtual;
    FILE *placar = fopen(arquivoPlacar, "r");
    if (placar == NULL)
    {
        printf("Problemas na abertura do arquivo\n");
        exit(1);
    }
    char linha[200], nome[190];
    int pontuacao;
    int primeiroElemento = 1;

    while(fgets(linha, 200, placar))
    {
        sscanf(linha,"%s %d", nome, &pontuacao);
        if(primeiroElemento)
        {
            listaPlacar = (ListaPlacar*)malloc(sizeof(ListaPlacar));
            listaPlacar->nome = strdup(nome);
            listaPlacar->pontuacao = pontuacao;
            listaPlacar->prox = NULL;
            celulaAtual = listaPlacar;
            primeiroElemento = 0;
        }
        else
        {
            celulaAtual->prox = (ListaPlacar*)malloc(sizeof(ListaPlacar));
            celulaAtual = celulaAtual->prox;
            celulaAtual->nome = strdup(nome);
            celulaAtual->pontuacao = pontuacao;
            celulaAtual->prox = NULL;
        }
    }

    fclose(placar);
    return listaPlacar;
}

void imprimeListaPlacarArquivo(ListaPlacar *listaPlacar, char *arquivoPlacar)
{
    FILE *placar = fopen(arquivoPlacar, "w");
    ListaPlacar * celula;
    celula = listaPlacar;

    do{
        fprintf(placar,"%s %d\n", celula->nome, celula->pontuacao);
        celula = celula->prox;
    }while (celula != NULL);
    fclose(placar);
}

void imprimePlacar(char *arquivoPlacar)
{
    FILE *placar = fopen(arquivoPlacar, "r");
    char linha[200], nome[190];
    int pontuacao, index = 1;

    while(fgets(linha, 200, placar))
    {
        sscanf(linha,"%s %d", nome, &pontuacao);
        printf("%d - %s: %d\n", index, nome, pontuacao);
        index++;
    }
    getchar();
    getchar();
    fclose(placar);
}

ListaPlacar *inserePlacar(Jogador *jogador, ListaPlacar *listaPlacar)
{
    ListaPlacar *celulaAtual = listaPlacar;
    ListaPlacar *novaCelula = (ListaPlacar*)malloc(sizeof(ListaPlacar));
    novaCelula->nome = strdup(retornaNome(jogador));
    novaCelula->pontuacao = retornaVitorias(jogador);
    int index = 2;
    if(celulaAtual->pontuacao < novaCelula->pontuacao)
    {
        novaCelula->prox = celulaAtual;
        printf("Fim de jogo!\n%s sobreviveu %d rodadas e está em 1° lugar no placar!\n", retornaNome(jogador), retornaVitorias(jogador));
        return novaCelula;
    }
    else
    {
        while(celulaAtual->prox != NULL && celulaAtual->prox->pontuacao > novaCelula->pontuacao)
        {
            celulaAtual = celulaAtual->prox;
            index++;
        }
        novaCelula->prox = celulaAtual->prox;
        celulaAtual->prox = novaCelula;
    }

    printf("Fim de jogo!\n%s sobreviveu %d rodadas e está em %d° lugar no placar!\n", retornaNome(jogador), retornaVitorias(jogador), index);

    return listaPlacar; 
}

void destroiListaPlacar(ListaPlacar *listaPlacar)
{   
    ListaPlacar *celulaAtual = listaPlacar;
    ListaPlacar *celulaProx;

    do
    {
        celulaProx = celulaAtual->prox;
        destroiCelulaPlacar(celulaAtual);
        celulaAtual = celulaProx;
    }while(celulaAtual != NULL);
}

void destroiCelulaPlacar(ListaPlacar *celula)
{
    free(celula->nome);
    free(celula);
}