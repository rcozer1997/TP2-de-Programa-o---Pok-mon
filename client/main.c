#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"

int main(int argc, char *argv[])
{
  if(argc != 4)
    printf("ERRO!!! Parametros fora do padrao.");
  else
  {
    srand(atoi(argv[3]));
    menuPrincipal(argv[1], argv[2]);
  }
  return 0;
}