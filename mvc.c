#include "common.h"
#include "graph.h"
#include "io_utility.h"
#include "math.h"
#include "hnn.h"

#define rounds 500

//Declared in common.h
char masks[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
int results[rounds];

/* Function declarations */ 
int minVC(struct graph*);
float outputPotential(struct model*, int);
void init_hnn_weights(struct graph*, struct model*);
float delta_weight_sim_anneal(struct graph*, struct model*, int);
void update_temperature(int, struct model*);



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
    //long vertices = G->N;

    //Set hyperparameters
    struct model* M = (struct model*)malloc(sizeof(struct model));
    M->h_params = (struct hyperparameters*)malloc(sizeof(struct hyperparameters));
    M->h_params->theta = 5;
    M->h_params->decision_thresh = .5;
    M->h_params->epsilon = .05;
    M->h_params->A = 1;
    M->h_params->B = 1;
    M->h_params->decay = 1;
    M->h_params->beta = .03;
    M->h_params->temperature = .15*G->N;

    init_hnn_weights(G, M);

    
    // just testing  the functions
    float test = delta_weight_sim_anneal(G, M, 1);
    printf("\n%f, %f", M->weights[1], test);

    M->weights[1] = test;

    float outputp = outputPotential(M, 1);
    printf("\n%f, %f", M->weights[1], outputp);




    
  /*  printf("\n%f, %f, %f, %f, %f, %f, %f, %f, %f, %f", M->weights[1], M->weights[2], M->weights[3], M->weights[4], M->weights[5], 
        M->weights[vertices-1], M->weights[vertices-2], M->weights[vertices-3], M->weights[vertices-4], M->weights[vertices-5]);*/

    return 1;
}


// determine the optimal MVC from all rounds
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
    float x = model->weights[i] / model->h_params->theta;
    float v = 1/(1 + expf(-x));
    return v;
}

void init_hnn_weights(struct graph* G, struct model* model) {
    model->weights = (float*)malloc(sizeof(float) * G->N);
    int eps = model->h_params->epsilon * 100;
    for (long i=0; i < G->N; i++) {
        model->weights[i] = model->h_params->decision_thresh + (float)(rand() % (eps*2+1))/(float)100  - model->h_params->epsilon;    
    }
}

float delta_weight_sim_anneal(struct graph* G, struct model* M, int i){
    float A = M->h_params->A;
    float B = M->h_params->B;
    
    float sum1 = 0;
    float sum2 = 0;
    
    //sum1
    for(int j = 0; j < G->N; j++){
        if(G->edges[i][j] == 1 && M->cover[j] == 1){
            sum1 = sum1 + 1;
        }
    }
    
    //sum2
    for(int j = 0; j < G->N; j++){
        if(G->edges[i][j] == 1){
            sum2 = sum2 + 1;
        }
    }

    float derivativeE = -A -2*B*sum1 + 2*B*sum2;
    float greedy_factor_sim_anneal = M->h_params->temperature * (1 - G->degrees[i]/G->M);
    float delta_i = - M->weights[i]/M->h_params->decay - derivativeE - greedy_factor_sim_anneal;
    return delta_i;
}


void update_temperature(int t, struct model* M){
    M->h_params->temperature = M->h_params->temperature * (1 - M->h_params->beta);
}








