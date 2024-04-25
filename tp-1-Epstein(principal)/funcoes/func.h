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

typedef struct Graph {
    int numVertices; // Número de vértices no grafo
    node** adjLists; // Lista de adjacência para representar os vértices e suas conexões
    int* visited; // Array para rastrear os vértices visitados durante a travessia
} Graph;

//estrutura heap
typedef struct HeapNode {
    int vertex;
    long int priority;
} HeapNode;

typedef struct Heap_Priority {
    int size;
    int capacity;
    HeapNode* array;
} Heap_Priority;


// grafo e dfs
Graph* createGraph(int vertices);
node* createNode(int v, int w);
void addEdge(Graph* graph, int src, int dest, int weight);
bool DijkstraForKpas(Graph* graph, int k, FILE* output_file);
void freeGraph(Graph* graph);
 
// heap
Heap_Priority* createPriorityHeap(int capacity);
void swapNodes(HeapNode* a, HeapNode* b) ;
void heapify(Heap_Priority* heap, int idx);
void insertPriorityHeap(Heap_Priority* heap, int vertex, long int priority);
HeapNode extractMin(Heap_Priority* heap);


#endif // _index_funcoes_h 