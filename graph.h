// Irakli Eradze  ASU ID (emplid): 1222868231

#ifndef GRAPH_H
#define GRAPH_H

#include "data_structures.h"

// Graph operations
void ReadGraph(const char *filename, const char *graphType, int flag, 
              pVERTEX **V, pNODE **ADJ, int *n, int *m);
void PrintAdjacencyLists(pVERTEX *V, pNODE *ADJ, int n);
void Dijkstra(pVERTEX *V, pNODE *ADJ, pHEAP heap, int source, int destination, int n);
void PrintPath(pVERTEX *V, pSTACK stack, int s, int t);
void PrintLength(pVERTEX *V, int s, int t);

#endif