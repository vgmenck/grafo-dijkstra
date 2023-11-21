#include <stdlib.h>
#include <stdio.h>
#define true 1
#define false 0
typedef int bool;
typedef int TIPOPESO;

typedef struct adjacencia{
    int vertice;
    TIPOPESO peso;
    struct adjacencia *prox;
}ADJACENCIA;

typedef struct vertice{
    ADJACENCIA *cab;
}VERTICE;

typedef struct grafo{
    int** mat;
    int vertices;
    int arestas;
    VERTICE *adj;
}GRAFO;

GRAFO *criaGrafo (int v){
    int i, j;

    GRAFO *g = (GRAFO*)malloc(sizeof(GRAFO));
    g->vertices = v;
    g->arestas = 0;
    g->adj = (VERTICE*)malloc(v*sizeof(VERTICE));
    g->mat = (int**)malloc(v*sizeof(int));

    for(i = 0; i < v; i++) {
            g->mat[i] = (int*)malloc(v*sizeof(int));
    }

    for(i = 0; i < v; i++) {
        for (j = 0; j < v; j++) {
            g->mat[i][j] = 0;
        }
    }

    for (i=0; i<v;i++){
        g -> adj[i].cab=NULL;
    }
    return (g);
}

ADJACENCIA *criadAdj(int v, int peso){
    ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
    temp->vertice =v;
    temp->peso = peso;
    temp->prox = NULL;
    return(temp);
}

bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO p){
    if(!gr) return(false);
    if((vf<0)||(vf>=gr->vertices))return(false);
    if((vi<0)||(vi>=gr->vertices))return(false);
    
    ADJACENCIA *novo = criadAdj(vf,p);
    
    novo->prox = gr->adj[vi].cab;
    gr->adj[vi].cab=novo;
    gr->arestas++;
    gr->mat[vi][vf] = p;
    return (true);
}

void imprime(GRAFO *gr){
    printf("Vertices: %d. Arestas: %d \n",gr->vertices,gr->arestas);
    int i;
    
    for(i = 0; i<gr->vertices; i++){
        printf("v%d:",i+1);
        ADJACENCIA *ad = gr->adj[i].cab;
        while (ad){
            printf("v%d(%d) ",ad->vertice+1,ad->peso);
            ad=ad->prox;
        }
        printf("\n");
    }
}

void matriz(GRAFO *gr){ 
    int i;
    int j;
    for(i = 0; i < gr->vertices; i++) {
        for (j = 0; j < gr->vertices; j++) {
            printf("%4d", gr->mat[i][j]);
        }
        printf("\n");
    }
}

void caminhoMaisCurto(GRAFO *grafo, int origem, int destino) {
    int i, vert, k, NovaDist, min;
    int *visitados, *menorDist, *menorCaminho, *caminho;
    visitados = (int*)malloc(grafo->vertices*sizeof(int));
    menorDist = (int*)malloc(grafo->vertices*sizeof(int));
    menorCaminho = (int*)malloc(grafo->vertices*sizeof(int));
    caminho = (int*)malloc(grafo->vertices*3*sizeof(int));

    for(i=0; i<grafo->vertices; i++) {
        visitados[i] = 0;
        menorCaminho[i] = -1;
        menorDist[i] = 300000;
    }

    vert = origem;
    menorDist[vert] = 0;
    while(vert != destino && vert != -1) {
        for(i = 0; i < grafo->vertices; i++) {
            if(grafo->mat[vert][i] != 0 && visitados[i]==0) {
                NovaDist = menorDist[vert] + grafo->mat[vert][i];
                if(NovaDist < menorDist[i]) {
                    menorDist[i] = NovaDist;
                    menorCaminho[i] = vert;
                }
            }
        }
        visitados[vert] = 1;
        min = 300000;
        vert = -1;
        for(i = 0; i < grafo->vertices; i++) {
            if(visitados[i] == 0 && menorDist[i] < min) {
                min = menorDist[i];
                vert = i;
            }
        }
    }

    if(vert == destino) {
        printf("Caminho mais curto entre %d e %d tem comprimento: %d", origem, destino, menorDist[destino]);
        caminho[0] = destino;
        k = 1;
        while(vert != origem) {
            caminho[k] = menorCaminho[vert];
            vert = menorCaminho[vert];
            k++;
        }

        for(i = k-1; i >= 0; i--) {
            printf("%4d", caminho[i]);
        }
    } else {
        printf("Nao existe caminho entre %d e %d", origem, destino);
    }
}

int main() {
    GRAFO *grafo;
    grafo = criaGrafo(6);

    // 0 -> 1 e 1 -> 0
    criaAresta(grafo, 0, 1, 1);
    criaAresta(grafo, 1, 0, 1);

    // 0 -> 2 e 2 -> 0
    criaAresta(grafo, 0, 2, 4);
    criaAresta(grafo, 2, 0, 4);



    // 1 -> 2 e 2 -> 1
    criaAresta(grafo, 1, 2, 4);
    criaAresta(grafo, 2, 1, 4);

    // 1 -> 3 e 3 -> 1
    criaAresta(grafo, 1, 3, 2);
    criaAresta(grafo, 3, 1, 2);
    
    // 1 -> 4 e 4 -> 1
    criaAresta(grafo, 1, 4, 7);
    criaAresta(grafo, 4, 1, 7);



    // 2 -> 3 e 3 -> 2
    criaAresta(grafo, 2, 3, 3);
    criaAresta(grafo, 3, 2, 3);

    // 2 -> 4 e 4 ->2
    criaAresta(grafo, 2, 4, 5);
    criaAresta(grafo, 4, 2, 5);



    // 3 -> 4 e 4 -> 3
    criaAresta(grafo, 3, 4, 4);
    criaAresta(grafo, 4, 3, 4);

    // 3 -> 5 e 5 -> 3
    criaAresta(grafo, 3, 5, 6);
    criaAresta(grafo, 5, 3, 6);



    // 4 -> 5 e 5 -> 4
    criaAresta(grafo, 4, 5, 7);
    criaAresta(grafo, 5, 4, 7);

    printf("\n");
    imprime(grafo);
    printf("\n");
    matriz(grafo);
    printf("\n");
    caminhoMaisCurto(grafo, 0, 5);
    
    return 0;
}
