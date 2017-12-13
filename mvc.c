#include "common.h"
#include "graph.h"
#include "io_utility.h"

int main(int argc, char** argv) {
    
    //Read the input file
    if(argc < 2) {
        printf("Usage: mvc <input_graph>\n");
        exit(0);
    }
    
    //Create a new graph
    struct graph* G = (struct graph*)malloc(sizeof(struct graph*)); 
    read_bin_graph(argv[1], G);    
    printf("# Vertices: %ld | # Edges: %ld\n", G->N, G->M);
    return 1;
}
