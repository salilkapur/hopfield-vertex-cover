/* 
 * Utility functions to read/write graphs
 */
#ifndef _H_IO_UTILITY
#define _H_IO_UTILITY

#include "common.h"
#include "graph.h"

#define MAX_PREAMBLE 10000

void read_bin_graph(char*, struct graph*);
char get_edge(struct graph*, int i, int j);
#endif
