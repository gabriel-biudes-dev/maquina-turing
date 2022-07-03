#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#define MAX 1000

//Cria uma lista vazia
//Pré-condição: nenhuma
//Pós-condição: retorna uma lista vazia
Lista* criar_lista_vazia(){
  Lista *aux = (Lista*) malloc(sizeof(Lista));
  aux->info = NULL;
  aux->prox = NULL;
  return aux;
}

//Insere um valor numa lista
//Pré-condição: o valor deve ser uma string
//Pós-condição: retorna a nova lista com o valor inserido
Lista* inserir(Lista *l, char* valor){
  Lista *aux = (Lista*) malloc(sizeof(Lista));
  aux->info = valor;
  if(l->info) aux->prox = l;
  else aux->prox = NULL;
  return aux;
}

//Busca um valor numa lista
//Pré-condição: o valor buscado deve ser uma string
//Pós-condição: retorna 1 caso a lista possua o valor, 0 caso contrário
int buscar(Lista *l, char* item){
  if(l->info != NULL){
    if(strcmp(item, l->info) == 0) return 1;
    if(l->prox != NULL) buscar(l->prox, item);
  }
  return 0;
}

//Remove os X últimos caracteres de uma string
//Pré-condição: x > 0
//Pós-condição: a string é modificada
void remove_ultimo(char *str, int x){
  *(str + strlen(str) - x) = 0;
}

//Remove todos os espaços em branco de uma string
//Pré-condição: nenhuma
//Pós-condição: retorna a string sem os espaços em branco
char* remove_espacos(char* s){
    int i = 0;
    char *temp = (char*) malloc(sizeof(char) * MAX);
    while(*s){
        if(*s != ' '){
          *(temp + i) = *s;
          i++;
        }
        s++;
    }
    *(temp + i) = 0;
    temp = (char *) realloc(temp, strlen(temp) + 1);
    return temp;
}

//Guarda um valor devidamente formatado na lista
//Pré-condição: o valor deve ser uma string
//Pós-condição: retorna a nova lista com o valor inserido
Lista* guardarDados(Lista *l, char *str){
  char *aux = (char*) malloc(sizeof(char) * MAX);
  strcpy(aux, str);
  aux = strtok(aux, "{");
  aux = strtok(NULL, "{");
  remove_ultimo(aux, 2);
  aux = strtok(aux, ",");
  while(aux){
    aux = remove_espacos(aux);
    l = inserir(l, aux);
    aux = strtok(NULL, ",");
  }
  return l;
}

//Verifica a quantidade de estados da máquina
//Pré-condição: nenhuma
//Pós-condição: retorna a quantidade de estados da máquina
int getstate(char *str){
  char *aux = (char*) malloc(strlen(str) + 1);
  strcpy(aux, str);
  aux = strtok(aux, "=");
  aux = strtok(NULL, "=");
  return atoi(aux);
}

//Troca todas as ocorrências de X por Y
//Pré-condição: nenhuma
//Pós-condição: modifica a string
void trocar(char *str, char x, char y){
  while(*str){
    if(*str == x) *str = y;
    *str++;
  }
}

//Remove todas as ocorrências de um caractere na string
//Pré-condição: nenhuma
//Pós-condição: modifica a string
void remover(char * str, char charToRemmove){
  int i, j, tamanho;
  tamanho = strlen(str);
  for(i = 0; i < tamanho; i++){
    if(str[i] == charToRemmove){
      for(j = i; j < tamanho; j++) str[j] = str[j+1];
      tamanho--;
      i--;
    }
  }
}

//Guarda os valores da transição formatados corretamente numa lista
//Pré-condição: nenhuna
//Pós-condição: retorna a nova lista com o valor inserido
Lista* guardarTransicao(Lista *l, char *str){
  str = remove_espacos(str);
  remover(str, '(');
  remover(str, ')');
  remover(str, 10);
  trocar(str, ',', ' ');
  trocar(str, '=', ' ');
  l = inserir(l, str);
}

//Adiciona os caracteres '*' e '$' ao início e fim da cadeia, respectivamente
//Pré-condição: nenhuma
//Pós-condição: retorna a string modificada
char* formatar(char *str){
  char *inicio = (char*) malloc(sizeof(str) + 7);
  char *fim = "$";
  *inicio = '*';
  *(inicio + 1) = 0;
  strcat(inicio, "[q0]");
  strcat(inicio, str);
  strcat(inicio, fim);
  return inicio;
}

//Verifica o primeiro caractere de uma string
//Pré-condição: nenhuma
//Pós-condição: retorna o primeiro caractere da string
char* pegar_primeiro(char *str){
  char *aux = (char*) malloc(sizeof(char));
  strcpy(aux, str);
  *(aux + 1) = 0;
  return aux;
}

