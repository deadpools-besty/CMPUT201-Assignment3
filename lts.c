#include "lts.h"

const char* lts(char seq[], int len) {
	
	int split_pt = 0; int max_LCS = 0; int lts_len;
	char *lts; char lonest_string[10000];
	
	for (;split_pt < len; split_pt++) {
		
		int left_len = split_pt; int right_len = len - left_len;
		
		if (max_LCS > len - split_pt) break;
		// split string
		char *left = malloc(left_len + 1);
		memcpy(left, seq, left_len);
		left[left_len] = '\0';

		char *right = malloc(right_len + 1);
		memcpy(right, seq + left_len, right_len);
		right[right_len] = '\0';

		//printf("%d\nLeft: %s\tRight: %s\n", split_pt, left, right);

		int curr_lcs = strlen(lcs(left, right, left_len, right_len));
		
		if (curr_lcs > max_LCS) {
			
			max_LCS = curr_lcs;
			strcpy(lonest_string, lcs(left, right, left_len, right_len));
		}
		free(left); free(right);

	}

	lts_len = max_LCS*2;
	lts = malloc(lts_len + 1);
	lts[lts_len] = '\0';
	memcpy(lts, lonest_string, max_LCS);
	memcpy(lts+max_LCS, lonest_string, max_LCS);

	return lts;
	
}

const char* lcts(char seq_1[], char seq_2[], int l1, int l2) {
	
	
	int split_pt_1 = 0; int max_LCS = 0;

	char *lcts; char lonest_string[10000];

	for (; split_pt_1 < l1; split_pt_1++) {
		
		if (max_LCS > l1 - split_pt_1) break;
		int split_pt_2 = 0;
		int l_len_1 = split_pt_1; int r_len_1 = l1 - l_len_1;
		// split string 1
		char *left_1 = malloc(l_len_1 + 1);
		memcpy(left_1, seq_1, l_len_1);
		left_1[l_len_1] = '\0';
		
		char *right_1 = malloc(r_len_1 + 1);
		memcpy(right_1, seq_1 + l_len_1, r_len_1);
		right_1[r_len_1] = '\0';

		//printf("Left_1: %s\tRight_1: %s\n\n", left_1, right_1);

		for (; split_pt_2 < l2; split_pt_2++) {
			
			if (max_LCS > l2 - split_pt_2) break;
			int l_len_2 = split_pt_2; int r_len_2 = l2 - l_len_2;
			
			// split string 2
			char *left_2 = malloc(l_len_2 + 1);
			memcpy(left_2, seq_2, l_len_2);
			left_2[l_len_2] = '\0';

			char *right_2 = malloc(r_len_2 + 1);
			memcpy(right_2, seq_2 + l_len_2, r_len_2);
			right_2[r_len_2] = '\0';

			//printf("Left_2: %s\tRight_2: %s\n", left_2, right_2);

			// compute lcs between 4 split strings
			char lcs_string[10000];
			strcpy(lcs_string, lcs_4d(left_1, left_2, right_1, right_2, l_len_1, l_len_2, r_len_1, r_len_2));
			
			int curr_lcs = strlen(lcs_string);

			if (curr_lcs > max_LCS) {
				max_LCS = curr_lcs;
				strcpy(lonest_string, lcs_string);
			}
			 free(left_2);  free(right_2);
		}
		free(left_1); free(right_1);
	}
	
	int lcts_len = max_LCS*2;
	lcts = malloc(lcts_len + 1);
	lcts[lcts_len] = '\0';
	memcpy(lcts, lonest_string, max_LCS);
	memcpy(lcts+max_LCS, lonest_string, max_LCS);
	return lcts;
}