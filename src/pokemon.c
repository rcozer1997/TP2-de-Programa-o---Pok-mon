#include "pokemon.h"

struct pokemon
{
    char *nome;
    char *tipo;
    int ataque[3];
    int forca;
    int defesa;
    float hpMax;
    float hp;
    //efeitos
    int paralisado;
    int sono;
    int dormindo;
    int queimar;
    int cavar;
    int protegido;
};

struct listaPokemon
{
    Pokemon *pokemon;
    struct listaPokemon *prox;
};

typedef Pokemon* (*fptrPokemon)();

fptrPokemon pokemons[128] = {NULL};

typedef void (*fptrDesenhaPokemon)();

fptrDesenhaPokemon desenhaPokemons[128] = {NULL};

ListaPokemon *iniciaLista(Pokemon *pokemon)
{
    ListaPokemon *iniciais = (ListaPokemon*)malloc(sizeof(ListaPokemon));
    iniciais->pokemon = pokemon;
    iniciais->prox = NULL;
    return iniciais;
}

ListaPokemon *inserePokemon(ListaPokemon *celulaAtual, Pokemon *pokemon)
{
    celulaAtual->prox = (ListaPokemon*)malloc(sizeof(ListaPokemon));
    celulaAtual = celulaAtual->prox;
    celulaAtual->pokemon = pokemon;
    celulaAtual->prox = NULL;
    return celulaAtual;
}

void imprimeListaPokemon(ListaPokemon *lista)
{
    ListaPokemon * celula;
    celula = lista;

    int index = 1;
    do{
        printf("%d - %s\n", index,  retornaNomePokemon(celula->pokemon));
        celula = celula->prox;
        index++;
    }while (celula != NULL);
}

ListaPokemon *removePokemonLista(ListaPokemon *lista, int posicaoPokemon)
{
    ListaPokemon *celulaAnterior = NULL;
    ListaPokemon *celulaAtual = lista;
    int index = 0;
    while(celulaAtual != NULL && index != posicaoPokemon)
    {
        celulaAnterior = celulaAtual;
        celulaAtual = celulaAtual->prox;
        index++;
    }
    if(celulaAtual == NULL)
        return lista;
    if(index == posicaoPokemon)
    {
        if(index == 0)
        {
            lista = celulaAtual->prox;
            destroiCelula(celulaAtual);
        }
        else
        {
            celulaAnterior->prox = celulaAtual->prox;
            destroiCelula(celulaAtual);
        }
    }
    return lista;
}

void destroiListaPokemon(ListaPokemon *lista)
{   
    ListaPokemon *celulaAtual = lista;
    ListaPokemon *celulaProx;

    do
    {
        celulaProx = celulaAtual->prox;
        destroiCelula(celulaAtual);
        celulaAtual = celulaProx;
    }while(celulaAtual != NULL);
}

void destroiCelula(ListaPokemon *celula)
{
    destroiPokemon(celula->pokemon);
    free(celula);
}

void destroiPokemon(Pokemon *pokemon)
{
    free(pokemon->nome);
    free(pokemon->tipo);
    free(pokemon);
}

int converteTipo(Pokemon *pokemon)
{
    if(strcmp(pokemon->tipo, "Fogo") == 0) return 0;
    if(strcmp(pokemon->tipo, "Agua") == 0) return 1;
    if(strcmp(pokemon->tipo, "Planta") == 0) return 2;
    if(strcmp(pokemon->tipo, "Eletrico") == 0) return 3;
    if(strcmp(pokemon->tipo, "Psiquico") == 0) return 4;
    if(strcmp(pokemon->tipo, "Metal") == 0) return 5;
}

void retiraEfeitosPokemon(Pokemon *pokemon)
{
    if(pokemon->paralisado > 0)
        pokemon->paralisado--;
    if(pokemon->sono > 0)
        pokemon->sono--;
    if(pokemon->dormindo > 0)
    {
        pokemon->dormindo--;
        if(pokemon->dormindo == 0)
            pokemon->hp = pokemon->hpMax;
    }
    if(pokemon->cavar > 0)
        pokemon->cavar--;
    if(pokemon->protegido > 0)
        pokemon->protegido--;
}

