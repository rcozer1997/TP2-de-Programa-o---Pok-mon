#ifndef ATAQUE_H
#define ATAQUE_H

#include "pokemon.h"
#include "batalha.h"


/**
 * @brief Retorna o dano do ataque
 * @param poder Valor do poder do ataque do pokémon atacante
 * @param forca Força do pokémon atacante
 * @param defesa Defesa do pokémon defensor
 * @param mt Valor do MT do ataque 
 * @param relacaoTipo Relação entre os tipos dos Pokémon
 * @return float Dano calculado durante o ataque 
 */
float calculaDano(int poder, int forca, int defesa, float mt, float relacaoTipo);

/**
 * @brief Retorna o nome do ataque 
 * @param ataque código do ataque
 * @return char* O nome do ataque 
 */
char* retornaNomeAtaque(int ataque);

/**
 * @brief Verifica a relação entre os tipos dos pokémons
 * @param pokemonAtacante struct do Pokémon atacante
 * @param pokemonDefensor struct do Pokémon defensor
 * @return float A relação de dano dos pokemons de acordo com o tipo dos pokémons
 */
float relacaoTipos(Pokemon* pokemonAtacante, Pokemon* pokemonDefensor);

/**
 * @brief Imprime no arquivo log, e no terminal, um ataque realizado durante uma batalha
 * @param pokemon struct Pokémon
 * @param numeroAtaque código do ataque
 * @param log arquivo log
 */
void imprimeLogAtaque(Pokemon *pokemon, int numeroAtaque,FILE *log);

/**
 * @brief Seleciona os ataques durante as batalhas
 * @param pokemonAtacante struct do Pokémon atacante
 * @param pokemonDefensor struct do Pokémon defensor
 * @param log arquivo log
 * @param code código do ataque na dispatch table
 */
void selecionaAtaque(int code, Pokemon *pokemonAtacante, Pokemon *pokemonDefensor,FILE *log);

/**
 * @brief Inicializa a dispatch table de ataques
 */
void inicializaTabelaAtaques();

/**
 * @brief Aplica os respectivos ataques aos pokémons durante a batalha, conforme selecionados
 * @param pokemonAtacante struct do Pokémon atacante
 * @param pokemonDefensor struct do Pokémon defensor
 * @param log arquivo log
 */
void choqueDoTrovao(Pokemon *pokemonAtacante, Pokemon *pokemonDefensor,FILE *log);
void ondaDeChoque(Pokemon *pokemonAtacante, Pokemon *pokemonDefensor,FILE *log);
void bater(Pokemon *pokemonAtacante, Pokemon *pokemonDefensor,FILE *log);
void lancaChamas(Pokemon *pokemonAtacante, Pokemon *pokemonDefensor,FILE *log);
void dormir(Pokemon *pokemonAtacante, Pokemon *pokemonDefensor,FILE *log);
void armaDeAgua(Pokemon *pokemonAtacante, Pokemon *pokemonDefensor,FILE *log);
void proteger(Pokemon *pokemonAtacante, Pokemon *pokemonDefensor,FILE *log);
void poDeSono(Pokemon *pokemonAtacante, Pokemon *pokemonDefensor,FILE *log);
void bombaDeSemente(Pokemon *pokemonAtacante, Pokemon *pokemonDefensor,FILE *log);
void doisGumes(Pokemon *pokemonAtacante, Pokemon *pokemonDefensor,FILE *log);
void raboDeFerro(Pokemon *pokemonAtacante, Pokemon *pokemonDefensor,FILE *log);
void cavar(Pokemon *pokemonAtacante, Pokemon *pokemonDefensor,FILE *log);
void metronomo(Pokemon *pokemonAtacante, Pokemon *pokemonDefensor,FILE *log);
void autoDestruir(Pokemon *pokemonAtacante, Pokemon *pokemonDefensor,FILE *log);

#endif