#ifndef POKEMON_H
#define POKEMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pokemon Pokemon;

typedef struct listaPokemon ListaPokemon; 

/**
 * @brief Inicia a Lista Pokémon com um Pokémon
 * @param pokemon struct Pokémon
 * @return ListaPokemon Uma nova struct lista de Pokémon  
 */
ListaPokemon *iniciaLista(Pokemon *pokemon);

/**
 * @brief Insere um Pokémon na lista de Pokémon
 * @param pokemon struct Pokémon
 * @param celulaAtual struct Celula atual na lista Pokémon
 * @return ListaPokemon* Uma struct lista com um novo Pokémon inserido
 */
ListaPokemon *inserePokemon(ListaPokemon *celulaAtual, Pokemon *pokemon);

/**
 * @brief Imprime a lista de Pokémons
 * @param lista struct Lista Pokémon
 */
void imprimeListaPokemon(ListaPokemon *lista);

/**
 * @brief Remove a célula de um Pokemon da lista de Pokémons
 * @param lista struct Lista de Pokémon
 * @param posicaoPokemon Posição da célula do Pokémon na lista
 * @return ListaPokemon* Uma struct lista com um pokémon removido
 */
ListaPokemon *removePokemonLista(ListaPokemon *lista, int posicaoPokemon);

/**
 * @brief Libera da memória os dados de todas as células da lista Pokémon
 * @param lista struct Lista de Pokémons
 */
void destroiListaPokemon(ListaPokemon *lista);

/**
 * @brief Libera da memória os dados de uma célula da lista de Pokémons
 * @param celula struct Célula na lista Pokémon
 */
void destroiCelula(ListaPokemon *celula);

/**
 * @brief Libera da memória os dados armazenados do Pokémon
 * @param pokemon struct Pokémon
 */
void destroiPokemon(Pokemon *pokemon);

/**
 * @brief Transforma o tipo char* do Pokémon em um número int  
 * @param pokemon struct Pokémon
 * @return int Código do tipo do Pokémon
 */
int converteTipo(Pokemon *pokemon);


/**
 * @brief Diminui em um os efeitos ativos no pokémon
 * @param pokemon struct Pokémon
 */
void retiraEfeitosPokemon(Pokemon *pokemon);


/**
 * @brief Imprime os efeitos ativos no pokémon
 * @param pokemon struct Pokémon
 */
void imprimeEfeitosPokemon(Pokemon *pokemon);

/**
 * @brief Imprime no arquivo log os efeitos ativos no pokémon
 * @param pokemon struct Pokémon
 * @param log Arquivo de log
 */
void imprimeArquivoEfeitosPokemon(Pokemon *pokemon, FILE *log);

/**
 * @brief Verifica efeitos ativos que impossibilitam o Pokémon de atacar
 * @param pokemon struct Pokémon
 * @return int Verifica os efeitos ativos
 */
int verificaEfeitos(Pokemon *pokemon);

/**
 * @brief Reseta todos os efeitos de um Pokémon
 * @param pokemon struct Pokémon
 */
void resetaEfeitosPokemon(Pokemon *pokemon);

/**
 * @brief Retorna a struct de um Pokémon da lista de Pokémons
 * @param listaPokemon struct Lista de Pokémons
 * @return Pokemon struct Pokémon
 */
Pokemon *retornaPokemon(ListaPokemon* listaPokemon);

/**
 * @brief Retorna alguma variável do Pokémon
 * @param pokemon struct Pokémon
 * @param num  Código do ataque
 * @param lista struct lista Pokémons
 * @param posicaoPokemon Posição do Pokémon na lista
 * @return int Variável Pokémon
 * @return float Variável Pokémon
 * @return char* Nome Pokémon
 */
char *retornaNomePokemon(Pokemon *pokemon);
char* retornaNomePokemonLista(ListaPokemon *lista, int posicaoPokemon);
float retornaHpPokemon(Pokemon* pokemon);
float retornaHpMaxPokemon(Pokemon* pokemon);
float retornaPocentagemHp(Pokemon* pokemon);
int retornaForca(Pokemon* pokemon);
int retornaDefesa(Pokemon* pokemon);
int retornaNumAtaque(Pokemon* pokemon, int num);
int retornaDomindo(Pokemon* pokemon);
int retornaSono(Pokemon* pokemon);
int retornaQueimar(Pokemon* pokemon);
int retornaParalisado(Pokemon* pokemon);
int retornaCavar(Pokemon* pokemon);
int retornaProtegido(Pokemon* pokemon);


/**
 * @brief Altera alguma variável do Pokémon
 * @param pokemon struct Pokémon
 * @param turnos Quantidade de turnos
 * @param hp Hp do Pokémon
 */
void setterDormindo(Pokemon *pokemon, int turnos);
void setterSono(Pokemon *pokemon, int turnos);
void setterQueimar(Pokemon *pokemon, int turnos);
void setterParalisado(Pokemon *pokemon, int turnos);
void setterPokemonHp(Pokemon *pokemon, float hp);
void setterCavar(Pokemon *pokemon, int turnos);
void setterProtegido(Pokemon *pokemon, int turnos);

/**
 * @brief Inicializa a dispatch table de Pokémons
 */
void inicializaTabelaPokemons();

/**
 * @brief Chama a função para selecionar os Pokémons através da dispatch table de Pokémons
 * @param code Código do pokémon
 * @return Pokemon Retorna a função do pokémon
 */
Pokemon *selecionaPokemon(char code);

/**
 * @brief Cria uma struct para cada pokémon armazenando seus dados na memória com malloc
 * @return Pokemon Uma struct preenchida para o pokémon 
 */
Pokemon *pikachu();
Pokemon *charizard();
Pokemon *blastoise();
Pokemon *venosauro();
Pokemon *steelix();
Pokemon *mew();

/**
 * @brief Inicializa a dispatch table de desenhos dos pokémon
 */
void inicializaTabelaDesenhaPokemons();

/**
 * @brief Chama a função para desenhar os pokémons através da dispatch table de desenhos dos pokémons.
 * @param code Código do pokémon
 */
void desenhaPokemon(char code);

/**
 * @brief Printa imagem dos respectivos pokémon na tela de batalha
 */
void desenhaPikachu();
void desenhaCharizard();
void desenhaBlastoise();
void desenhaVenosauro();
void desenhaSteelix();
void desenhaMew();

#endif