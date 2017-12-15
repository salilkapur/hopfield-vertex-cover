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
    char** adj_list;
    char** adj_mat;
    int* degrees;
};

void graph_init(struct graph* G);
char get_edge(struct graph*, int, int);
void compute_degrees(struct graph*);
void compute_adj_mat(struct graph*);

#endif
