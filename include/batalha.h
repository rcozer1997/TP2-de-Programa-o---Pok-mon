#ifndef BATALHA_H 
#define BATALHA_H 

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#include "jogador.h" 
#include "ataque.h" 
#include "placar.h" 

/**
 * @brief Inicializa o menu de batalha
 * @param jogador struct Jogador
 * @param contadorPartidas Contador da quantidade de partidas jogadas
 * @param log Arquivo log
 * @param arquivoPlacar Caminho do arquivo de placares
 */
void menuBatalha(Jogador *jogador, int contadorPartidas, FILE *log, char *arquivoPlacar); 

/**
 * @brief Imprime as opções do jogador durante as partidas
 * @param jogador struct Jogador
 * @param Pokemon struct Pokemon
 */
void imprimeMenuOpcoes(Jogador *jogador, Pokemon *pokemon); 

/**
 * @brief Inicializa turno do jogador
 * @param jogador struct Jogador
 * @param pokemonAtacante struct do Pokémon atacante
 * @param pokemonDefensor struct do Pokémon defensor
 * @param log Arquivo log
 * @return int Verdadeiro ou falso para verificar se o pokémon conseguiu fugir da batalha
 */
int turnoAtual(Jogador *jogador, Pokemon *pokemonAtacante, Pokemon *pokemonDefensor, FILE *log); 

/**
 * @brief Inicializa turno do inimigo
 * @param jogador struct Jogador
 * @param pokemonAtacante struct do Pokémon atacante
 * @param pokemonDefensor struct do Pokémon defensor
 * @param log Arquivo log
 */
void turnoInimigo(Jogador *jogador, Pokemon *pokemonAtacante, Pokemon *pokemonDefensor, FILE *log); 

/**
 * @brief Imprime a vida atual dos pokémons em batalha
 * @param pokemonAtual struct do Pokémon atual em batalha
 * @param pokemonInimigo struct do Pokémon inimigo
 */
void imprimeVidaBatalha(Pokemon *pokemonAtual, Pokemon *pokemonInimigo); 

/**
 * @brief Imprime a vida atual dos pokémons em batalha no arquivo log
 * @param pokemonAtual struct do Pokémon atual em batalha
 * @param pokemonInimigo struct do Pokémon inimigo
 * @param log arquivo log
 */  
void imprimeArquivoVidaBatalha(Pokemon *pokemonAtual, Pokemon *pokemonInimigo, FILE *log); 

/**
 * @brief Sorteia um número aleatório
 * @param randMax Número máximo limite para o sorteio
 * @return int Número sorteado
 */
int numeroAleatorio(int randMax); 

/**
 * @brief Verifica se ocorreu uma ação de acordo com a probabilidade da mesma
 * @param probabilidade probabilidade da ação ocorrer
 * @return int Verdadeiro ou falso para a ação
 */
int probabilidade(float probabilidade); 
 
#endif 