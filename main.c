#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "desenvolvimento_funcoes/func.h"

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
    fscanf(input_file, "%d %d %d", &n, &m, &k);
    Graph* graph = createGraph(n);
    
    for(int i = 0; i < m; i++) {
        int a, b, c;
        fscanf(input_file, "%d %d %d", &a, &b, &c);
        addEdge(graph, a - 1, b - 1, c);
    }

    if (!DijkstraForKpas(graph, k, output_file)) {
        fprintf(stderr, "Erro ao executar o algoritmo.\n");
        fclose(input_file);
        fclose(output_file);
        return 1;
    }

    fclose(input_file);
    fclose(output_file);
    freeGraph(graph);
    return 0;
}

