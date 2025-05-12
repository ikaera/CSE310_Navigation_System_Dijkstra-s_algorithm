// Irakli Eradze  ASU ID (emplid): 1222868231

#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H 1

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

typedef enum {WHITE, GRAY, BLACK} COLOR;

/*We need to have a data structure for vertices in the graph. Our algorithms also use a color system on vertices. The following is a part of the codes that I wrote. Note that the definition of COLOR in the following is NOT provided. */
typedef struct TAG_VERTEX {
    int index;
    COLOR color;
    double key;
    int pi;
    int position;
} VERTEX;
/*Here the field index is the index of the corresponding vertex. It does not change. The fields key is the length of the current best path from the source computed. The field position is used to record the position of the vertex in the min-heap array. You will find this very handy when DecreaseKey operations are needed. I use the key field (rather than the d field) to reuse my codes for the min-heap. 
Here is a sample usage of the data type VERTEX. 
pVERTEX *V; 
// V is a pointer to pointer to VERTEX 
V = (pVERTEX *) calloc(n+1, sizeof(pVERTEX)); 
// Now you can make reference to V[1], but not to V[1]->index 
for (int i=1; i<=n; i++){ 
V[i] = (VERTEX *) calloc(1, sizeof(VERTEX)); 
// Now you can make reference to V[1]->index 
} 
Please note that illegal memory access is the main cause of segmentation fault. 
*/

typedef VERTEX *pVERTEX;

/*a data structure for nodes on the adjacency lists of the graph*/
typedef struct TAG_NODE {
       int index;
       int u;
       int v;
       double w;
       struct TAG_NODE *next;
   } NODE;
   
   typedef NODE *pNODE;

/*In Project 2, I have implemented the min-heap data structure, where the HEAP data structure contains the fields capacity (of type int), size (of type int), and H (of type int *). In this project, you need to modify it so that H is of type ELEMENT **. The data structure ELEMENT contains only one required field: key (of type double). 
To partially re-use your implementation of Project 2, you can use the following: 
typedef VERTEX ELEMENT; 
typedef ELEMENT *pELEMENT; 
Because VERTEX has a field named key (of type double), your earlier implementations of min-heap should work as usual. Note that you can make reference to the four other fields defined in VERTEX, and in ELEMENT. 
In this project, the elements of the heap array should be pointers to objects of type VERTEX. To reuse codes with minimal modification, I used the following in my implementation. 
*/   

typedef VERTEX ELEMENT;
typedef ELEMENT *pELEMENT;

typedef struct TAG_HEAP{
int capacity; // capacity of the heap
int size; // current size of the heap
pELEMENT *H; // stores pointers to VERTEX elements. [array of pointers to indices of the ELEMENT array
       // int H; // array of indices to the ELEMENT array
// Other fields as you see fit
}HEAP;
typedef HEAP *pHEAP;

/* STACK 
    In order to print out the computed path from a source node s to a destination node t, we start from the destination node to trace out the path using the predecessor field. This will trace out the path in reverse order. In order to print the path in correct order, we need to use a stack. The elements of the stack should contain information (or pointers to information) about the corresponding vertices on the path. 
*/
typedef struct TAG_STACK {
    int top;
    int capacity;
    int *array;
} STACK;
typedef STACK *pSTACK;

#endif

/*Suggested Schedule 
The workload for this project is not light. It is recommended that you start working on it immediately. 
I suggest that you try the following schedule, starting immediately. 
1. Day 1: Get the data structures implemented and compiled on general.asu.edu. You can have each of the functions having an empty shell for now (just to have the correct syntax). 
2. Day 2: Read in the graph and build the adjacency lists for directed graphs, with flag=0, using network01.txt. Make sure it compiles and works correctly on general.asu.edu. You can use Example 1 as an aid. Submit to Gradescope Checkpoint 1 and see how many test cases your program passes. 
3. Day 3: Read in the graph and build the adjacency lists for directed graphs, with flag=1, using network01.txt. Make sure it compiles and works correctly on general.asu.edu. You can use Example 2 as an aid. Submit to Gradescope Checkpoint 1 and see how many test cases your program passes. 
4. Day 4: Read in the graph and build the adjacency lists for undirected graphs, with flag=0 and 1, using network02.txt. Make sure it compiles and works correctly on general.asu.edu. You can use Examples 3 and 4 as an aid. Submit to Gradescope Checkpoint 1 and see how many test cases your program passes. 
5. Day 5: Read in all valid instructions, and print the instructions to stderr. Make sure it compiles and works correctly on general.asu.edu. You should be able to get this done easily after the first project. Submit to Gradescope Checkpoint 1 and see how many test cases your program passes. 
6. Day 6: Write the function for SinglePair and PrintPath. Make sure it compiles and works correctly on general.asu.edu. Submit to Gradescope Checkpoint 1 and see how many test cases your program passes. 
7. Day 7: Write the function for SingleSource and PrintLength. Make sure it compiles and works correctly on general.asu.edu. Submit to Gradescope Checkpoint 1 and see how many test cases your program passes. 
20
8. Day 8: Work on all possible cases you can think of (including invalid instructions). Work on output format (use the diff utility to compare files). Submit to Gradescope Checkpoint 1 and see how many test cases your program passes. 
9. Day 9 and More: In case your program does not pass all the test cases, try to figure out the reason, and fix it. 

If you follow the above schedule, you should be able to complete this project using half of the time given. If you get one day’s work in two days, you should be on target to get a perfect score. If you cannot keep up with the proposed schedule, you need to work harder. Please note that the first few test cases are easy, but some of the later ones are much harder. Start early and manage your time wisely.
*/