#ifndef PLACAR_H
#define PLACAR_H

#include "jogador.h"

typedef struct listaPlacar ListaPlacar;

/**
 * @brief Altera o arquivo de placares ao final de cada partida
 * @param jogador struct Jogador
 * @param arquivoPlacar caminho do arquivo de placares
 */
void resultadoPlacar(Jogador *jogador, char *arquivoPlacar);

/**
 * @brief Cria uma lista de placares com os placares do arquivo de placares
 * @param arquivoPlacar caminho do arquivo de placares
 * @return ListaPlacar* Uma struct lista de placares
 */
ListaPlacar *criaListaPlacar(char *arquivoPlacar);

/**
 * @brief Imprime a lista de placares ordenada no arquivo de placares
 * @param listaPlacar struct lista de placares
 * @param arquivoPlacar caminho do arquivo de placares
 */
void imprimeListaPlacarArquivo(ListaPlacar *listaPlacar, char *arquivoPlacar);

/**
 * @brief Imprime os placares do arquivo de placares
 * @param arquivoPlacar caminho do arquivo de placares
 */
void imprimePlacar(char *arquivoPlacar);

/**
 * @brief Insere um placar na lista de placares
 * @param jogador struct Jogador
 * @param listaplacar struct lista de placares
 * @return ListaPlacar* Uma struct lista placares com um novo placar adicionado
 */
ListaPlacar *inserePlacar(Jogador *jogador, ListaPlacar *listaPlacar);

/**
 * @brief Libera da memória os dados de todas as células da lista de Placares
 * @param listaPlacar struct Lista de placares
 */
void destroiListaPlacar(ListaPlacar *listaPlacar);

/**
 * @brief Libera da memória os dados de uma célula da lista de placar
 * @param celula struct Celula da lista de placar
 */
void destroiCelulaPlacar(ListaPlacar *celula);

#endif