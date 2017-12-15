#include "common.h"
#include "graph.h"
#include "io_utility.h"

#define DEBUG if(1)

//Declared in common.h
char masks[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

int main(int argc, char** argv) {
    
    //Read the input file
    if(argc < 2) {
        printf("Usage: mvc <input_graph>\n");
        exit(0);
    }
    
    //Create a new graph
    struct graph* G = (struct graph*)malloc(sizeof(struct graph)); 
    graph_init(G);
    read_bin_graph(argv[1], G);    
    DEBUG printf("# Vertices: %ld | # Edges: %ld\n", G->N, G->M);
    compute_adj_mat(G);
    compute_degrees(G);
    DEBUG printf("Degree: %d\n", G->degrees[10]);
    return 1;
}
