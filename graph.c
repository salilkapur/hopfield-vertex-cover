/*
 * functions for graph handling and manipulations
 */

#include "graph.h"

char get_edge(struct graph* G, int i, int j)
{
    int byte, bit;
    char mask;

    bit  = 7-(j & 0x00000007);
    byte = j >> 3;

    mask = masks[bit];
    return( (G->adj_list[i][byte] & mask)==mask );
}

void compute_degrees(struct graph* G) {
    for (long i=0; i < G->N; i++) {
        G->degrees[i] = 0;
        for(long j=0; j < G->N; j++) {
            if(G->adj_mat[i][j] == 1) {
                //printf("Edge: (%ld, %ld)\n",i, j);
                G->degrees[i]++;
            }
        }
    }
}

void compute_adj_mat(struct graph* G) {
    for (long i=0; i < G->N; i++) {
        for(long j=0; j < G->N; j++) {
            if(get_edge(G, i, j) == 1) {
                G->adj_mat[i][j] = 1;
                G->adj_mat[j][i] = 1;
            }
        }
    }
}

void graph_init(struct graph* G) {
    printf("Initializing graph...\n");
    G->adj_list = (char**)malloc(sizeof(char*) * MAX_NR_VERTICES);
    G->adj_mat = (char**)malloc(sizeof(char*) * MAX_NR_VERTICES);
    int i = 0;
    for(i = 0; i < MAX_NR_VERTICES; i++) {
        G->adj_list[i] = (char*)malloc(sizeof(char) * MAX_NR_VERTICESdiv8);
        G->adj_mat[i] = (char*)malloc(sizeof(char) * MAX_NR_VERTICES);
    }
    G->degrees = (int*)malloc(sizeof(int) * G->N);
    printf("Graph initialized!\n");
}
