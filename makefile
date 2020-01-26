program: main.o lps.o lcs.o lts.o utility.o
	gcc -Wall -std=c99 main.o lps.o lcs.o lts.o utility.o -o a3

main.o: main.c main.h
	gcc -Wall -std=c99 -c main.c

lps.o: lps.c lps.h
	gcc -Wall -std=c99 -c lps.c

lts.o: lcs.c lcs.h
	gcc -Wall -std=c99 -c lts.c

lcs.o: lcs.c lcs.h
	gcc -Wall -std=c99 -c lcs.c

utility.o: utility.c utility.h
	gcc -Wall -std=c99 -c utility.c

ovrwrt:
	make clean
	make
clean:
	rm -f *out *o