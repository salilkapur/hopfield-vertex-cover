/*
 * Data structures and functions for HNN computation
 */
#include <stdint.h>

#ifndef _H_HNN
#define _H_HNN

#include "common.h"
#include "graph.h"

struct hyperparameters {
    float theta;
    float decision_thresh;
    float epsilon;
    float A;
    float B;
    float decay;
    float beta;
};

struct model {
    float* weights;
    struct hyperparameters* h_params;
    uint8_t cover;
    struct graph* G;
};

#endif
