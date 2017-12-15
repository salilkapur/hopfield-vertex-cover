/*
 * Data structure to store graphs
 */

#ifndef _H_GRAPH
#define _H_GRAPH

#include "common.h" 

#define MAX_NR_VERTICES		10000
#define MAX_NR_VERTICESdiv8	1250

struct graph {
    long N; //number of vertices
    long M; //number of edges
    char** edges;
    int* degrees;
};

void graph_init(struct graph* G);
char get_edge(struct graph*, int, int);
void compute_degrees(struct graph*);

#endif
