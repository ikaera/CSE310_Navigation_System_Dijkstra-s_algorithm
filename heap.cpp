// Irakli Eradze  ASU ID (emplid): 1222868231

#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

// Function to maintain the heap property at index i
/* MIN-HEAPIFY(A, i)
    l = LEFT(i)
    r = RIGHT(i)
    if l ≤ heap-size[A] and A[l] < A[i] then
        smallest = l
    else
        smallest = i
    if r ≤ heap-size[A] and A[r] < A[smallest] then
        smallest = r
    if smallest ≠ i then
        exchange A[i] and A[smallest]
        MIN-HEAPIFY(A, smallest) */
void Heapify(pHEAP heap, pVERTEX *V, int i) {
    int l = 2 * i;
    int r = 2 * i + 1;
    int smallest = i;

    if (l <= heap->size && V[heap->H[l]->index]->key < V[heap->H[smallest]->index]->key)
        smallest = l;
    if (r <= heap->size && V[heap->H[r]->index]->key < V[heap->H[smallest]->index]->key)
        smallest = r;
    if (smallest != i) {
        pELEMENT temp = heap->H[i];
        heap->H[i] = heap->H[smallest];
        heap->H[smallest] = temp;
        
        V[heap->H[i]->index]->position = i;
        V[heap->H[smallest]->index]->position = smallest;
        
        Heapify(heap, V, smallest);
    }
}

// Function to build the heap using the linear-time BuildHeap algorithm
/* BUILD-MIN-HEAP(A)
    heap-size[A] = length[A]
    for i = \[ \text{length}[A]/2 \] down to 1 do
        MIN-HEAPIFY(A, i) */
void BuildHeap(pHEAP heap, pVERTEX *V) {
    for (int i = heap->size / 2; i >= 1; i--)
        Heapify(heap, V, i);
}

// Function to extract the minimum element from the heap
/*EXTRACT-MIN(A)
    if heap-size[A] < 1 then
        "error: heap empty"
    else
        min = A[1]
        A[1] = A[heap-size[A]]
        heap-size[A]--
        MIN-HEAPIFY(A, 1)
        return min */
pELEMENT ExtractMin(pHEAP heap, pVERTEX *V) {
    if (heap->size < 1) {
        fprintf(stderr, "Error: heap underflow\n");
        return NULL;
    }

    pELEMENT min = heap->H[1];
    heap->H[1] = heap->H[heap->size];
    V[heap->H[1]->index]->position = 1;
    heap->size--;
    Heapify(heap, V, 1);
    return min;
}
// Function to decrease the key of an element in the heap
/* DECREASE-KEY(A, i, key)
    if key > A[i] then
        “error: new key is larger than current key”
    else
        A[i] := key
        while i > 1 and A[PARENT(i)] > A[i]
            exchange A[i] with A[PARENT(i)]
            i := PARENT(i) */
void DecreaseKey(pHEAP heap, pVERTEX *V, int position, double newKey) {
    heap->H[position]->key = newKey;
    while (position > 1 && 
           V[heap->H[position/2]->index]->key > V[heap->H[position]->index]->key) {
        pELEMENT temp = heap->H[position];
        heap->H[position] = heap->H[position/2];
        heap->H[position/2] = temp;
        
        heap->H[position]->position = position;
        heap->H[position/2]->position = position/2;
        
        position = position/2;
    }
}

// Function to insert an element into the heap
/*MIN-HEAP-INSERT(A, key)
    heap-size[A]++
    i := heap-size[A]
    A[i] = ∞
    HEAP-DECREASE-KEY(A, i, key)*/
void Insert(pHEAP heap, pVERTEX *V, int index) {
    if (heap->size == heap->capacity) {
        fprintf(stderr, "Error: heap overflow\n");
        return;
    }

    heap->size++;
    heap->H[heap->size] = V[index];
    V[index]->position = heap->size;
    DecreaseKey(heap, V, heap->size, V[index]->key);
}