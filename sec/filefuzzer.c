/* original code from DeMott fuzzing book 
 * modified by Sebastien Duquette
 * */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 6250577
int NUM_FILES = 500;	

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("usage: filefuzzer <filename> [<number_of_files>]\n");
		return(0);
	}
	if (argc == 3) {
		NUM_FILES = atoi(argv[2]);
	}
	
	FILE *in, *out, *lout;
	unsigned int n, i, j;
	char *buf = malloc(SIZE);
	char *backup = malloc(SIZE);
	char outfile[1024];
	int rn, rn2, rn3, rn4;
	int rbyte;
	int numwrites;
	
	in = fopen(argv[1], "r");
	n = read(fileno(in), buf, SIZE);
	memcpy(backup, buf, n);

	lout=fopen("list", "w");
	
	srand(time(NULL));
	
	for(i=0; i<NUM_FILES; i++)
	{
		//seek and write
		numwrites=rand() % 16;
		numwrites++;

		printf("[+] Writing %d bytes\n", numwrites);
		for(j=0; j<numwrites; j++)
		{
			rbyte = rand() % 257;
			if( rbyte == 256 )
				rbyte = -1;
			rn = rand() % n - 1;
			printf("[+] buf[%d] = %d\n", rn, rbyte);
			buf[rn] = rbyte;
		}
		
		sprintf(outfile, "%s-%d.out", argv[1], i);
		out = fopen(outfile, "w");
		write(fileno(out), buf, n);
		fclose(out);
		fprintf(lout, "%s\n", outfile);
		memcpy(buf, backup, n);
	}
}	
