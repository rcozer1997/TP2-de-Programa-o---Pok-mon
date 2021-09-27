#ifndef JOGADOR_H
#define JOGADOR_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pokemon.h"

typedef struct jogador Jogador;

/**
 * @brief Cria a struct com os dados do jogador
 * @param nome nome do jogador
 * @return Jogador* struct Jogador
 */
Jogador *criaJogador(char *nome);

/**
 * @brief Verifica se o nome do jogador está nos padrões corretos 
 * @param nome nome do Jogador
 * @return int Um inteiro para verificar verdadeiro ou falso
 */
int verificaNome(char *nome);

/**
 * @brief Permite ao jogador escolher seus três pokémons iniciais
 * @param jogador struct jogador
 * @param pokemonsIniciais struct lista de Pokemons iniciais
 */
void escolherIniciais(Jogador *jogador, ListaPokemon *pokemonsIniciais);

/**
 * @brief Remove um pokémon da lista de pokémons do jogador
 * @param jogador struct Jogador
 */
void removePokemonListaJogador(Jogador *jogador);

/**
 * @brief Libera da memória os dados armazenados do jogador
 * @param jogador struct Jogador
 */
void destroiJogador(Jogador *jogador);

/**
 * @brief Adiciona um pokémon capturado em batalha na lista de pokémons do jogador
 * @param jogador struct Jogador
 * @param pokemon struct Pokemon
 */
void capturaPokemon(Jogador *jogador, Pokemon *pokemon);

/**
 * @brief Retorna o primeiro pokémon da lista de Pokémons de um jogador
 * @param jogador struct Jogador
 * @return Pokemon* struct do primeiro Pokémon da lista do jogador  
 */
Pokemon *retornaListaJogador(Jogador *jogador);

/**
 * @brief Retorna alguma variável do jogador
 * @param jogador struct Jogador
 * @return int Quantidade de alguma variável do jogador
 * @return char* Nome do jogador  
 */
char *retornaNome(Jogador *jogador);
int retornaQtdPokebolas(Jogador *jogador);
int retornaQtdPokemons(Jogador *jogador);
int retornaVitorias(Jogador *jogador);

/**
 * @brief Altera alguma variável do jogador
 * @param jogador struct Jogador
 * @param qtd Quantidade de alguma variável do jogador
 */
void setterQtdVitoria(Jogador *jogador);
void setterQtdPokemon(Jogador *jogador, int qtd);
void setterQtdPokebolas(Jogador *jogador, int qtd);

#endif