#include "lcs.h"

const char* lcs(char seq_1[], char seq_2[], int seq_1_len, int seq_2_len) {
	

	//int lcs_table[seq_1_len+1][seq_2_len+1];
	/*
    int * arr = (int *)malloc((seq_1_len + 1)*(seq_2_len+1)*sizeof(int));
	int (*lcs_table)[seq_1_len + 1] = (int (*)[seq_2_len + 1]) arr;
	*/
	int m = seq_1_len + 1;
	int n = seq_2_len + 1;
	int **lcs_table;
	lcs_table = malloc(sizeof(int*) *m);

	for (int i = 0; i < m; i++) {
		lcs_table[i] = malloc(sizeof(int) *n);
	}
	
	for (int row = 0; row <=seq_1_len; row++) {
		for (int col = 0; col <= seq_2_len; col++){
			if (row == 0 || col == 0) { // if either sequence is empty, there is no subsequence to compare so the lcs is 0
				lcs_table[row][col] = 0;
			}
			else if (seq_1[row - 1] == seq_2[col - 1]) { // if the letter at the two sequences match add 1 to the previous value
				lcs_table[row][col] = lcs_table[row - 1][col - 1] + 1;
			}
			else { // else compare the two previous possible values in the table and put the bigger one in the current position
				lcs_table[row][col] = lcs_table[row -1][col] > lcs_table[row][col - 1] ? lcs_table[row -1][col] : lcs_table[row][col - 1];
			}	
		}
	}
	
	int lcs_length = lcs_table[seq_1_len][seq_2_len]; // result of lcs computation aka the bottom right cell in the lcs table

	char* lcs_chars = calloc((lcs_length+1), sizeof(char*)); // char string for printing out the lcs
	lcs_chars[lcs_length] = '\0'; // terminating char for the string
	
	int seq_1_index = seq_1_len, seq_2_index = seq_2_len, lcs_index = lcs_length; 
	
	while (seq_1_index > 0 && seq_2_index > 0) {
		/* this while loop will essentially start from the bottom right of the lcs table and goes back up to store 
		each matching char in lcs_chars */
		if (seq_1[seq_1_index - 1] == seq_2[seq_2_index - 1]) {
			lcs_chars[lcs_index - 1] = seq_1[seq_1_index - 1]; // if chars are matching store that char at the current index in lcs chars
			seq_1_index--;
			seq_2_index--;
			lcs_index--; // then decrement all the indices to move further through the table
		}
		else if (lcs_table[seq_1_index - 1][seq_2_index] > lcs_table[seq_1_index][seq_2_index - 1]) {
			// otherwise check which previous number is bigger and decrement in that direction
			seq_1_index--;
		}
		else {
			seq_2_index--;
		}
	}
	
	free(lcs_table);
	//printf("LCS: %s\n", lcs_chars);
	return lcs_chars;
}

const char* lcs_4d(char s1[], char s2[], char s3[], char s4[], int l1, int l2, int l3, int l4) {


	int ****lcs_table2; // for dimensional look up table
	
	lcs_table2 = calloc(l1+1, sizeof(lcs_table2[0]));
	for (int w = 0; w < l1+1; w++) {
		lcs_table2[w] = calloc(l2+1, sizeof(lcs_table2[0][0]));
		for (int x = 0; x < l2+1; x++) {
			lcs_table2[w][x] = calloc(l3+1, sizeof(lcs_table2[0][0][0]));
			for (int y = 0; y < l3+1; y++) {
				lcs_table2[w][x][y] = calloc(l4+1, sizeof(lcs_table2[0][0][0][0]));
			}
		}
	}
	
	for (int i = 0; i <=l1; i++) {
		for (int j = 0; j <= l2; j++) {
			for (int k = 0; k <= l3; k++) {
				for (int l = 0; l <= l4; l++) {
					if (i == 0 || j == 0 || k == 0 || l == 0) {
						lcs_table2[i][j][k][l] = 0;
					}
					else if (s1[i - 1] == s2[j - 1] && s1[i - 1] == s3[k - 1] && s1[i - 1] == s4[l - 1]) {
						lcs_table2[i][j][k][l] = lcs_table2[i - 1][j - 1][k - 1][l - 1] + 1;
					}
					else {
						lcs_table2[i][j][k][l] = max(max(lcs_table2[i - 1][j][k][l], lcs_table2[i][j - 1][k][l]), max(lcs_table2[i][j][k - 1][l], lcs_table2[i][j][k][l - 1]));
					}
				}
			}
		}
	}

	int lcs_4d_len = lcs_table2[l1][l2][l3][l4];
	char* lcs_chars = calloc((lcs_4d_len+1), sizeof(char*));
	lcs_chars[lcs_4d_len] = '\0';

	int s1_idx = l1; int s2_idx = l2; int s3_idx = l3; int s4_idx = l4; int lcs_idx = lcs_4d_len;

	while (s1_idx > 0 && s2_idx > 0 && s3_idx > 0 && s4_idx > 0) {
		
		if (s1[s1_idx - 1] == s2[s2_idx - 1] && s1[s1_idx - 1] == s3[s3_idx - 1] && s1[s1_idx - 1] == s4[s4_idx - 1]){
			lcs_chars[lcs_idx - 1] = s1[s1_idx - 1];
			s1_idx--;s2_idx--;s3_idx--;s4_idx--; lcs_idx--;
		}
		else if (lcs_table2[s1_idx - 1][s2_idx][s3_idx][s4_idx] > lcs_table2[s1_idx][s2_idx - 1][s3_idx][s4_idx] && lcs_table2[s1_idx - 1][s2_idx][s3_idx][s4_idx] > lcs_table2[s1_idx][s2_idx][s3_idx - 1][s4_idx] && lcs_table2[s1_idx - 1][s2_idx][s3_idx][s4_idx] > lcs_table2[s1_idx][s2_idx][s3_idx][s4_idx - 1]) 
		{
			s1_idx--;
		}
		else if (lcs_table2[s1_idx][s2_idx - 1][s3_idx][s4_idx] > lcs_table2[s1_idx][s2_idx][s3_idx - 1][s4_idx] && lcs_table2[s1_idx][s2_idx - 1][s3_idx][s4_idx] > lcs_table2[s1_idx][s2_idx][s3_idx][s4_idx - 1]) {
			s2_idx--;
		}
		else if (lcs_table2[s1_idx][s2_idx][s3_idx - 1][s4_idx] > lcs_table2[s1_idx][s2_idx][s3_idx][s4_idx - 1]) {
			s3_idx--;
		}
		else s4_idx--;
	}
	//printf("%s\n", lcs_chars);
	free(lcs_table2);
	return lcs_chars;

}

int max(int i1, int i2) {
	if (i1 > i2) return i1;
	else return i2;
}