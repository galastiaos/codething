#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
	if(argc > 1){
		for(int i=0; i<argc; i++){
			printf("%s\n",argv[i]);
		}
		FILE *infile = fopen(argv[1],"rb");
		if(infile == NULL){
			perror("Error opening file ");
			return 1;
		}
		fseek(infile, 0, SEEK_END);
		long filesize=ftell(infile);
		rewind(infile);
		char *buf = (char *)malloc(filesize+1);
		if(buf==NULL){
			fprintf(stderr, "Memory allocation failed\n");
			free(buf);
			fclose(infile);
			return 1;
		}
		size_t bytesread = fread(buf,1,filesize,infile);
		if(bytesread != filesize){
			fprintf(stderr, "Reading error\n");
			free(buf);
			fclose(infile);
			return 1;
		}

		buf[bytesread] = '\0';
		printf("buffer:%s",buf);
		free(buf);
		fclose(infile);
		return 0;
	} else{
		printf("missing operators\n");
	}
	return 0;
}
