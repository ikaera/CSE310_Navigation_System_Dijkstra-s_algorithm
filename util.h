// Irakli Eradze  ASU ID (emplid): 1222868231

#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototype for parsing instructions
// int nextInstruction(char *Word, int *index, double *newKey);

int NextInstruction(char *command, int *arg1, int *arg2, double *arg3);
void PrintError(const char *message);

#endif // UTIL_H
