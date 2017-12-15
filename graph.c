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
    return( (G->edges[i][byte] & mask)==mask );
}

void compute_degrees(struct graph* G) {
    G->degrees = (int*)malloc(sizeof(int) * G->N);
    for (long i=0; i < G->N; i++) {
        G->degrees[i] = 0;
        for(long j=0; j < G->N; j++) {
            if(get_edge(G, i, j) == 1) {
                printf("Edge: (%ld, %ld)\n",i, j);
                G->degrees[i]++;
            }
        }
    }
}

void graph_init(struct graph* G) {
    printf("Initializing graph...\n");
    G->edges = (char**)malloc(sizeof(char*) * MAX_NR_VERTICES);
    int i = 0;
    for(i = 0; i < MAX_NR_VERTICES; i++) {
        G->edges[i] = (char*)malloc(sizeof(char) * MAX_NR_VERTICESdiv8);
    }
    //memset(G->edges, 0, MAX_NR_VERTICES * MAX_NR_VERTICESdiv8);
    printf("Graph initialized!\n");
}
