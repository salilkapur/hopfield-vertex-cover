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
            if(get_edge(G, i, j) == 1)
                G->degrees[i]++;
        }
    }
}