void imprimeEfeitosPokemon(Pokemon *pokemon)
{
    if(pokemon->paralisado != 0 || pokemon->dormindo != 0 || pokemon->queimar != 0 || pokemon->protegido != 0 || pokemon->sono != 0)
        printf(" (");
    if(pokemon->paralisado > 0) printf(" Paralisado ");
    if(pokemon->sono > 0 || pokemon->dormindo > 0) printf(" Dormindo ");
    if(pokemon->queimar > 0) printf(" Queimando ");
    if(pokemon->cavar > 0 || pokemon->protegido > 0) printf(" Protegido ");
    if(pokemon->paralisado != 0 || pokemon->dormindo != 0 || pokemon->queimar != 0 || pokemon->protegido != 0 || pokemon->sono != 0)
        printf(")");
    printf("\n");
}

void imprimeArquivoEfeitosPokemon(Pokemon *pokemon, FILE *log)
{
    if(pokemon->paralisado != 0 || pokemon->dormindo != 0 || pokemon->queimar != 0 || pokemon->protegido != 0 || pokemon->sono != 0)
        fprintf(log," (");
    if(pokemon->paralisado > 0) fprintf(log," Paralisado ");
    if(pokemon->sono > 0 || pokemon->dormindo > 0) fprintf(log," Dormindo ");
    if(pokemon->queimar > 0) fprintf(log," Queimando ");
    if(pokemon->cavar > 0 || pokemon->protegido > 0) fprintf(log," Protegido ");
    if(pokemon->paralisado != 0 || pokemon->dormindo != 0 || pokemon->queimar != 0 || pokemon->protegido != 0 || pokemon->sono != 0)
        fprintf(log,")");
    fprintf(log, "\n");
}

int verificaEfeitos(Pokemon *pokemon)
{
    if(retornaParalisado(pokemon) == 0 && retornaDomindo(pokemon) == 0 && retornaSono(pokemon) == 0 && retornaCavar(pokemon) == 0)
        return 1;
    return 0;
}

void resetaEfeitosPokemon(Pokemon *pokemon)
{
    pokemon->paralisado = 0;
    pokemon->sono = 0;
    pokemon->dormindo = 0;
    pokemon->queimar = 0;
    pokemon->cavar = 0;
    pokemon->protegido = 0;
}

char *retornaNomePokemon(Pokemon *pokemon)
{
    return pokemon->nome;
}

char* retornaNomePokemonLista(ListaPokemon *lista, int posicaoPokemon)
{
    int index = 0;
    ListaPokemon *celulaAtual = lista;

    while(celulaAtual != NULL && index != posicaoPokemon)
    {
        celulaAtual = celulaAtual->prox;
        index++;
    }
    if(celulaAtual != NULL && index == posicaoPokemon)
        return retornaNomePokemon(celulaAtual->pokemon);
    printf("ERRO. Pokemon nao encontrado!!!\n");
    return NULL;
}

Pokemon *retornaPokemon(ListaPokemon* listaPokemon)
{
    return listaPokemon->pokemon;
}

float retornaHpPokemon(Pokemon* pokemon)
{
    return pokemon->hp;
}

float retornaHpMaxPokemon(Pokemon* pokemon)
{
    return pokemon->hpMax;
}

float retornaPocentagemHp(Pokemon* pokemon)
{
    return (pokemon->hp/pokemon->hpMax)*100.0;
}

int retornaForca(Pokemon* pokemon)
{
    return pokemon->forca;
}

int retornaDefesa(Pokemon* pokemon)
{
    return pokemon->defesa;
}


int retornaNumAtaque(Pokemon* pokemon, int num)
{
    return pokemon->ataque[num];
}

int retornaDomindo(Pokemon* pokemon)
{
    return pokemon->dormindo;
}

int retornaSono(Pokemon* pokemon)
{
    return pokemon->sono;
}

int retornaQueimar(Pokemon* pokemon)
{
    return pokemon->queimar;
}

int retornaParalisado(Pokemon* pokemon)
{
    return pokemon->paralisado;
}

int retornaCavar(Pokemon* pokemon)
{
    return pokemon->cavar;
}

int retornaProtegido(Pokemon* pokemon)
{
    return pokemon->protegido;
}

void setterDormindo(Pokemon *pokemon, int turnos)
{
    if(turnos > pokemon->dormindo)
        pokemon->dormindo = turnos;
}

void setterSono(Pokemon *pokemon, int turnos)
{
    if(turnos > pokemon->sono)
        pokemon->sono = turnos;
}

