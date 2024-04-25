#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "func.h" // Inclui o cabeçalho com as definições de estrutura e funções

#define INFINITY INT_MAX // Define o infinito como o valor máximo de um inteiro



// Função para criar um novo nó com o vértice e o peso especificados
node* createNode(int v, int w) {
    node* newNode = malloc(sizeof(node)); // Aloca memória para o novo nó
    newNode->vertex = v; // Define o vértice do nó
    newNode->weight = w; // Define o peso do nó
    newNode->next = NULL; // Define o próximo nó como nulo
    return newNode; // Retorna o novo nó criado
}

// Função para criar um novo grafo com o número especificado de vértices
Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph)); // Aloca memória para o novo grafo
    graph->numVertices = vertices; // Define o número de vértices do grafo

    // Aloca memória para a lista de adjacência e o array de visitados
    graph->adjLists = malloc(vertices * sizeof(node*));
    graph->visited = malloc(vertices * sizeof(int));

    // Inicializa as listas de adjacência e o array de visitados
    int i;
    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL; // Inicializa a lista de adjacência como vazia
        graph->visited[i] = 0; // Define todos os vértices como não visitados
    }

    return graph; // Retorna o novo grafo criado
}

// Função para adicionar uma aresta entre dois vértices com o peso especificado
void addEdge(Graph* graph, int src, int dest, int weight) {
    // Cria um novo nó com o destino e o peso especificados e o adiciona à lista de adjacência do vértice de origem
    node* newNode = createNode(dest, weight);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Cria um novo nó com a origem e o peso especificados e o adiciona à lista de adjacência do vértice de destino
    newNode = createNode(src, weight);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
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


void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Função de travessia em profundidade para encontrar todos os caminhos possíveis entre dois vértices
void DFS(Graph* graph, int vertex, int end, int path[], int path_index, int path_weight, DynamicArray *numbers) {
    graph->visited[vertex] = 1; // Marca o vértice atual como visitado
    path[path_index] = vertex; // Adiciona o vértice atual ao caminho
    path_index++; // Incrementa o índice do caminho

    if (vertex == end) { // Se o vértice atual for o vértice de destino
        append(numbers, path_weight);
    } else {
        // Explora todos os vértices adjacentes não visitados
        node* temp = graph->adjLists[vertex];
        while (temp) {
            int connectedVertex = temp->vertex; // Obtém o vértice adjacente
            if (graph->visited[connectedVertex] == 0) { // Se o vértice adjacente não foi visitado
                // Chama recursivamente a função DFS para explorar o vértice adjacente
                DFS(graph, connectedVertex, end, path, path_index, path_weight + temp->weight, numbers);
            }
            temp = temp->next; // Move para o próximo vértice adjacente
        }
    }

    path_index--; // Decrementa o índice do caminho
    graph->visited[vertex] = 0; // Marca o vértice atual como não visitado para que ele possa ser explorado novamente em outro caminho
}


//-----------------------------------------------array
void initDynamicArray(DynamicArray *dynArray, size_t initialCapacity) {
    // Aloca memória para o array com a capacidade inicial especificada
    dynArray->array = (int *)malloc(initialCapacity * sizeof(int));
    // Verifica se a alocação foi bem-sucedida
    if (dynArray->array == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória.\n");
        exit(EXIT_FAILURE);
    }
    // Inicializa o tamanho como 0 e a capacidade como a capacidade inicial
    dynArray->size = 0;
    dynArray->capacity = initialCapacity;
}

// Função para adicionar um elemento ao vetor dinâmico
void append(DynamicArray *dynArray, int value) {
    // Verifica se o tamanho atual é maior ou igual à capacidade
    if (dynArray->size >= dynArray->capacity) {
        // Se for, dobramos a capacidade
        size_t newCapacity = dynArray->capacity * 2;
        // Realocamos memória para o array com a nova capacidade
        int *temp = realloc(dynArray->array, newCapacity * sizeof(int));
        // Verificamos se a realocação foi bem-sucedida
        if (temp == NULL) {
            fprintf(stderr, "Erro: Falha na realocação de memória.\n");
            exit(EXIT_FAILURE);
        }
        // Atualizamos o ponteiro do array e a capacidade
        dynArray->array = temp;
        dynArray->capacity = newCapacity;
    }
    // Adicionamos o novo elemento ao final do array
    dynArray->array[dynArray->size++] = value;
}

// Função para liberar a memória alocada para o vetor dinâmico
void freeDynamicArray(DynamicArray *dynArray) {
    // Liberamos a memória do array
    free(dynArray->array);
    // Definimos os ponteiros para NULL e os tamanhos como 0
    dynArray->array = NULL;
    dynArray->size = dynArray->capacity = 0;
}


    