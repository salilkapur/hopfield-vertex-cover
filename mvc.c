#include "common.h"
#include "graph.h"
#include "io_utility.h"
#include "hnn.h"

#define DEBUG if(1)
#define ROUNDS 500

//Declared in common.h
char masks[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
int* results;

int main(int argc, char** argv) {
    
    //Read the input file
    if(argc < 2) {
        printf("Usage: mvc <input_graph>\n");
        exit(0);
    }
    
    //Create a new graph
    struct graph* G = (struct graph*)malloc(sizeof(struct graph)); 
    graph_init(G);
    DEBUG printf("Initializing graph...\n");
    read_bin_graph(argv[1], G);    
    DEBUG printf("Graph initialized!\n");
    DEBUG printf("# Vertices: %ld | # Edges: %ld\n", G->N, G->M);
    compute_adj_mat(G);
    compute_degrees(G);
    
    srand(time(NULL)); //Seeding the random number generator
    rand();
    //Initialize the model
    struct model* M = (struct model*)malloc(sizeof(struct model));
    DEBUG printf("Initializing model...\n");
    init_model(M, G, NULL);
    DEBUG printf("Model initialized!\n");
    
    results = (int*)malloc(sizeof(int) * ROUNDS);
    // Run optimization
    optimize(M, results, ROUNDS);

    return 1;
}
