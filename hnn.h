/*
 * Data structures and functions for HNN computation
 */

#ifndef _H_HNN
#define _H_HNN

#include "common.h"
#include "graph.h"

struct hyperparameters {
    float theta;
    float decision_thresh;
    float A;
    float B;
    float decay;
    float beta;
    float temperature;
    float epsilon;
};

struct model {
    float* weights;
    struct hyperparameters* h_params;
    uint8_t* cover;
    struct graph* G;
};

void init_model(struct model*, struct graph*, struct hyperparameters*);
void init_model_weights(struct model*);
int find_min_vertex_cover(int, int*, int);
float output_potential(struct model*, int);
float delta_weight(struct model* M, int i);
void update_temperature(struct model*);
void optimize(struct model*, int*, int);
#endif
