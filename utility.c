#include "utility.h"


const char* get_seq_stdin()
{

    char* seq;
    seq = calloc(N, sizeof(char*));
    
    while (1==1) {
        int non_digit = 0;
		scanf("%[^\n]c", seq);
		while(getchar() != '\n'); // clears the input buffer 
		
		// goes through sequence to check for non-digit character
        
		for (int i = 0; seq[i] != '\0'; i++) {
            if (isalpha(seq[i]) != 0) {
				
                non_digit++;
			}
		}
		
		if (non_digit == 0) {
			break;
		}
		else {
			printf("Error, non-digit character detected. Enter sequence again.\n");
		}
	}

    return seq;

}

void generate_seq(int len, char *seq)
{
    static char charset[] = "0123456789";
    int l = (int) (sizeof(charset) -1);
        for (int n = 0;n < len ;n++) {
            int key = rand() % l;
            seq[n] = charset[key];
        }

        seq[len] = '\0';
}

void print_options(void)
{
    printf("This program can be run with the following command line arguements: \n\n");
    printf("-g:\tto generate an instance consisting of two sequences over the digit alphabet\n");
    printf("-c:\tto compute an LCS for the two input sequences\n");
    printf("-t:\tto compute an LTS for the input sequence\n");
    printf("-p:\tto compute an LPS for the input sequence\n");
    printf("-ct:\tto compute an LCTS for the two input sequences\n");
    printf("-i inputfilename:\tto read in sequence(s) from file \"inputfilename\"\n");
    printf("-o outputfilename:\tto read in sequence(s) from file \"outputfilename\"\n");
}