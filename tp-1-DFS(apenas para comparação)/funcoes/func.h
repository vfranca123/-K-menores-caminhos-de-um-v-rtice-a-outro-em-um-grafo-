#include<stdio.h>
#include <limits.h>
#include <stdbool.h> // Inclui a biblioteca para usar o tipo de dados bool

// Evita múltiplas inclusões do mesmo arquivo de cabeçalho
#ifndef _index_funcoes_h
#define _index_funcoes_h

#define MAX_VERTICES 100000 // Define o número máximo de vértices

// Estrutura de um nó de lista encadeada para representar os vértices e seus pesos
typedef struct node {
    int vertex; // Vértice adjacente
    int weight; // Peso da aresta
    struct node* next; // Próximo nó na lista encadeada
} node;

// Estrutura de um grafo
typedef struct Graph {
    int numVertices; // Número de vértices no grafo
    node** adjLists; // Lista de adjacência para representar os vértices e suas conexões
    int* visited; // Array para rastrear os vértices visitados durante a travessia
} Graph;

//estrutura vetor dinamico 
typedef struct {
    int *array;      // Ponteiro para o array que armazena os elementos
    size_t size;     // Tamanho atual do vetor
    size_t capacity; // Capacidade atual do vetor
} DynamicArray;

// grafo e dfs
Graph* createGraph(int vertices);
node* createNode(int v, int w);
void addEdge(Graph* graph, int src, int dest, int weight);
void DFS(Graph* graph, int vertex, int end, int path[], int path_index, int path_weight,DynamicArray *numbers);
void freeGraph(Graph* graph);
 
// vetor dinamico
void initDynamicArray(DynamicArray *dynArray, size_t initialCapacity);
void append(DynamicArray *dynArray, int value);
void freeDynamicArray(DynamicArray *dynArray);

//ordenar o vetor
void insertionSort(int arr[], int n);

#endif // _index_funcoes_h 