//Verifica qual é o próximo caractere a ser avaliado na cadeia
//Pré-condição: nenhuma
//Pós-condição: retorna o caractere
char* proximo_char(char *str){
  char *aux = (char*) malloc(strlen(str) + 1);
  strcpy(aux, str);
  aux = strtok(aux, "]");
  aux = strtok(NULL, "]");
  aux = pegar_primeiro(aux);
  return aux;
}

//Verifica, de acordo com a lista de transições, para onde a máquina deve ir
//Pré-condição: deve receber a lista de transições formatada corretamente
//Pós-condição: retorna informações sobre a mudança da máquina numa string
char* avaliar_transicao(char *atual, char *estado_atual, Lista *transicoes){
  char* str_final = (char*) malloc(MAX);
  char *aux = (char*) malloc(sizeof(char) * MAX);
  if(transicoes->info){
    strcpy(aux, transicoes->info);
    aux = strtok(aux, " ");
    if(strcmp(aux, estado_atual) == 0){
      aux = strtok(NULL, " ");
      if(strcmp(aux, atual) == 0){
        aux = strtok(NULL, " ");
        strcat(str_final, aux);
        strcat(str_final, " ");
        aux = strtok(NULL, " ");
        strcat(str_final, aux);
        strcat(str_final, " ");
        aux = strtok(NULL, " ");
        strcat(str_final, aux);
        return str_final;
      }
    }
  }
  if(transicoes->prox) return avaliar_transicao(atual, estado_atual, transicoes->prox);
  return "";
}

//Verifica se, dado o estado atual e o caractere a ser avaliado, há como a máquina continuar
//Pré-condição: deve receber a lista de transições devidamente formatada
//Pós-condição: retorna 1 caso sim, 0 caso a máquina deva parar
int tem_transicao(char *atual, char *estado_atual, Lista *transicoes){
  char *aux = (char*) malloc(sizeof(char) * MAX);
  if(transicoes->info){
    strcpy(aux, transicoes->info);
    aux = strtok(aux, " ");
    if(strcmp(aux, estado_atual) == 0){
      aux = strtok(NULL, " ");
      if(strcmp(aux, atual) == 0){
        return 1;
      }
    }
  }
  if(transicoes->prox) return tem_transicao(atual, estado_atual, transicoes->prox);
  return 0;
}

//Substitui todas as ocorrências de uma substring por outra substring
//Pré-condição: nenhuma
//Pós-condição: retorna a string modificada
char* substituir(char* s, char* oldW, char* newW){
  char* resultado;
  int i, cnt = 0;
  int newWlen = strlen(newW);
  int oldWlen = strlen(oldW);

  for (i = 0; s[i] != '\0'; i++){
    if (strstr(&s[i], oldW) == &s[i]) {
      cnt++;
      i += oldWlen - 1;
    }
  }
  resultado = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);
  i = 0;
  while (*s){
    if(strstr(s, oldW) == s){
      strcpy(&resultado[i], newW);
      i += newWlen;
      s += oldWlen;
    }
    else resultado[i++] = *s++;
  }
  resultado[i] = '\0';
  return resultado;
}

//Substitui o caractere avaliado pelo novo caractere
//Pré-condição: nenhuma
//Pós-condição: retorna a cadeia modificada
char* alterarChar(char *str, char *x){
  char *aux1 = (char*) malloc(sizeof(char) * MAX);
  char *aux2 = (char*) malloc(sizeof(char) * MAX);
  char *aux3 = (char*) malloc(sizeof(char) * MAX);

  strcpy(aux1, str);
  aux1 = strtok(aux1, "]");
  strcpy(aux2, aux1);
  aux1 = strtok(NULL, "]");
  strcpy(aux3, aux1);
  *aux3 = x[0];
  strcat(aux2, "]");
  strcat(aux2, aux3);
  return aux2;
}

//Remove o primeiro caractere de uma string
//Pré-condição: string não vazia
//Pós-condição: modifica a string
void remove_primeiro(char *str){
  int i;
  for(i = 0; i < strlen(str); i++){
    *(str + i) = *(str + i + 1);
  }
}

//Move a máquina para a direita
//Pré-condição: nenhuma
//Pós-condição: retorna a cadeia modificada
char* mover_dir(char *str){
  char *temp = (char*) malloc(strlen(str) + 1);
  char *aux1 = (char*) malloc(sizeof(char) * MAX);
  char *aux2 = (char*) malloc(sizeof(char) * MAX);
  char *aux3 = (char*) malloc(sizeof(char) * 2);
  strcpy(temp, str);
  strcpy(aux2, "[");
  *(aux3 + 1) = 0;
  temp = strtok(temp, "[");
  strcpy(aux1, temp);
  temp = strtok(NULL, "[");
  temp = strtok(temp, "]");
  strcat(aux2, temp);
  strcat(aux2, "]");
  temp = strtok(NULL, "]");
  *aux3 = *temp;
  remove_primeiro(temp);
  strcat(aux1, aux3);
  strcat(aux1, aux2);
  strcat(aux1, temp);
  return aux1;
}

