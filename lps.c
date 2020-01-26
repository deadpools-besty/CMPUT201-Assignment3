#include "lps.h"

const char* lps(char seq[], int len) {
	// compute lps
	
	// memory allocation to handle larger arrays
	size_t n = len;
	int * array = (int *)
		malloc(n * n * sizeof(int));
	int (*lpstable)[n] = (int (*)[n]) array;
	
	//int lpslen;
	for (int i = 0; i < len; i++) { // fill diagonal with ones because the lps of a string of len(1) = 1
		lpstable[i][i] = 1;
	}

	// calculate LPS length
	for (int sub_len = 2; sub_len <= len; sub_len++) { // iterate through different lengths of substrings
		for (int first = 0; first < len - sub_len + 1; first++) {
			int last = sub_len + first - 1;
			if (sub_len == 2 && seq[first] == seq[last]) { // if the substring lenght is 2 and fist and last chars match then lps is 2
				lpstable[first][last] = 2;
			}
			else if (seq[first] == seq[last]) { // if the first and last chars match add 2 to the previous lps
				lpstable[first][last] = lpstable[first + 1][last - 1] + 2;
			}
			else { // if the first and last chars dont match, then the lps at that cell is the highest lps from a previous substring
				lpstable[first][last] = (lpstable[first + 1][last] > lpstable[first][last - 1]) ? lpstable[first + 1][last] : lpstable[first][last - 1];
			}
		}
	}
	
	//lpslen = lpstable[0][len - 1];

	// print LPS
	int index = lpstable[0][len-1];
	char* lpschars = calloc((index+1), sizeof(char*)); // array to store characters that make lps
	lpschars[index] = '\0'; index--;
	int row = 0; int col = len - 1; 
	
	// handles printing for odd lenghts
	while (index > -1 && row <= col) {
		if(seq[row] == seq[col]) {  
			lpschars[index--] = seq[row];
			row++; col--;
		}
		else {
			if (lpstable[row + 1][col] > lpstable[row][col - 1]) {
				row++;
			}
			else {
				col--;
			} 
		}
	}

	
	int i = 0;
	int mid = lpstable[0][len - 1]/2; 
	int j = lpstable[0][len - 1] - 1;
	while (j >= mid) {
		lpschars[i] = lpschars[j]; i++; j--;
	}
	
	free(array);
	/*printf("An LPS (length = %d) is: ", lpslen);
	printf("%s\n", lpschars);*/

	return lpschars;
}

const char* lcps(char seq_1[], char seq_2[], int seq_1_len, int seq_2_len) {

	// rev strings, find LCS between orig string and reveresed, then find lcs between to LCS's	
	
	// reverse string 1
	char rev_1[N], rev_2[N];
	int start, fin, count = 0;
	while (seq_1[count] != '\0') count++;
	fin = count - 1;
	for (start = 0; start < count; start++) {
		rev_1[start] = seq_1[fin];
		fin--;
	}
	rev_1[start] = '\0';
	
	// reverse string 2
	int start2, fin2, count2 = 0;
	while (seq_2[count2] != '\0') count2++;
	fin2 = count2 - 1;
	for (start2 = 0; start2 < count2; start2++) {
		rev_2[start2] = seq_2[fin2];
		fin2--;
	}
	rev_2[start2] = '\0';

	// compute LCS between all 4 s1, rev1, s2, rev2 using lcs_4d functions
	char *lcps_str = calloc(N, sizeof(char*));
	strcpy(lcps_str, lcs_4d(seq_1, seq_2, rev_1, rev_2, seq_1_len, seq_2_len, seq_1_len, seq_2_len));

	return lcps_str;
	
}
