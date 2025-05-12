// Irakli Eradze  ASU ID (emplid): 1222868231

#include "graph.h"
#include "heap.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>  // For DBL_MAX

/* Reads graph from file and builds adjacency lists
   - filename: Input file containing graph data
   - graphType: "DirectedGraph" or "UndirectedGraph" 
   - flag: 0=prepend new nodes, 1=append new nodes
   - V: Output array of vertices
   - ADJ: Output adjacency lists
   - n: Output number of vertices
   - m: Output number of edges
*/
void ReadGraph(const char *filename, const char *graphType, int flag, 
              pVERTEX **V, pNODE **ADJ, int *n, int *m) {
    FILE *fp = fopen(filename, "r");
    fscanf(fp, "%d %d", n, m);
    
    *V = (pVERTEX *)calloc(*n + 1, sizeof(pVERTEX));
    for (int i = 1; i <= *n; i++) {
        (*V)[i] = (VERTEX *)malloc(sizeof(VERTEX));
        (*V)[i]->index = i;
        (*V)[i]->key = DBL_MAX;
        (*V)[i]->pi = 0;
        (*V)[i]->color = WHITE;
    }
    
    *ADJ = (pNODE *)calloc(*n + 1, sizeof(pNODE));
    
    for (int i = 0; i < *m; i++) {
        int index, u, v;
        double w;
        fscanf(fp, "%d %d %d %lf", &index, &u, &v, &w);
        
        pNODE new_node = (pNODE)malloc(sizeof(NODE));
        new_node->index = index;
        new_node->u = u;
        new_node->v = v;
        new_node->w = w;
        
        if (flag) {
            new_node->next = NULL;
            if (!(*ADJ)[u]) (*ADJ)[u] = new_node;
            else {
                pNODE curr = (*ADJ)[u];
                while (curr->next) curr = curr->next;
                curr->next = new_node;
            }
        } else {
            new_node->next = (*ADJ)[u];
            (*ADJ)[u] = new_node;
        }
        
        if (strcmp(graphType, "UndirectedGraph") == 0) {
            pNODE rev_node = (pNODE)malloc(sizeof(NODE));
            rev_node->index = index;
            rev_node->u = v;
            rev_node->v = u;
            rev_node->w = w;
            
            if (flag) {
                rev_node->next = NULL;
                if (!(*ADJ)[v]) (*ADJ)[v] = rev_node;
                else {
                    pNODE curr = (*ADJ)[v];
                    while (curr->next) curr = curr->next;
                    curr->next = rev_node;
                }
            } else {
                rev_node->next = (*ADJ)[v];
                (*ADJ)[v] = rev_node;
            }
        }
    }
    fclose(fp);
}
/* Prints the adjacency list representation of the graph
   - V: Vertex array
   - ADJ: Adjacency lists to print
   - n: Number of vertices
*/
void PrintAdjacencyLists(pVERTEX *V, pNODE *ADJ, int n) {
    for (int i = 1; i <= n; i++) {
        printf("ADJ[%d]:", i);
        pNODE curr = ADJ[i];
        while (curr) {
            printf("-->[%d %d: %.2f]", curr->u, curr->v, curr->w);
            curr = curr->next;
        }
        printf("\n");
    }
}

/*
Shortest Path Algorithm 
For improved efficiency, you should implement the following version of Dijkstra’s shortest s-t path algorithm. 
Dijkstra-ST(G, w, s, t) 
01: FOR v=1 TO n { 
02: V[v]->index = v; 
03: V[v]->key = infinity; 
04: V[v]->pi = NULL; 
05: V[v]->color = WHITE; 
06: V[v]->position = 0; 
07: } 
08: Create empty min-heap pHeap; 
09: Set the key of s to 0, and the color of s to GRAY; 
10: Insert s into pHeap; 
11: WHILE pHeap->size > 0 { 
12: u = ExtractMin(pHeap); 
13: IF (u == t) THEN STOP; 
14: FOR each v on ADJ[u] { 
15: IF v is WHITE { 
16: Set the color of v to GRAY; 
16: Update v’s key, pi; // Relax(u, v, w); 
17: Insert v into pHeap; 
18: }ELSE IF v is GRAY { 
19: Relax(u, v, w); 
20: Call DecreaseKey if nexessary; // Using the position field of v 21: } 
22: } 
23: Color u BLACK; 
24: } 
For single-pair shortest path, both s and t are in {1, 2, . . . , n}. For single-source shortest paths, s is in {1, 2, . . . , n}, t is set to −1. 
*/
/* Finds shortest paths using Dijkstra's algorithm
   - V: Vertex array
   - ADJ: Adjacency lists
   - heap: Priority queue (MinHeap) for the algorithm
   - source: Starting vertex
   - destination: Target vertex (-1 for all paths)
   - n: Number of vertices
*/
void Dijkstra(pVERTEX *V, pNODE *ADJ, pHEAP heap, int source, int destination, int n) {
    heap->size = 0;
    for (int i = 1; i <= n; i++) {
        V[i]->key = DBL_MAX;
        V[i]->pi = 0;
        V[i]->color = WHITE;
    }
    
    V[source]->key = 0.0;
    V[source]->color = GRAY;
    Insert(heap, V, source);
    
    while (heap->size > 0) {
        pELEMENT u_element = ExtractMin(heap, V);
        if (!u_element) break;
        
        int u = u_element->index;
        V[u]->color = BLACK;
        
        if (destination != -1 && u == destination) break;
        
        pNODE edge = ADJ[u];
        while (edge) {
            int v = edge->v;
            double new_key = V[u]->key + edge->w;
            
            if (V[v]->color == WHITE) {
                V[v]->key = new_key;
                V[v]->pi = u;
                V[v]->color = GRAY;
                Insert(heap, V, v);
            } 
            else if (V[v]->color == GRAY && new_key < V[v]->key) {
                V[v]->key = new_key;
                V[v]->pi = u;
                DecreaseKey(heap, V, V[v]->position, new_key);
            }
            edge = edge->next;
        }
    }
}

/* Prints the shortest path between two vertices
   - V: Vertex array with computed paths
   - stack: Temporary storage for path reversal
   - s: Source vertex
   - t: Target vertex
*/
void PrintPath(pVERTEX *V, pSTACK stack, int s, int t) {
    if (V[t]->key == DBL_MAX) {
        printf("There is no path from %d to %d.\n", s, t);
        return;
    }
    
    int current = t;
    while (current != 0 && current != s) {
        Push(stack, current);
        current = V[current]->pi;
    }
    Push(stack, s);
    
    printf("The shortest path from %d to %d is:\n", s, t);
    printf("[%d:%8.2lf]", s, V[s]->key);
    
    while (!IsEmpty(stack)) {
        int v = Pop(stack);
        if (v != s) printf("-->[%d:%8.2lf]", v, V[v]->key);
    }
    printf(".\n");
}

/* Prints only the length of the shortest path
   - V: Vertex array with computed paths
   - s: Source vertex
   - t: Target vertex
*/
void PrintLength(pVERTEX *V, int s, int t) {
    if (V[t]->key == DBL_MAX) {
        printf("There is no path from %d to %d.\n", s, t);
    } else {
        printf("The length of the shortest path from %d to %d is: %8.2lf\n", s, t, V[t]->key);
    }
}