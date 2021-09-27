#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jogador.h"
#include "batalha.h"

/**
 * @brief Inicializa o menu principal
 * @param arquivoPlacar caminho do arquivo de placares
 * @param arquivoLog  caminho do arquivo log
 */
void menuPrincipal(char* arquivoPlacar, char* arquivoLog);

/**
 * @brief Imprime as opções do menu principal
 */
void imprimeMenuPrincipal();

/**
 * @brief Menu para que o jogador possa escolher os Pokémons iniciais
 * @param jogador struct Jogador
 */
void menuIniciais(Jogador *jogador);

#endif