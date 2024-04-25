#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "func.h" // Inclui o cabeçalho com as definições de estrutura e funções

#define INFINITY INT_MAX // Define o infinito como o valor máximo de um inteiro

Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->adjLists = (node**)malloc(numVertices * sizeof(node*));
    graph->visited = (int*)malloc(numVertices * sizeof(int));

    for (int i = 0; i < numVertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Função para criar um nó de lista encadeada
node* createNode(int vertex, int weight) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Função para adicionar uma aresta ao grafo
void addEdge(Graph* graph, int src, int dest, int weight) {
    node* newNode = createNode(dest, weight);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}
// Função para criar uma nova heap de prioridade
Heap_Priority* createPriorityHeap(int capacity) {
    Heap_Priority* heap = (Heap_Priority*)malloc(sizeof(Heap_Priority));
    heap->capacity = capacity;
    heap->size = 0;
    heap->array = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    return heap;
}

// Função para trocar dois nós na heap de prioridade
void swapNodes(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Função para reorganizar a heap de prioridade após uma inserção ou remoção
void heapify(Heap_Priority* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->array[left].priority < heap->array[smallest].priority)
        smallest = left;

    if (right < heap->size && heap->array[right].priority < heap->array[smallest].priority)
        smallest = right;

    if (smallest != idx) {
        swapNodes(&heap->array[idx], &heap->array[smallest]);
        heapify(heap, smallest);
    }
}

// Função para inserir um nó na heap de prioridade
void insertPriorityHeap(Heap_Priority* heap, int vertex, long int priority) {
    if (heap->size == heap->capacity)
        return;

    int i = heap->size++;
    heap->array[i].vertex = vertex;
    heap->array[i].priority = priority;

    while (i != 0 && heap->array[(i - 1) / 2].priority > heap->array[i].priority) {
        swapNodes(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Função para remover e retornar o nó de menor prioridade da heap de prioridade
HeapNode extractMin(Heap_Priority* heap) {
    HeapNode minNode = heap->array[0];
    heap->array[0] = heap->array[--heap->size];
    heapify(heap, 0);
    return minNode;
}

// Algoritmo de Dijkstra modificado para contar as visitas ao destino
bool DijkstraForKpas(Graph* graph, int k, FILE* output_file) {
    int* visit_count = (int*)malloc(graph->numVertices * sizeof(int));
    Heap_Priority* heap = createPriorityHeap(graph->numVertices);
    node *adj;
    for (int i = 0; i < graph->numVertices; ++i)
        visit_count[i] = 0;

    insertPriorityHeap(heap, 0, 0);

    while (visit_count[graph->numVertices - 1] < k) {
        HeapNode node = extractMin(heap);

        if (visit_count[node.vertex] == k)
            continue;

        visit_count[node.vertex] += 1;

        if (node.vertex == graph->numVertices - 1)
            fprintf(output_file, "%ld ", node.priority);

        adj = graph->adjLists[node.vertex]; // Corrigindo aqui para usar a estrutura node

        while (adj) {
            insertPriorityHeap(heap, adj->vertex, (long int)adj->weight + node.priority);
            adj = adj->next;
        }
    }

    free(visit_count);
    free(heap->array);
    free(heap);
    fprintf(output_file, "\n");
    return true;
}

void freeGraph(Graph* graph) {
    // Libera a memória alocada para cada lista de adjacência
    for (int i = 0; i < graph->numVertices; i++) {
        node* current = graph->adjLists[i];
        while (current != NULL) {
            node* next = current->next;
            free(current);
            current = next;
        }
    }
    // Libera a memória alocada para a lista de adjacência e o array de vértices visitados
    free(graph->adjLists);
    free(graph->visited);
    // Libera a memória alocada para a estrutura do grafo
    free(graph);
}

