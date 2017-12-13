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
};

struct model {
    float* weights;
    struct hyperparameters* h_params;
    uint8* cover;
    struct graph* G;
};

#endif
