#include "batalha.h"

void menuBatalha(Jogador *jogador, int contadorPartidas, FILE *log, char *arquivoPlacar)
{
    inicializaTabelaAtaques();
    inicializaTabelaDesenhaPokemons();
    int turnoJogador = 1, fugir = 0, contadorBatalhas = 1;

    float chanceMew = 0, chancePokebola = 0;

    Pokemon *pokemonInimigo = selecionaPokemon(numeroAleatorio(5) + 48);
    Pokemon *pokemonAtual = retornaListaJogador(jogador);

    printf("Um %s selvagem apareceu!!!\n\n", retornaNomePokemon(pokemonInimigo));
    fprintf(log,"%d.%d - %s vs %s\n", contadorPartidas, contadorBatalhas, retornaNomePokemon(pokemonAtual), retornaNomePokemon(pokemonInimigo));
    contadorBatalhas++;
    desenhaPokemon(retornaNomePokemon(pokemonInimigo)[0]);
    imprimeVidaBatalha(pokemonAtual, pokemonInimigo);
    while(pokemonAtual != NULL)
    {
        while(retornaHpPokemon(pokemonAtual) > 0 && retornaHpPokemon(pokemonInimigo) > 0)
        {
            if(turnoJogador)
            {
                if(retornaCavar(pokemonAtual) == 1)
                {
                    selecionaAtaque(retornaNumAtaque(pokemonAtual, 2), pokemonAtual, pokemonInimigo, log);
                    imprimeVidaBatalha(pokemonAtual, pokemonInimigo);  
                    imprimeArquivoVidaBatalha(pokemonAtual, pokemonInimigo, log); 
                }
                else
                {
                    if(verificaEfeitos(pokemonAtual))
                    {
                        imprimeMenuOpcoes(jogador, pokemonAtual);
                        fugir = turnoAtual(jogador, pokemonAtual, pokemonInimigo, log);
                        getchar();
                    }
                    else
                    {
                        imprimeVidaBatalha(pokemonAtual, pokemonInimigo);  
                        imprimeArquivoVidaBatalha(pokemonAtual, pokemonInimigo, log); 
                    }
                }
                if(retornaQueimar(pokemonAtual))
                    setterPokemonHp(pokemonAtual, retornaHpPokemon(pokemonAtual) - (retornaHpMaxPokemon(pokemonAtual)/16.0));
                retiraEfeitosPokemon(pokemonAtual);
                turnoJogador = 0;
                getchar();
            }
            else
            {
                if(retornaCavar(pokemonInimigo) == 1)
                {
                    selecionaAtaque(11, pokemonInimigo, pokemonAtual, log);
                }
                else
                {
                    if(verificaEfeitos(pokemonInimigo))
                    {
                        turnoInimigo(jogador, pokemonInimigo, pokemonAtual, log);
                    }
                    else
                    {
                        imprimeVidaBatalha(pokemonAtual, pokemonInimigo);  
                        imprimeArquivoVidaBatalha(pokemonAtual, pokemonInimigo, log); 
                    }
                }
                if(retornaQueimar(pokemonInimigo))
                    setterPokemonHp(pokemonInimigo, retornaHpPokemon(pokemonInimigo) - (retornaHpMaxPokemon(pokemonInimigo)/16.0));
                retiraEfeitosPokemon(pokemonInimigo);

                getchar();

                turnoJogador = 1;
            }
        }
        if(retornaHpPokemon(pokemonAtual) <= 0)
        {
            printf("%s perdeu!\n", retornaNome(jogador));
            fprintf(log,"\t%s perdeu!\n\n", retornaNome(jogador));
            getchar();
            setterQtdPokemon(jogador, -1);
            if(retornaQtdPokemons(jogador) != 0)
            {
                removePokemonListaJogador(jogador);
                pokemonAtual = retornaListaJogador(jogador);
            }
            else    
                break;
            imprimeVidaBatalha(pokemonAtual, pokemonInimigo);
            fprintf(log,"%d.%d - %s vs %s\n", contadorPartidas, contadorBatalhas, retornaNomePokemon(pokemonAtual), retornaNomePokemon(pokemonInimigo));
            contadorBatalhas++;
        }
        else
        {
            if(fugir == 0)
            {
                printf("%s venceu!\n", retornaNome(jogador));
                fprintf(log,"\t%s venceu!\n\n", retornaNome(jogador));
                getchar();

                chanceMew++;
                chancePokebola++;
                
                setterQtdVitoria(jogador);
                fugir = 0;
            }

            destroiPokemon(pokemonInimigo);

            if(probabilidade(chancePokebola/12.0))
                setterQtdPokebolas(jogador, 1);
            if(probabilidade(chanceMew/128.0))
            {
                pokemonInimigo = selecionaPokemon('M');
                chanceMew = 0;
            }
            else
                pokemonInimigo = selecionaPokemon(numeroAleatorio(5) + 48);

            setterPokemonHp(pokemonAtual, retornaHpPokemon(pokemonAtual) + 10);
            resetaEfeitosPokemon(pokemonAtual);
            printf("Um %s selvagem apareceu!!!\n\n", retornaNomePokemon(pokemonInimigo)); 
            fprintf(log,"%d.%d - %s vs %s\n", contadorPartidas, contadorBatalhas, retornaNomePokemon(pokemonAtual), retornaNomePokemon(pokemonInimigo));
            contadorBatalhas++;
            desenhaPokemon(retornaNomePokemon(pokemonInimigo)[0]);
            imprimeVidaBatalha(pokemonAtual, pokemonInimigo);

            turnoJogador = 1;
        }
    }
    destroiPokemon(pokemonInimigo);
    resultadoPlacar(jogador, arquivoPlacar);
    fprintf(log, "\tFim do jogo %d %s sebreviveu %d batalhas\n", contadorPartidas, retornaNome(jogador), retornaVitorias(jogador));
    getchar();
}

