// Irakli Eradze  ASU ID (emplid): 122286823i1
//
#include <stdio.h>
#include <string.h>
#include "util.h"

// Function to parse the next instruction from stdin
//#include "util.h"
//#include <stdio.h>
//#include <string.h>

int NextInstruction(char *command, int *arg1, int *arg2, double *arg3) {
    char line[256];
    if (!fgets(line, sizeof(line), stdin)) return 0;
    
    int ret = sscanf(line, "%s", command);
    if (ret != 1) return 0;
    
    if (strcmp(command, "Stop") == 0) return 1;
    if (strcmp(command, "PrintADJ") == 0) return 1;
    if (strcmp(command, "SingleSource") == 0) 
        return (sscanf(line, "%s %d", command, arg1) == 2);
    if (strcmp(command, "SinglePair") == 0) 
        return (sscanf(line, "%s %d %d", command, arg1, arg2) == 3);
    if (strcmp(command, "PrintPath") == 0) 
        return (sscanf(line, "%s %d %d", command, arg1, arg2) == 3);
    if (strcmp(command, "PrintLength") == 0) 
        return (sscanf(line, "%s %d %d", command, arg1, arg2) == 3);
    
    return 0;
}

void PrintError(const char *message) {
    fprintf(stderr, "Error: %s\n", message);
}