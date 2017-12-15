/* 
 * Utility functions to read/write graphs
 * References: https://turing.cs.hbg.psu.edu/txn131/clique.html
 */

#include "io_utility.h"

/* getting count of vertices and edges from the preamble string, 
 * containing Dimacs format "p ??? num num" 
 */

int get_params(char* pp, struct graph *G)
{
	char c, *tmp;
	//char* pp = Preamble;
	int stop = 0;
	tmp = (char *)calloc(100, sizeof(char));
	
	int N = 0;
    int M = 0;
	
	while (!stop && (c = *pp++) != '\0'){
		switch (c)
		  {
			case 'c':
			  while ((c = *pp++) != '\n' && c != '\0');
			  break;
			  
			case 'p':
			  sscanf(pp, "%s %d %d\n", tmp, &N, &M);
			  stop = 1;
			  break;
			  
			default:
			  break;
		  }
	}
	
	free(tmp);
    
    //Updating graph structure
    G->N = N;
    G->M = M;

	if (N == 0 || M == 0)
	  return 0;  /* error */
	else
	  return 1;
}

void read_bin_graph(char* file, struct graph* G)
{

    int i, length = 0;
    char Preamble[MAX_PREAMBLE];
    FILE *fp;

    if ( (fp=fopen(file,"r"))==NULL ) { 
        printf("ERROR: Cannot open infile\n");
        exit(0);
    }

    if (!fscanf(fp, "%d\n", &length)) {
        printf("ERROR: Corrupted preamble.\n");
        exit(0);
    }

    if(length >= MAX_PREAMBLE) {
        printf("ERROR: Too long preamble.\n");
        exit(0);
    }
    
    printf("Reading graph preamble...\n");
    fread(Preamble, 1, length, fp);
    Preamble[length] = '\0';
    printf("Graph preamble read!\n");

    if (!get_params(Preamble, G)) {
        printf("ERROR: Corrupted preamble.\n");
        exit(10);
    }
    
    printf("Reading edges into the graph\n");
    printf("Graph Vertices: %ld\n", G->N);
    
    for ( i = 0
            ; i < G->N && fread(G->adj_list[i], 1, (int)((i + 8)/8), fp)
            ; i++ );
    
    printf("Edges read!\n");
    fclose(fp);
}