void imprimeMenuOpcoes(Jogador *jogador, Pokemon *pokemon)
{
    printf("1- %s\n2- %s\n3- %s\n4- Pokebolas (%d disponiveis)\n5- Fugir\n", retornaNomeAtaque(retornaNumAtaque(pokemon, 0)), retornaNomeAtaque(retornaNumAtaque(pokemon, 1)), retornaNomeAtaque(retornaNumAtaque(pokemon, 2)), retornaQtdPokebolas(jogador));
}

int turnoAtual(Jogador *jogador, Pokemon *pokemonAtacante, Pokemon *pokemonDefensor, FILE *log)
{
    char opcao[10];
    do
    {
        scanf("%s", opcao);   
    } while((atoi(opcao) < 1 || atoi(opcao) > 5) || (atoi(opcao) == 4 && retornaQtdPokebolas(jogador) == 0));

    switch(atoi(opcao))
    {
        case 1:
            selecionaAtaque(retornaNumAtaque(pokemonAtacante, 0), pokemonAtacante, pokemonDefensor, log);
            imprimeVidaBatalha(pokemonAtacante, pokemonDefensor);
            imprimeArquivoVidaBatalha(pokemonAtacante, pokemonDefensor, log);
            break;

        case 2:
            selecionaAtaque(retornaNumAtaque(pokemonAtacante, 1), pokemonAtacante, pokemonDefensor, log);
            imprimeVidaBatalha(pokemonAtacante, pokemonDefensor);
            imprimeArquivoVidaBatalha(pokemonAtacante, pokemonDefensor, log);
            break;

        case 3:
            selecionaAtaque(retornaNumAtaque(pokemonAtacante, 2), pokemonAtacante, pokemonDefensor, log);
            imprimeVidaBatalha(pokemonAtacante, pokemonDefensor);
            imprimeArquivoVidaBatalha(pokemonAtacante, pokemonDefensor, log);
            break;

        case 4:
            printf("Tentativa de captura\n");
            fprintf(log, "\tTentativa de captura\n");
            if(probabilidade(retornaHpMaxPokemon(pokemonDefensor)/retornaHpPokemon(pokemonDefensor)/20.0))
            {
                capturaPokemon(jogador, pokemonDefensor);
                printf("Sucesso!\n");
                fprintf(log,"Sucesso!\n");
                setterPokemonHp(pokemonDefensor, 0);
            }
            else
            {
                printf("Falha!\n");
                fprintf(log,"Falha!\n");
            }
            setterQtdPokebolas(jogador, -1);
            break;

        case 5:
            printf("Tentativa de Fuga\n");
            fprintf(log, "\tTentativa de fuga\n");
            if(probabilidade(1/16.0))
            {
                printf("Sucesso!\n");
                fprintf(log,"Sucesso!\n");
                setterPokemonHp(pokemonDefensor, 0);
                return 1;
            }
            else
            {
                printf("Falha!\n");
                fprintf(log,"Falha!\n");
            }
            break;
    }
    return 0;
}

void turnoInimigo(Jogador *jogador, Pokemon *pokemonAtacante, Pokemon *pokemonDefensor, FILE *log)
{
    int opcao;
    opcao = numeroAleatorio(3);

    switch(opcao)
    {
        case 1:
            selecionaAtaque(retornaNumAtaque(pokemonAtacante, 0), pokemonAtacante, pokemonDefensor, log);
            break;

        case 2:
            selecionaAtaque(retornaNumAtaque(pokemonAtacante, 1), pokemonAtacante, pokemonDefensor, log);
            break;

        case 3:
            selecionaAtaque(retornaNumAtaque(pokemonAtacante, 2), pokemonAtacante, pokemonDefensor, log);
            break;
    }
    imprimeVidaBatalha(pokemonDefensor, pokemonAtacante);
    imprimeArquivoVidaBatalha(pokemonDefensor, pokemonAtacante, log);
}

void imprimeVidaBatalha(Pokemon *pokemonAtual, Pokemon *pokemonInimigo)
{
    printf("%s - %.1f%% HP", retornaNomePokemon(pokemonInimigo), retornaPocentagemHp(pokemonInimigo));
    imprimeEfeitosPokemon(pokemonInimigo);
    printf("%s - %.1f%% HP", retornaNomePokemon(pokemonAtual), retornaPocentagemHp(pokemonAtual));
    imprimeEfeitosPokemon(pokemonAtual);
    printf("\n");
}

void imprimeArquivoVidaBatalha(Pokemon *pokemonAtual, Pokemon *pokemonInimigo, FILE *log)
{
    fprintf(log, "\t%s - %.1f%% HP", retornaNomePokemon(pokemonAtual), retornaPocentagemHp(pokemonAtual));
    imprimeArquivoEfeitosPokemon(pokemonAtual, log);
    fprintf(log, "\t%s - %.1f%% HP", retornaNomePokemon(pokemonInimigo), retornaPocentagemHp(pokemonInimigo));
    imprimeArquivoEfeitosPokemon(pokemonInimigo, log);
    fprintf(log,"\n");
}

int numeroAleatorio(int randMax)
{
    int aleatorio =  rand() % randMax + 1;
    return aleatorio;
}

int probabilidade(float probabilidade)
{
    float aleatorio = (float)rand()/(float)(RAND_MAX);
    if(aleatorio <= probabilidade)
        return 1;
    else
        return 0;
}