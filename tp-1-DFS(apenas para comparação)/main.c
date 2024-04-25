#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "funcoes/func.h"

int main() {
    FILE *input_file = fopen("../input/input.txt", "r");
    if (input_file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    FILE *output_file = fopen("../output/output.txt", "w");
    if (output_file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo de saída.\n");
        fclose(input_file);
        return 1;
    }

    int n, m, k;
    DynamicArray numbers;
    initDynamicArray(&numbers, 5);

    fscanf(input_file, "%d %d %d", &n, &m, &k);
    Graph* graph = createGraph(n);
    
    for(int i = 0; i < m; i++) {
        int a, b, c;
        fscanf(input_file, "%d %d %d", &a, &b, &c);
        addEdge(graph, a - 1, b - 1, c);
    }
    
    int path[graph->numVertices];
    DFS(graph, 0, graph->numVertices - 1, path, 0, 0, &numbers);

    insertionSort(numbers.array, numbers.size);
    
    for (size_t i = 0; i < k; i++) {
        fprintf(output_file, "%d ", numbers.array[i]);

        if(i >= numbers.size-1){
            fprintf(output_file, "\ntodos os caminhos ja encontrados ");
            break;
        } 
    }
    fprintf(output_file, "\n");

    fclose(input_file);
    fclose(output_file);
    freeGraph(graph);
    freeDynamicArray(&numbers);
    return 0;
}

 /*
    entradas n , m e k
    n=numero de cidades (1-Mysthollow ,n-Luminae)
    m= numero de voos 
    k=parametro ( numero de caminhos a serem encontrados );

    apos 

    m * linhas de voos{
        -cada linha tem 3 int a ,b ,c
        -a para b e seu preço é c  apenas uma direção 
    }

   

    */
