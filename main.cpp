// Irakli Eradze  ASU ID (emplid): 1222868231
// All memory allocation and deallocation is handled in main

#include "main.h"
#include "graph.h"
#include "heap.h"
#include "stack.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc != 4) {
        PrintError("Usage: ./PJ3 <InputFile> <GraphType> <Flag>");
        return 1;
    }
    
    // Validate arguments
    int flag = atoi(argv[3]);
    if ((strcmp(argv[2], "DirectedGraph") != 0 && 
         strcmp(argv[2], "UndirectedGraph") != 0) ||
        (flag != 0 && flag != 1)) {
        PrintError("Invalid arguments");
        return 1;
    }
    
    // Initialize data structures
    pVERTEX *V = NULL;
    pNODE *ADJ = NULL;
    int n, m;
    
    // Initialize heap
    HEAP heap;
    heap.capacity = 0;
    heap.size = 0;
    heap.H = NULL;
    
    // Initialize stack
    STACK stack;
    stack.top = -1;
    stack.capacity = 0;
    stack.array = NULL;
    
    // Read graph
    ReadGraph(argv[1], argv[2], flag, &V, &ADJ, &n, &m);
    
    // Allocate heap
    heap.capacity = n;
    heap.H = (pELEMENT *)calloc(n + 1, sizeof(pELEMENT));
    
    // Allocate stack
    stack.capacity = n;
    stack.array = (int *)malloc(n * sizeof(int));
    
    // Process commands
    char command[50];
    int arg1, arg2, last_source = -1;
    double arg3;
    
    while (NextInstruction(command, &arg1, &arg2, &arg3)) {
        if (strcmp(command, "Stop") == 0) break;
        
        if (strcmp(command, "PrintADJ") == 0) {
            PrintAdjacencyLists(V, ADJ, n);
        }
        else if (strcmp(command, "SingleSource") == 0) {
            last_source = arg1;
            Dijkstra(V, ADJ, &heap, arg1, -1, n);
        }
        else if (strcmp(command, "SinglePair") == 0) {
            last_source = arg1;
            Dijkstra(V, ADJ, &heap, arg1, arg2, n);
        }
        else if (strcmp(command, "PrintPath") == 0) {
            if (arg1 != last_source) {
                PrintError("Invalid source for PrintPath");
                continue;
            }
            PrintPath(V, &stack, arg1, arg2);
        }
        else if (strcmp(command, "PrintLength") == 0) {
            PrintLength(V, arg1, arg2);
        }
    }
    
    // Clean up memory (centralized in main)
    for (int i = 1; i <= n; i++) {
        free(V[i]);
        pNODE curr = ADJ[i];
        while (curr) {
            pNODE temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(V);
    free(ADJ);
    free(heap.H);
    free(stack.array);
    
    return 0;
}