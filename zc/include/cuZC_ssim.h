#include <stdio.h>
 
const int N = 16; 
const int blocksize = 16; 
 
__global__ void hello(char *a, int *b); 
