typedef struct no{
  char *info;
  struct no *prox;
} Lista;

//Cria uma lista vazia
//Pré-condição: nenhuma
//Pós-condição: retorna uma lista vazia
Lista* criar_lista_vazia();

//Insere um valor numa lista
//Pré-condição: o valor deve ser uma string
//Pós-condição: retorna a nova lista com o valor inserido
Lista* inserir(Lista *l, char* valor);

//Busca um valor numa lista
//Pré-condição: o valor buscado deve ser uma string
//Pós-condição: retorna 1 caso a lista possua o valor, 0 caso contrário
int buscar(Lista *l, char* item);

//Remove os X últimos caracteres de uma string
//Pré-condição: x > 0
//Pós-condição: a string é modificada
void remove_ultimo(char *str, int x);

//Remove todos os espaços em branco de uma string
//Pré-condição: nenhuma
//Pós-condição: retorna a string sem os espaços em branco
char* remove_espacos(char* s);

//Guarda um valor devidamente formatado na lista
//Pré-condição: o valor deve ser uma string
//Pós-condição: retorna a nova lista com o valor inserido
Lista* guardarDados(Lista *l, char *str);

//Verifica a quantidade de estados da máquina
//Pré-condição: nenhuma
//Pós-condição: retorna a quantidade de estados da máquina
int getstate(char *str);

//Troca todas as ocorrências de X por Y
//Pré-condição: nenhuma
//Pós-condição: modifica a string
void trocar(char *str, char x, char y);

//Remove todas as ocorrências de um caractere na string
//Pré-condição: nenhuma
//Pós-condição: modifica a string
void remover(char * str, char charToRemmove);

//Guarda os valores da transição formatados corretamente numa lista
//Pré-condição: nenhuna
//Pós-condição: retorna a nova lista com o valor inserido
Lista* guardarTransicao(Lista *l, char *str);

//Adiciona os caracteres '*' e '$' ao início e fim da cadeia, respectivamente
//Pré-condição: nenhuma
//Pós-condição: retorna a string modificada
char* formatar(char *str);

//Verifica o primeiro caractere de uma string
//Pré-condição: nenhuma
//Pós-condição: retorna o primeiro caractere da string
char* pegar_primeiro(char *str);

//Verifica qual é o próximo caractere a ser avaliado na cadeia
//Pré-condição: nenhuma
//Pós-condição: retorna o caractere
char* proximo_char(char *str);

//Verifica, de acordo com a lista de transições, para onde a máquina deve ir
//Pré-condição: deve receber a lista de transições formatada corretamente
//Pós-condição: retorna informações sobre a mudança da máquina numa string
char* avaliar_transicao(char *atual, char *estado_atual, Lista *transicoes);

//Verifica se, dado o estado atual e o caractere a ser avaliado, há como a máquina continuar
//Pré-condição: deve receber a lista de transições devidamente formatada
//Pós-condição: retorna 1 caso sim, 0 caso a máquina deva parar
int tem_transicao(char *atual, char *estado_atual, Lista *transicoes);

//Substitui todas as ocorrências de uma substring por outra substring
//Pré-condição: nenhuma
//Pós-condição: retorna a string modificada
char* replaceWord(char* s, char* oldW, char* newW);

//Substitui o caractere avaliado pelo novo caractere
//Pré-condição: nenhuma
//Pós-condição: retorna a cadeia modificada
char* alterarChar(char *str, char *x);

//Remove o primeiro caractere de uma string
//Pré-condição: string não vazia
//Pós-condição: modifica a string
void remove_primeiro(char *str);

//Move a máquina para a direita
//Pré-condição: nenhuma
//Pós-condição: retorna a cadeia modificada
char* mover_dir(char *str);

//Move a máquina para a esquerda
//Pré-condição: nenhuma
//Pós-condição: retorna a cadeia modificada
char* mover_esq(char *str);

//Define a direção que a máquina deverá se mover
//Pré-condição: nenhuma
//Pós-condição: retorna a cadeia modificada
char* mover_estado(char *str, char direcao);

//Reescreve a cadeia de acordo com a lista de transições
//Pré-condição: nenhuma
//Pós-condição: retorna a cadeia modificada
char* reescrever(char *cadeia, char *next, char *estado_atual);

//Valida a cadeia de caracteres
//Pré-condição: nenhuma
//Pós-condição: mostra se a cadeia foi aceita ou rejeitada
void validar(char *cadeia, Lista* alfabeto, Lista* finais, Lista* transicoes, int estados);
