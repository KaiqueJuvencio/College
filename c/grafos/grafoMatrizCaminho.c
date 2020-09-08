/*
Programa implementa fun��es para criar e
manipular um grafo armazenado usando Listas de Adjacencias
-std=c99
*/
#include <stdio.h>
#include <stdlib.h> // calloc
#include<stdbool.h> //para usar boolean

typedef struct _TNo{
	int w; // vertice adjacente ao vertice v
	struct _TNo *prox; // proximo no na lista de ajdacencia
}TNo;

// definindo o tipo TGrafo
typedef struct{
	int V; // quantidade de v�rtices
	int A; // quantidade de arestas
	TNo **adj; //vetor armanazena o inicio de uma lista encadeada de adjac�ncia
}TGrafo;

// declaracao de funcoes
TGrafo * Init( int V );
void insereA( TGrafo *G, int v, int w);
void removeA(TGrafo *G, int v, int w);
void show(TGrafo *G);
void libera(TGrafo *G);

int main(void){
    // cria uma variavel ponteiro para armazenar um tipo TGrafo
    TGrafo *grafo;

    grafo = Init( 5 );// cria um grafo com 4 vertices

    insereA(grafo,0,3);
    insereA(grafo,0,7);
    insereA(grafo,0,5);
    insereA(grafo,0,5);
    insereA(grafo,0,2);
    insereA(grafo,0,1);
    insereA(grafo,0,15);

    removeA(grafo, 0, 3);

    //insereA(grafo,1,3);
    //insereA(grafo,2,1);
    //insereA(grafo,2,3);

    show(grafo);
    libera(grafo);
    return 0;
}
/*
Fun��o cria e devolve uma nova estrutura TGrafo,
inicializa os atributos da estrutura, cria uma lista de
adjac�ncias para V v�rtices e zera os valores para arestas.
*/
TGrafo * Init( int V ){
    int i;
    TGrafo *g; //variavel ponteiro
    // aloca a inicializa a posicao de memoria com 0
    g = (TGrafo *) calloc(1, sizeof(TGrafo));
    g->V = V; // atualiza a quantidade de vertices
    g->A = 0; // zera o numero de arestas

    // alocar vetor para as entradas da lista de adjacencias
    g->adj = (TNo**) calloc(g->V, sizeof(TNo *));

    // retorna o grafo
    return g;
}
/*
Fun��o cria uma aresta v-w no grafo. A fun��o sup�e
que v e w s�o distintos, positivos e menores que V.
Se o grafo j� tem a aresta v-w, a fun��o n�o faz nada.
A fun��o tamb�m atualiza a quantidade de arestas no grafo.
*/
void insereA( TGrafo *G, int v, int w){
    bool wExiste = false; //Seta a flag para verificar se w existe como false
    int i = 0;
    TNo *aux;
    aux = G->adj[v];
    while( aux ){ // aux != null
        if(w == aux->w){//Verifica se o w ja existe na lista
            printf("WARNING: Ja existe o %d no grafo \n \n", w);
            wExiste = true;//Atribui true na flag, avisando que o w ja existe
        }
        aux = aux->prox;
    }
    if(wExiste == false){//se o w nao existir na lista, pode inserir
        if(G->adj[v]){
            TNo *aux2;
            aux2 = G->adj[v];
            int v;
            for(v=0;v<G->V;v++){ // aux != null
                if(w > aux2->w){// Se o w for maior que o elemento elemento atual da lista
                    if(aux2->prox == NULL){//Se o proximo for nulo
                        TNo *novo = (TNo*) calloc(1, sizeof(TNo));//Cria novo no
                        novo->w = w;
                        aux2->prox = novo;
                        G->A++;
                        break;
                    }
                    TNo *aux2Proximo = aux2->prox;
                    if(w < aux2Proximo->w){//Se o w for menor que o proximo do elemento atual, ele insere no meio
                        TNo *novo = (TNo*) calloc(1, sizeof(TNo));//Cria novo no
                        novo->w = w;
                        novo->prox = aux2->prox;
                        aux2->prox = novo;
                        G->A++;
                        break;
                    }
                }else{//caso o w seja menor que o elemento da lista
                    // insere no inicio da lista da entrada do vertice v
                    TNo *novo = (TNo*) calloc(1, sizeof(TNo));//Cria novo no
                    novo->w = w; //Aloca o w no novo no
                    novo->prox = G->adj[v];
                    G->adj[v] = novo;
                    G->A++;
                    break;
                }
                aux2 = aux2->prox;
            }
        }else{
            // insere no inicio da lista da entrada do vertice v
            TNo *novo = (TNo*) calloc(1, sizeof(TNo));//Cria novo no
            novo->w = w; //Aloca o w no novo no
            novo->prox = G->adj[v];
            G->adj[v] = novo;//Cabeca da lista recebe o novo no
            G->A++;
            }
    }
}
/*
Fun��o remove do grafo a aresta que tem ponta inicial v
e ponta final w. A fun��o sup�e que v e w s�o distintos,
positivos e menores que V. Se n�o existe a aresta v-w,
a fun��o n�o faz nada. A fun��o tamb�m atualiza a
quantidade de arestas no grafo.
*/
void removeA(TGrafo *G, int v, int w){
    TNo *aux;
    aux = G->adj[v];
    aux = aux->prox;

}
/*
Para cada v�rtice v do grafo, esta fun��o imprime,
em uma linha, todos os v�rtices adjacentes a v.
*/
void show(TGrafo *G){
    int v, w;
    printf("grafo V:%d A:%d\n",G->V,G->A);
    for(v=0;v<G->V;v++){
        TNo *aux;
        aux = G->adj[v];
        printf("%d:",v);
        while( aux ){ // aux != null
            printf(" %d",aux->w);
            aux = aux->prox;
        }
        printf("\n");
    }
}
/*
Fun��o libera a mem�ria utilizado pelo grafo e pela
matriz de adjac�ncia.
*/
void libera(TGrafo *G){
    free(G);
}