void setterQueimar(Pokemon *pokemon, int turnos)
{
    if(strcmp(pokemon->tipo, "Fogo") != 0)
        if(turnos > pokemon->queimar)
            pokemon->queimar = turnos;
}

void setterParalisado(Pokemon *pokemon, int turnos)
{
    if(turnos > pokemon->paralisado)
        pokemon->paralisado = turnos;
}

void setterCavar(Pokemon *pokemon, int turnos)
{
    if(turnos > pokemon->cavar)
        pokemon->cavar = turnos;
}

void setterProtegido(Pokemon *pokemon, int turnos)
{
    if(turnos > pokemon->protegido)
        pokemon->protegido = turnos;
}

void setterPokemonHp(Pokemon *pokemon, float hp)
{
    pokemon->hp = hp;
    if(pokemon->hp < 0)
        pokemon->hp = 0;
    if(pokemon->hp > pokemon->hpMax)
        pokemon->hp = pokemon->hpMax;
}

void inicializaTabelaPokemons()
{
  pokemons['P'] = pikachu;
  pokemons['1'] = pikachu;

  pokemons['C'] = charizard;
  pokemons['2'] = charizard;

  pokemons['B'] = blastoise;
  pokemons['3'] = blastoise;

  pokemons['V'] = venosauro;
  pokemons['4'] = venosauro;

  pokemons['S'] = steelix;
  pokemons['5'] = steelix;
  
  pokemons['M'] = mew;
}

Pokemon *selecionaPokemon(char code)
{
   return pokemons[code]();
}

Pokemon *pikachu()
{
    Pokemon* pikachu = (Pokemon*)malloc(sizeof(Pokemon));

    pikachu->nome = strdup("Pikachu");
    pikachu->hpMax = 200;
    pikachu->hp = 200;
    pikachu->forca = 110;
    pikachu->defesa = 100;
    pikachu->tipo = strdup("Eletrico");
    pikachu->ataque[0] = 0;
    pikachu->ataque[1] = 1;
    pikachu->ataque[2] = 2;
    pikachu->paralisado = 0;
    pikachu->sono = 0;
    pikachu->dormindo = 0;
    pikachu->queimar = 0;
    pikachu->cavar = 0;
    pikachu->protegido = 0;

    return pikachu;
}

Pokemon *charizard()
{
    Pokemon* charizard = (Pokemon*)malloc(sizeof(Pokemon));

    charizard->nome = strdup("Charizard");
    charizard->hpMax = 260;
    charizard->hp = 260;
    charizard->forca = 160;
    charizard->defesa = 150;
    charizard->tipo = strdup("Fogo");
    charizard->ataque[0] = 3;
    charizard->ataque[1] = 4;
    charizard->ataque[2] = 2;
    charizard->paralisado = 0;
    charizard->sono = 0;
    charizard->dormindo = 0;
    charizard->queimar = 0;
    charizard->cavar = 0;
    charizard->protegido = 0;

    return charizard;
}

Pokemon *blastoise()
{
    Pokemon* blastoise = (Pokemon*)malloc(sizeof(Pokemon));

    blastoise->nome = strdup("Blastoise");
    blastoise->hpMax = 280;
    blastoise->hp = 280;
    blastoise->forca = 180;
    blastoise->defesa = 200;
    blastoise->tipo = strdup("Agua");
    blastoise->ataque[0] = 5;
    blastoise->ataque[1] = 6;
    blastoise->ataque[2] = 2;
    blastoise->paralisado = 0;
    blastoise->sono = 0;
    blastoise->dormindo = 0;
    blastoise->queimar = 0;
    blastoise->cavar = 0;
    blastoise->protegido = 0;

    return blastoise;
}

Pokemon *venosauro()
{
    Pokemon* venosauro = (Pokemon*)malloc(sizeof(Pokemon));

    venosauro->nome = strdup("Venosauro");
    venosauro->hpMax = 300;
    venosauro->hp = 300;
    venosauro->forca = 160;
    venosauro->defesa = 160;
    venosauro->tipo = strdup("Planta");
    venosauro->ataque[0] = 7;
    venosauro->ataque[1] = 8;
    venosauro->ataque[2] = 9;
    venosauro->paralisado = 0;
    venosauro->sono = 0;
    venosauro->dormindo = 0;
    venosauro->queimar = 0;
    venosauro->cavar = 0;
    venosauro->protegido = 0;

    return venosauro;
}

