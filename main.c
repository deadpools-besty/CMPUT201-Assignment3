/* CMPUT 201 Assignment 3 */
/*Submitting student: Nana Andoh
Collaborators: None
References: https://cboard.cprogramming.com/c-programming/88542-dynamically-allocating-4d-arrays.html -- dynamically allocating 4d arrays
https://codereview.stackexchange.com/a/29276 -- generating random sequence of characters
*/

// TIMES (mins:secs)
/*      50          100         200         500         1000            2000            5000            10000
LCS      
LPS
LTS
LCPS
LCTS
*/

#include "main.h"

int main(int argc, char *argv[]) 
{

    
    int gen = 0, c = 0, t = 0, p = 0, ct = 0, cp = 0, in = 0, o = 0; // variables for cmd arguments
    char *f_output_str, *f_input_str;
    f_output_str = malloc(N*sizeof(char*)); // allocating space for output file name
    f_input_str = malloc(N*sizeof(char*)); // allocating space for input file name
    
    
    for (int i = 0; i < argc; i++) { // loop throgh each argument provided from command line and incrememnt the respective variable
    
        if (!strncmp(argv[i], "-g", 2)) gen++;
        if (!strcmp(argv[i], "-c")) c++;
        if (!strncmp(argv[i], "-t", 2)) t++;
        if (!strncmp(argv[i], "-p", 2)) p++;
        if (!strcmp(argv[i], "-ct")) ct++;
        if (!strncmp(argv[i], "-cp", 3)) cp++;
        if (!strncmp(argv[i], "-i", 2)) {
            strcpy(f_input_str, argv[i+1]);
            in++;
        }
        if (!strncmp(argv[i], "-o", 2)) {
            strcpy(f_output_str, argv[i+1]);
            o++;
        }
    }
    
    if (argc == 1) {
        print_options();
    } 
    else if (gen) { // generate random sequences
        
        int size1, size2;
        printf("Enter the lengths of the two sequences: ");
        scanf("%d %d", &size1, &size2);
        char *seq1 = malloc(size1 + 1);
        char *seq2 = malloc(size2 + 1);
        generate_seq(size1, seq1);
        generate_seq(size2, seq2);
        printf("%s\n", seq1);
        printf("%s\n", seq2);
        if (o) { // if -o flag is selected, output numbers to provided file
            FILE *fptr;
            fptr = fopen(f_output_str, "a");
            fprintf(fptr, "%s\n", seq1);
            fprintf(fptr, "%s\n", seq2);
            fclose(fptr);
        }
    }
    else if (c || ct || cp) { // LCS, LCTS, LCPS handling
        
        char seq1[N], seq2[N];

        if (!in) { // read in sequence through stdin
            printf("Enter the first sequence: ");
            strcpy(seq1, get_seq_stdin());

            printf("Enter the second sequence: ");
            strcpy(seq2, get_seq_stdin());
        }
        else if (in) { // read in sequence through file if -i flag is on
            FILE *ifptr;
            if ((ifptr = fopen(f_input_str,"r")) == NULL){
                printf("Error opening file");
                exit(1);
            }
            fscanf(ifptr, "%s\n%s", &seq1, &seq2);
            fclose(ifptr);
        }
        
        /*--------------------------------------------------LCS, LCSTS, LCPS---------------------------------------------------*/
        if ((ct && c) || (ct && cp) || (cp && ct)) {
            print_options();
        }
        
        else if (c) { // LCS
            char *lcs_string = (char *) malloc(strlen(lcs(seq1, seq2, strlen(seq1), strlen(seq2)))*sizeof(char));
            strcpy(lcs_string, lcs(seq1, seq2, strlen(seq1), strlen(seq2)));
            printf("# an LCS (length = %ld) for the two sequences is: %s\n", strlen(lcs_string), lcs_string);

            if (o) {
                FILE *ofptr = fopen(f_output_str, "a");
                fprintf(ofptr, "# an LCS (length = %ld) for the two sequences is: %s\n", strlen(lcs_string), lcs_string);
                fclose(ofptr);
            }
            free(lcs_string);   
        }
        
        else if (cp) { //LCPS
            char *lcps_string = (char *) malloc(strlen(lcps(seq1, seq2, strlen(seq1), strlen(seq2)))*sizeof(char));
            strcpy(lcps_string, lcps(seq1, seq2, strlen(seq1), strlen(seq2)));
            printf("# an LCPS (length = %ld) for the two sequences is: %s\n", strlen(lcps_string), lcps_string);
            if (o) {
                FILE *ofptr = fopen(f_output_str, "a");
                fprintf(ofptr, "# an LCPS (length = %ld) for the two sequences is: %s\n", strlen(lcps_string), lcps_string);
                fclose(ofptr);
            }
            free(lcps_string);
        }

        else if (ct) { // LCTS
            char *lcts_string = (char *) malloc(strlen(lcts(seq1, seq2, strlen(seq1), strlen(seq2)))*sizeof(char));
            strcpy(lcts_string, lcts(seq1, seq2, strlen(seq1), strlen(seq2)));
            printf("# an LCTS (length = %ld) for the two sequences is: %s\n", strlen(lcts_string), lcts_string);
            if (o) {
                FILE *ofptr = fopen(f_output_str, "a");
                fprintf(ofptr, "# an LTCS (length = %ld) for the two sequences is: %s\n", strlen(lcts_string), lcts_string);
                fclose(ofptr);
            }
            free(lcts_string);
        }

        /* ------------------------------------------------LPS and LTS----------------------------------------------------------*/
        if (p) { // LPS
            char *lps_string = (char *) malloc(strlen(lps(seq1, strlen(seq1))));
            strcpy(lps_string, lps(seq1, strlen(seq1)));
            printf("# an LPS (length = %ld) for the sequence is: %s\n", strlen(lps_string), lps_string);
            if (o) {
                FILE *ofptr = fopen(f_output_str, "a");
                fprintf(ofptr, "# an LPS (length = %ld) for the sequence is: %s\n", strlen(lps_string), lps_string);
                fclose(ofptr);
            }
            free(lps_string);
        }
        else if (t) { //LTS
            char *lts_string = (char *) malloc(strlen(lts(seq1, strlen(seq1))));
            strcpy(lts_string, lts(seq1, strlen(seq1)));
            printf("# an LTS of (length = %ld) is: %s\n", strlen(lts_string), lts_string);
            if (o) {
                FILE *ofptr = fopen(f_output_str, "a");
                fprintf(ofptr, "# an LTS (length = %ld) for the sequence is: %s\n", strlen(lts_string), lts_string);
                fclose(ofptr);
            }
            free(lts_string);
        }
    }
    
    else if (t || p) {
        
        char seq[N];
        if (in) {
            FILE *ifptr;
            if ((ifptr = fopen(f_input_str,"r")) == NULL){
                printf("Error opening file");
                exit(1);
            }
            fscanf(ifptr, "%s", &seq);
            fclose(ifptr);
       
        }
        else if (!in) {
            printf("Enter the a sequence: ");
            strcpy(seq, get_seq_stdin());
        }

        if ((c && p) || (c && t) || (p && t)) print_options();
        else if (p) { // LPS
            char *lps_string = (char *) malloc(strlen(lps(seq, strlen(seq))));
            strcpy(lps_string, lps(seq, strlen(seq)));
            printf("# an LPS (length = %ld) for the sequence is: %s\n", strlen(lps_string), lps_string);
            if (o) {
                FILE *ofptr = fopen(f_output_str, "a");
                fprintf(ofptr, "# an LPS (length = %ld) for the sequence is: %s\n", strlen(lps_string), lps_string);
                fclose(ofptr);
            }
            free(lps_string);
        }
        else if (t) { //LTS
            
            char *lts_string = (char *) malloc(strlen(lts(seq, strlen(seq))));            
            strcpy(lts_string, lts(seq, strlen(seq)));
            printf("# an LTS of (length = %ld) is: %s\n", strlen(lts_string), lts_string);
            if (o) {
                FILE *ofptr = fopen(f_output_str, "a");
                fprintf(ofptr, "# an LTS (length = %ld) for the sequence is: %s\n", strlen(lts_string), lts_string);
                fclose(ofptr);
            }
            free(lts_string);
        }
    }

    else print_options();
    return 0;
}