/*
 * functions for graph handling and manipulations
 */

#include "graph.h"

char get_edge(struct graph* G, int i, int j)
{
	int byte, bit;
	char mask;
	
	bit  = 7-(j & 0x00000007);
	byte = j >> 3;
	
	mask = masks[bit];
	return( (G->map[i][byte] & mask)==mask );
}