//Move a máquina para a esquerda
//Pré-condição: nenhuma
//Pós-condição: retorna a cadeia modificada
char* mover_esq(char *str){
  char *temp = (char*) malloc(strlen(str) + 1);
  char *aux1 = (char*) malloc(sizeof(char) * MAX);
  char *aux2 = (char*) malloc(sizeof(char) * MAX);
  char *aux3 = (char*) malloc(sizeof(char) * 2);
  strcpy(temp, str);
  strcpy(aux2, "[");
  *(aux3 + 1) = 0;
  temp = strtok(temp, "[");
  *aux3 = *(temp + strlen(temp) - 1);
  remove_ultimo(temp, 1);
  strcpy(aux1, temp);
  temp = strtok(NULL, "[");
  temp = strtok(temp, "]");
  strcat(aux2, temp);
  strcat(aux2, "]");
  temp = strtok(NULL, "]");
  strcat(aux1, aux2);
  strcat(aux1, aux3);
  strcat(aux1, temp);
  return aux1;
}

//Define a direção que a máquina deverá se mover
//Pré-condição: nenhuma
//Pós-condição: retorna a cadeia modificada
char* mover_estado(char *str, char direcao){
  if(direcao == 'D') return mover_dir(str);
  if(direcao == 'E') return mover_esq(str);
}

//Reescreve a cadeia de acordo com a lista de transições
//Pré-condição: nenhuma
//Pós-condição: retorna a cadeia modificada
char* reescrever(char *cadeia, char *next, char *estado_atual){
  char *aux = (char*) malloc(sizeof(char) * MAX);
  char direcao = *(next + strlen(next) - 1);
  strcpy(aux, next);
  aux = strtok(aux, " ");
  cadeia = substituir(cadeia, estado_atual, aux);
  aux = strtok(NULL, " ");
  cadeia = alterarChar(cadeia, aux);
  cadeia = mover_estado(cadeia, direcao);
  return cadeia;
}

//Valida a cadeia de caracteres
//Pré-condição: nenhuma
//Pós-condição: mostra se a cadeia foi aceita ou rejeitada
void validar(char *cadeia, Lista* alfabeto, Lista* finais, Lista* transicoes, int estados){
  int val = 1;
  char *atual = (char*) malloc(2);
  char *estado_atual = "q0";
  char *next = (char*) malloc(sizeof(char) * MAX);
  char *aux = (char*) malloc(sizeof(char) * MAX);

  cadeia = formatar(cadeia);
  atual = proximo_char(cadeia);
  while(tem_transicao(atual, estado_atual, transicoes)){
    printf("%s\n", cadeia);
    next = avaliar_transicao(atual, estado_atual, transicoes);
    cadeia = reescrever(cadeia, next, estado_atual);
    next = strtok(next, " ");
    estado_atual = next;
    atual = proximo_char(cadeia);
  }
  printf("%s\n", cadeia);
  if(buscar(finais, estado_atual)) printf("ACEITA\n");
  else printf("REJEITA\n");
}

int main()
{
  //Declaração de variáveis e estruturas
  Lista *alfabeto = criar_lista_vazia();
  Lista *finais = criar_lista_vazia();
  Lista *transicoes = criar_lista_vazia();
  char *cadeia = (char*) malloc(sizeof(char) * 50);
  char *nomeArq = (char*) malloc(sizeof(char) * 50);
  FILE *f;
  int i, estados;
  char linha[100];

  //Armazenamento dos dados em listas, a partir de um arquivo txt
  printf("Insira o nome do arquivo de texto a ser lido (com extensao): ");
  scanf("%[^\n]%*c", nomeArq);
  f = fopen(nomeArq, "r");
  for(i = 0; fgets(linha, MAX, f); i++){
    if(i == 0){
      estados = getstate(linha);
    }else if(i == 1){
      finais = guardarDados(finais, linha);
    }else if(i == 2){
      alfabeto = guardarDados(alfabeto, linha);
    }else{
      transicoes = guardarTransicao(transicoes, linha);
    }
  }

  //Loop de entrada de dados
  printf("Insira uma palavra a ser testada: ");
  while(scanf("%[^\n]%*c", cadeia)){
    validar(cadeia, alfabeto, finais, transicoes, estados);
    printf("\nInsira uma nova palavra a ser testada: ");
  }
  return 0;
}
