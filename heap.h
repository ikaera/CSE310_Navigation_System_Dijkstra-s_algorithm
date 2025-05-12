// Irakli Eradze  ASU ID (emplid): 1222868231

#ifndef HEAP_H
#define HEAP_H

#include "data_structures.h"
/*
typedef struct TAG_HEAP {
    int capacity;
    int size;
    pELEMENT *H;
} HEAP;

typedef HEAP *pHEAP;
*/

// Function prototypes for heap operations
// Heap operations
void Heapify(pHEAP heap, pVERTEX *V, int i); // maintains heap property after modifications
void BuildHeap(pHEAP heap, pVERTEX *V); 
pELEMENT ExtractMin(pHEAP heap, pVERTEX *V); // efficiently removes minimum element, it changes the size of array
void DecreaseKey(pHEAP heap, pVERTEX *V, int position, double newKey); // handles priority updates with position tracking
void Insert(pHEAP heap, pVERTEX *V, int index); // adds new elements while maintaining heap order

#endif // HEAP_H