Pokemon *steelix()
{
    Pokemon* steelix = (Pokemon*)malloc(sizeof(Pokemon));

    steelix->nome = strdup("Steelix");
    steelix->hpMax = 280;
    steelix->hp = 280;
    steelix->forca = 170;
    steelix->defesa = 400;
    steelix->tipo = strdup("Metal");
    steelix->ataque[0] = 10;
    steelix->ataque[1] = 4;
    steelix->ataque[2] = 11;
    steelix->paralisado = 0;
    steelix->sono = 0;
    steelix->dormindo = 0;
    steelix->queimar = 0;
    steelix->cavar = 0;
    steelix->protegido = 0;

    return steelix;
}

Pokemon *mew()
{
    Pokemon* mew = (Pokemon*)malloc(sizeof(Pokemon));

    mew->nome = strdup("Mew");
    mew->hpMax = 320;
    mew->hp = 320;
    mew->forca = 200;
    mew->defesa = 200;
    mew->tipo = strdup("Psiquico");
    mew->ataque[0] = 12;
    mew->ataque[1] = 2;
    mew->ataque[2] = 13;
    mew->paralisado = 0;
    mew->sono = 0;
    mew->dormindo = 0;
    mew->queimar = 0;
    mew->cavar = 0;
    mew->protegido = 0;

    return mew;
}

void inicializaTabelaDesenhaPokemons()
{
  desenhaPokemons['P'] = desenhaPikachu;
  desenhaPokemons['C'] = desenhaCharizard;
  desenhaPokemons['B'] = desenhaBlastoise;
  desenhaPokemons['V'] = desenhaVenosauro;
  desenhaPokemons['S'] = desenhaSteelix;
  desenhaPokemons['M'] = desenhaMew;
}

void desenhaPokemon(char code)
{
   desenhaPokemons[code]();
}

void desenhaPikachu()
{
    printf(" ====================================================================\n");
    printf("||                            _..----\"\"---.'      /                 ||\n");
    printf("||      _.....---------...,-\"\"                  ,'                  ||\n");
    printf("||      `-._  \\                                /                    ||\n");
    printf("||          `-.+_            __           ,--. .                    ||\n");
    printf("||               `-.._     .:  ).        (`--\"| \\                   ||\n");
    printf("||                    7    | `\" |         `...'  \\                  ||\n");
    printf("||                    |     `--'     '+\"        ,\". ,\"\"-            ||\n");
    printf("||                    |   _...        .____     | |/    '           ||\n");
    printf("||               _.   |  .    `.  '--\"   /      `./     j           ||\n");
    printf("||              \\' `-.|  '     |   `.   /        /     /            ||\n");
    printf("||              '     `-. `---\"      `-\"        /     /             ||\n");
    printf(" ====================================================================\n");
    printf("\n");
}

void desenhaCharizard()
{
    printf(" ====================================================================\n");
    printf("||                   `--Y.'      ___.                _              ||\n");
    printf("||                        \\     L._, \\                _             ||\n");
    printf("||              _.,        `.   <  <\\                _              ||\n");
    printf("||            ,' '           `, `.   | \\            ( `             ||\n");
    printf("||         ../, `.            `  |    .\\`.           \\ \\_           ||\n");
    printf("||        ,' ,..  .           _.,'    ||\\l            )  '\".        ||\n");
    printf("||       , ,'   \\           ,'.-.`-._,'  |           .  _._`.       ||\n");
    printf("||     ,' /      \\ \\        `' ' `--/   | \\          / /   ..\\      ||\n");
    printf("||   .'  /        \\ .         |\\__ - _ ,'` `        / /     `.`.    ||\n");
    printf("||   |  '          ..         `-...-\"  |  `-'      / /        . `.  ||\n");
    printf("||   | /           |L__           |    |          / /          `. ` ||\n");
    printf("||  , /            .   .          |    |         / /             ` `||\n");
    printf(" ====================================================================\n");
    printf("\n");
}

