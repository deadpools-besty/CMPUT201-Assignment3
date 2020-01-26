#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lcs.h"
#define N 10000
const char* lps(char seq[], int len);
const char* lcps(char seq_1[], char seq_2[], int seq_1_len, int seq_2_len);