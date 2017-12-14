#include "common.h"
#include "graph.h"
#include "io_utility.h"
#include "math.h"
#include "hnn.h"

#define rounds 500

//Declared in common.h
char masks[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
int results[rounds];

//error
int minVC(struct graph* G){
    int min = G->N;
    for( int i = 0; i < rounds; i++){
      if(results[i] < min){
        min = results[i];
      }
    }
    return min;
}

float outputPotential(struct model* model, int i){
    //float x = model->weights[i] / model->hyperparameters->theta;
    float x = model->weights[i] / model->h_params->theta;
    float v = 1/(1 + expf(-x));
    return v;
}


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
    compute_degrees(G);
    printf("Degree: %d", G->degrees[20]);
    return 1;
}




