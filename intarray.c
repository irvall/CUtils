#include <stdio.h>
#include <stdlib.h>

struct pair {
	int a,b;
};

struct pair new_pair(int a, int b) {
	struct pair p;
	p.a = a;
	p.b = b;
	return p;
}

struct pair* all_pairs(int *xs, int *ys, int xlen, int ylen) {
	int sz = xlen * ylen;
	struct pair *pairs;
	pairs = malloc(sz * sizeof(struct pair));
	int k = 0;
	for(int i = 0; i < xlen; i++) {
		for(int j = 0; j < ylen; j++) {
			pairs[k++] = new_pair(xs[i], ys[j]);
		}
	}
	return pairs;
}

void show_pairs(struct pair *pairs, int n) {
	int i;
	printf("[");
	for(i = 0; i < n-1; i++) {
		printf("(%d, %d), ", pairs[i].a, pairs[i].b);
	}
	printf("(%d, %d)]\n", pairs[i].a, pairs[i].b);
}

int main(int argc, char const *argv[])
{
	int xs[] = {1,2,3};
	int ys[] = {4,5};
	struct pair *prs = all_pairs(xs, ys, 3, 2);
	show_pairs(prs, 6);
	return 0; 
}