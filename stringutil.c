#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1024

char *concat(char *sep, char **strings, int n_strings) {
	int i, j, k, sep_length, strs_length, total;
	char *out;
	sep_length = strlen(sep);
	for (i = strs_length = 0; i < n_strings; i++)
		strs_length += strlen(strings[i]);
	total = strs_length + (n_strings * sep_length);
	out = (char *)malloc(1 + total * sizeof(char));
	for (i = j = 0, k = strlen(strings[j]);
	     i < total - strlen(strings[j]) - sep_length;
	     i += (strlen(strings[j]) + sep_length), j++,
	    k = strlen(strings[j])) {
		memcpy(out + i, strings[j], k);
		memcpy(out + i + k, sep, sep_length);
	}
	memcpy(out + i, strings[j], strlen(strings[j]));
	out[i + strlen(strings[j])] = '\0';
	return out;
}

char *replicate(char *s, int n) {
	char *out;
	int i, sz;
	sz = strlen(s);
	out = (char *)malloc(sz * n * sizeof(char));
	i = 0;
	while (n-- > 0) {
		memcpy(out + i, s, sz);
		i += sz;
	}
	out[i] = '\0';
	return out;
}

char *substring(char *str, int i, int j) {
	char *result;
	int sz = j - 1;
	result = (char *)malloc(sz * sizeof(char));
	memcpy(result, str + i, sz + 1);
	result[j] = '\0';
	return result;
}

int is_whitespace(char c) {
	return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

char *trim(char *str) {
	int i, j, n;
	char *result;
	n = strlen(str);
	for (i = 0; 	is_whitespace(str[i]); i++)
		;
	for (j = n - 1; is_whitespace(str[j]); j--)
		;
	result = (char *)malloc(1 + (j - i) * sizeof(char));
	memcpy(result, str + i, j - i + 1);
	result[n] = '\0';
	return result;
}

char **split(char *input, char delimiter) {
	int i, j, k, n;
	char **result;
	n = strlen(input);
	for (i = j = 0; i < n; i++)
		if (input[i] == delimiter) j++;
	result = (char **)malloc((1 + j) * sizeof(char *));
	for (i = j = k = 0; i < n; i++) {
		if (input[i] == delimiter || (i + 1) == n) {
			result[j] = (char *)malloc(MAX_LEN * sizeof(char));
			if ((i + 1) == n)
				memcpy(result[j], input + k + 1, i - k);
			else if (k > 0)
				memcpy(result[j], input + k + 1, i - k - 1);
			else
				memcpy(result[j], input + k, i - k);
			j++;
			k = i;
		}
	}
	return result;
}


int main(int argc, char **argv) {
	char *s = "   hello world   	\
						\t			\
			\n						\
	";
	printf("Untrimmed: \"%s\"\n", s);
	printf("Trimmed: \"%s\"\n", trim(s));
	return 0;
}
