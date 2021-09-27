#include "jogador.h"

struct jogador
{
    char *nome;
    int qtdPokemons;
    int qtdPokebolas;
    int vitorias;
    ListaPokemon *listaPokemon;
    ListaPokemon *celulaAtual;
};

Jogador *criaJogador(char *nome)
{
    Jogador *jogador = (Jogador*)calloc(1, sizeof(Jogador));

    jogador->nome = strdup(nome);
    jogador->qtdPokemons = 0;
    jogador->qtdPokebolas = 3;
    jogador->vitorias = 0;
    jogador->listaPokemon = NULL;
    jogador->celulaAtual = NULL;

    return jogador;
}

int verificaNome(char *nome)
{
    for(int i = 0; i < strlen(nome); i++)
    {
        if((isalpha(nome[i]) == 0) && (nome[i] != '_'))
        {
            printf("Digite um nome valido!!!\n");
            return 0;
        }
    }
    return 1;
}

void escolherIniciais(Jogador *jogador, ListaPokemon *pokemonsIniciais)
{
    int qtdIniciais = 6;
    char opcao[10];
    while(jogador->qtdPokemons < 3)
    {
        system("clear");
        printf("Escolha 1 dos %d pokemons iniciais!\n", qtdIniciais);
        imprimeListaPokemon(pokemonsIniciais);
        do
        {
            scanf("%s", opcao);
        }
        while (atoi(opcao) <= 0 || atoi(opcao) > qtdIniciais);

        char *nomePokemon = retornaNomePokemonLista(pokemonsIniciais, atoi(opcao) - 1);

        if(qtdIniciais == 6)
        {
            jogador->listaPokemon = iniciaLista(selecionaPokemon(nomePokemon[0]));
            jogador->celulaAtual = jogador->listaPokemon;
        }
        else
        {
            jogador->celulaAtual = inserePokemon(jogador->celulaAtual, selecionaPokemon(nomePokemon[0]));
        }
        pokemonsIniciais = removePokemonLista(pokemonsIniciais, atoi(opcao) - 1);
        jogador->qtdPokemons++;
        qtdIniciais--;
    }
    jogador->qtdPokemons = 3;
    destroiListaPokemon(pokemonsIniciais);
}

void removePokemonListaJogador(Jogador *jogador)
{ 
    jogador->listaPokemon = removePokemonLista(jogador->listaPokemon, 0);
}

void destroiJogador(Jogador *jogador)
{
    destroiListaPokemon(jogador->listaPokemon);
    free(jogador->nome);
    free(jogador);
}

void capturaPokemon(Jogador *jogador, Pokemon *pokemon)
{
    jogador->celulaAtual = inserePokemon(jogador->celulaAtual, selecionaPokemon(retornaNomePokemon(pokemon)[0]));
    jogador->qtdPokemons++;
}

char *retornaNome(Jogador *jogador)
{
    return jogador->nome;
}

Pokemon *retornaListaJogador(Jogador *jogador)
{
    return retornaPokemon(jogador->listaPokemon);
}

int retornaQtdPokebolas(Jogador *jogador)
{
    return jogador->qtdPokebolas;
}

int retornaQtdPokemons(Jogador *jogador)
{
    return jogador->qtdPokemons;
}

int retornaVitorias(Jogador *jogador)
{
    return jogador->vitorias;
}

void setterQtdVitoria(Jogador *jogador)
{
    jogador->vitorias++;
}

void setterQtdPokemon(Jogador *jogador, int qtd)
{
    jogador->qtdPokemons += qtd;
}

void setterQtdPokebolas(Jogador *jogador, int qtd)
{
    jogador->qtdPokebolas += qtd;
}