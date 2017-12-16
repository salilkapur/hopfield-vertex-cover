#include "hnn.h"

#define DERIVATIVE if(0)
#define OUTPUT_POTENTIAL if(1)
#define WEIGHTS if(1)

void init_model(struct model* M, struct graph* G, struct hyperparameters* h_params) {

    M->G = G;
    if (h_params == NULL) {
        M->h_params = (struct hyperparameters*)malloc(sizeof(struct hyperparameters));
        M->h_params->theta = 5;
        M->h_params->weight_mean = 0;
        M->h_params->decision_thresh = 0.5; //1/(1 + expf(-1 * 0 * 5));
        M->h_params->A = 1;
        M->h_params->B = 1;
        M->h_params->decay = 1;
        M->h_params->epsilon = 6 * M->h_params->theta;
        M->h_params->temperature = 1.5 * G->N;
    }
    else
        M->h_params = h_params;
    init_model_weights(M);
    M->cover = (uint8_t*)malloc(sizeof(uint8_t) * M->G->N);
}

void init_model_weights(struct model* M) {
    M->weights = (float*)malloc(sizeof(float) * M->G->N);
    int eps = M->h_params->epsilon * 100;
    for (long i=0; i < M->G->N; i++) {
        M->weights[i] = M->h_params->weight_mean + (float)(rand() % (eps*2))/(float)100  - M->h_params->epsilon; 
    }
    printf("Weights after initialization\n");
    print_weights(M);
}

int find_min_vertex_cover(int vertex_count, int* results, int rounds){
    int min = vertex_count;
    for( int i = 0; i < rounds; i++){
      if(results[i] < min){
        min = results[i];
      }
    }
    return min;
}

float output_potential(struct model* M, int i, int sigmoid) {
    if (sigmoid == 1) {
        float x = M->weights[i] / M->h_params->theta;
        return 1/(1 + expf(-1 * x));
    }
    else {
        return 0.5 * (1.0 + tanhf(0.5 * M->weights[i]));
    }
}

float delta_weight(struct model* M, int i) {
    float A = M->h_params->A;
    float B = M->h_params->B;
    
    float sum = 0;
    
    // Derivative formula from paper 2
    for(int j = 0; j < M->G->N; j++)
        sum = sum + M->G->adj_mat[i][j] * (1 - M->cover[j]);
    
    float derivativeE = -1 * A + 2 * B * sum;

    float greedy_factor_sim_anneal = M->h_params->temperature * (1 - M->G->degrees[i]/M->G->M);
    float delta_i = -1 * (M->weights[i]/M->h_params->decay) + derivativeE - greedy_factor_sim_anneal;
    return delta_i;
}

void update_temperature(struct model* M){
    M->h_params->temperature = M->h_params->temperature * (1 - M->h_params->beta);
}

void update_weights(struct model* M) {
    int i = 0;
    DERIVATIVE printf("Derivatives: ");
    for(i=0; i < M->G->N; i++) {
        float delta_u_i = delta_weight(M, i);
        DERIVATIVE printf("%4.2f\t", delta_u_i);
        M->weights[i] = M->weights[i] + delta_u_i;
    }
    DERIVATIVE printf("\n");
    WEIGHTS print_weights(M);
}

int compute_vertex_cover(struct model* M) {
    int i = 0;
    int count = 0;
    OUTPUT_POTENTIAL printf("Output Potential: ");
    for(i=0; i < M->G->N; i++) {
        float v = output_potential(M, i, 1);
        OUTPUT_POTENTIAL printf("%4.2f\t", v);
        if ( v >= M->h_params->decision_thresh) {
            M->cover[i] = 1;
            count++;
        }
        else
            M->cover[i] = 0;
    }
    OUTPUT_POTENTIAL printf("\n");
    return count;
}

void optimize(struct model* M, int* results, int rounds) {
    int t = 0;
    int cover_size_t = 0;
    for(t=0; t < rounds; t++) {
        //Find the vertex cover
        cover_size_t = compute_vertex_cover(M);
        printf("Itr: %d | Cover Size: %d\n", t, cover_size_t);
        results[t] = cover_size_t;
        //Update the weights for each neuron
        update_weights(M);
        update_temperature(M);
    }
}

void print_weights(struct model* M) {
    int i = 0;
    printf("Weights: ");
    for(i=0; i < M->G->N; i++)
        printf("%4.2f\t", M->weights[i]);
    printf("\n");
}