void desenhaBlastoise()
{
    printf(" ====================================================================\n");
    printf("||                 _,..-\"\"\"--' `,.-\".                               ||\n");
    printf("||               ,'      __.. --',  |                               ||\n");
    printf("||             _/   _.-\"' |    .' | |       ____                    ||\n");
    printf("||       ,.-\"\"'    `-\"+.._|     `.' | `-..,',--.`.                  ||\n");
    printf("||      |   ,.                      '    j 7    l \\__               ||\n");
    printf("||      |.-'                            /| |    j||  .              ||\n");
    printf("||      `.                   |         / L`.`\"\"','|\\  \\             ||\n");
    printf("||        `.,----..._       ,'`\"'-.  ,'   \\ `\"\"'  | |  l            ||\n");
    printf("||          Y        `-----'       v'    ,'`,.__..' |   .           ||\n");
    printf("||           `.                   /     /   /     `.|   |           ||\n");
    printf("||             `.                /     l   j       ,^.  |L          ||\n");
    printf("||               `._            L       +. |._   .' \\|  | \\         ||\n");
    printf(" ====================================================================\n");
    printf("\n");
}

void desenhaVenosauro()
{
    printf(" ====================================================================\n");
    printf("||`\"' /  /  / ,__...-----| _.,  ,'            `|----.._`-.|' |. .` .||\n");
    printf("||  /  '| /.,/   \\--.._ `-,' ,          .  '`.'  __,., '  ''``._ \\ \\||\n");
    printf("|| /_,'---  ,     \\`._,-` \\ //  / . \\    `._,  -`,  / / _   |   `-L ||\n");
    printf("||  /       `.     ,  ..._ ' `_/ '| |\\ `._'       '-.'   `.,'     | ||\n");
    printf("|| '         /    /  ..   `.  `./ | ; `.'    ,\"\" ,.  `.    \\      | ||\n");
    printf("||  `.     ,'   ,'   | |\\  |       \"        |  ,'\\ |   \\    `    ,L ||\n");
    printf("||  /|`.  /    '     | `-| '                  /`-' |    L    `._/  \\||\n");
    printf("|| / | .`|    |  .   `._.'                   `.__,'   .  |     |  (`||\n");
    printf("||'-\"\"-'_|    `. `.__,._____     .    _,        ____ ,-  j     \".-'\"||\n");
    printf("||       \\      `-.  \\/.    `\"--.._    _,.---'\"\"\\/  \"_,.'     /-'   ||\n");
    printf("||        )        `-._ '-.        `--\"      _.-'.-\"\"        `.     ||\n");
    printf(" ====================================================================\n");
    printf("\n");
}

void desenhaSteelix()
{
    printf(" ====================================================================\n");
    printf("||.        _______|                 .-'    |.       `. '            ||\n");
    printf("|| `...---\"     .-'               .'       | `.                 ,  '||\n");
    printf("|| ,'._     _,-\"                  `        |  ,`.  ,  .    _.-'|    ||\n");
    printf("||.    `\"\"-'    `.                 \\       `.....`.     .-',   |    ||\n");
    printf("|||             _,|                 ._ --.        |     '\"--...     ||\n");
    printf("|| `.--\"`.....-\" ,                    /\".`        |   |        _____||\n");
    printf("||   .       | .'_                   /   \\        |  j       \"'_,..'||\n");
    printf("||    /`-...-+\"   `.                 '   .'.__ -..'  |_,..   ,'  |  ||\n");
    printf("||   '          ____.                 \\  |    \"`-..___,....-.    '  ||\n");
    printf("||    .     _.\"\"'   |                  `. .                 / .-'   ||\n");
    printf("||     `. .'       .._                   \\ \\               / /      ||\n");
    printf("||       `-._   _.'   `.                  \\.--......____ .' /       ||\n");
    printf(" ====================================================================\n");
    printf("\n");
}

void desenhaMew()
{
    printf(" ====================================================================\n");
    printf("||              /H/  /H/      H==H      /=    H                     ||\n");
    printf("||             /   HH=          =H      H==    /                    ||\n");
    printf("||             H== ==           //      /==    H                    ||\n");
    printf("||             /==             // /      H==   /                    ||\n");
    printf("||              H=   /H/==     H H /      H==   /                   ||\n");
    printf("||               H=  H=H/=     /H/ H       H==  H                   ||\n");
    printf("||                H= H HH/     =/ =/        H===H/                  ||\n");
    printf("||                H= H H /      ==H  H       H=H=H/                 ||\n");
    printf("||                /==/HH/=       H  H=/       H= HH/                ||\n");
    printf("||                 H======       / H=/H      /=  / H                ||\n");
    printf("||                  /H==/==     H H== /      H= /  H                ||\n");
    printf("||                     HH/HHHHH/ H/==H       /= H =H                ||\n");
    printf(" ====================================================================\n");
    printf("\n");
}