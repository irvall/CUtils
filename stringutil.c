#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1024

char *concat(char *sep, char **strings, int n_strings) {
	int i, j, k, sep_length, strs_length, total;
	char *out;
	sep_length = strlen(sep);
	for (i = 0, strs_length = 0; i < n_strings; i++)
		strs_length += strlen(strings[i]);
	total = strs_length + (n_strings * sep_length);
	out = (char *)malloc(1 + total * sizeof(char));
	for (i = 0; i < total; i += (strlen(strings[i]) + sep_length)) {
		memcpy(out + i, strings[i], strlen(strings[i]));
		memcpy(out + i + strlen(strings[i]), sep, sep_length);
	}
	out[i] = '\0';
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
	result = (char *)malloc((j - i) * sizeof(char));
	memcpy(result, str + i, j - i + 1);
	result[j] = '\0';
	return result;
}

char *trim(char *str) {
	int i, j, n;
	char *result;
	n = strlen(str);
	result = (char *)malloc(MAX_LEN * sizeof(char));
	for (i = 0; str[i] == ' ' || str[i] == '\t' || str[i] == '\n'; i++)
		;
	for (j = n - 1; str[j] == ' ' || str[j] == '\t' || str[j] == '\n'; j--)
		;
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
	char *sep = "x";
	char *strings[] = {"a", "b", "b", "a"};
	char *con = concat(sep, strings, 4);
	printf("concatted: %s\n", con);
	return 0;
}
