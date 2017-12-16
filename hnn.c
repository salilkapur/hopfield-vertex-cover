#include "hnn.h"

void init_model(struct model* M, struct graph* G, struct hyperparameters* h_params) {

    M->G = G;
    if (h_params == NULL) {
        M->h_params = (struct hyperparameters*)malloc(sizeof(struct hyperparameters));
        M->h_params->theta = 5;
        M->h_params->decision_thresh = 0.5;
        M->h_params->A = 1;
        M->h_params->B = 1;
        M->h_params->decay = 1;
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
        M->weights[i] = M->h_params->decision_thresh + (float)(rand() % (eps*2+1))/(float)100  - M->h_params->epsilon; 
    }
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

float output_potential(struct model* M, int i) {
    float x = M->weights[i] / M->h_params->theta;
    return 1/(1 + expf(-x));
}

float delta_weight(struct model* M, int i) {
    float A = M->h_params->A;
    float B = M->h_params->B;
    
    float sum = 0;
    
    //sum1
    for(int j = 0; j < M->G->N; j++)
        sum = sum + M->G->adj_mat[i][j] * (1 - M->cover[j]);
    
    float derivativeE = -A + 2 * B * sum;

    float greedy_factor_sim_anneal = M->h_params->temperature * (1 - M->G->degrees[i]/M->G->M);
    float delta_i = -1 * (M->weights[i]/M->h_params->decay) - derivativeE - greedy_factor_sim_anneal;
    return delta_i;
}

void update_temperature(struct model* M){
    M->h_params->temperature = M->h_params->temperature * (1 - M->h_params->beta);
}

void optimize(struct model* M, int* results, int rounds) {
    int t = 0;

}
