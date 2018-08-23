#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN	1024	

char *trim(char *str)
{
	int i,j,n;
	char *result;
	n = strlen(str);
	result = (char*) malloc(MAX_LEN * sizeof(char));
	for(i = 0; str[i] == ' ' || str[i] == '\t' || str[i] == '\n'; i++);
	for(j = n-1; str[j] == ' '||str[j] == '\t' || str[j] == '\n'; j--);
	for(n = 0; i <= j;) result[n++] = str[i++];
	result[n] = '\0';
	return result;
}

char **split(char *input, char delimiter) 
{
	int i,j,k,n;
	char **result;
	n = strlen(input);
	for(i=j=0; i < n; i++) if(input[i] == delimiter) j++;
	result = (char**) malloc((1 + j) * sizeof(char*));
	for(i=j=k=0; i < n; i++) {
		if(input[i] == delimiter || (i+1) == n) {
			result[j] = (char*) malloc(MAX_LEN * sizeof(char));
			if((i+1) == n) 	memcpy(result[j], input+k+1, i-k);
			else if(k > 0) 	memcpy(result[j], input+k+1, i-k-1);
			else 		memcpy(result[j], input+k, i-k);
			j++; k=i;	
		}
	}
	return result;
}

int main(int argc, char **argv)
{
	printf("\"%s\"\n", trim("        hello wor  ld       "));
	return 0;
}
