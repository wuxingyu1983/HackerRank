#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG		0

char p[10][100001];
char v[10][100001];

int output[10][100000];
int cnt[10];

int failure[10][100000];

void getFailure(char v[], int f[])
{
	int len = strlen(v);
	for (int i=1, j=f[0]=-1; i<len; ++i)
	{
		while (j >= 0 && v[j+1] != v[i])
			j = f[j];

		if (v[j+1] == v[i]) j++;

		f[i] = j;
	}
}

int can_match(char v, char p, int pos_v, int pos_p, int pos_dismatch_in_pat) {
	int ret = 1;

	if (v != p) {
		if (pos_dismatch_in_pat < 0) {
		}
		else {
			if (pos_p - pos_dismatch_in_pat > pos_v) {
				// can
			}
			else {
				// can not
				ret = 0;
			}
		}
	}

	return ret;
}

int save_humanity(char pat[], char vir[], int out[], int f[]) {
	int ret = 0;
	int len_p = strlen(pat);
	int len_v = strlen(vir);
	int dismatch = -1;

	if (len_p >= len_v) {
		getFailure(vir, f);

		int start = -1;

		for (int i=0, j=-1; i<len_p; ++i)
		{
			while (j >= 0 && !can_match(vir[j+1], pat[i], j+1, i, dismatch)) {
				//			while (j >= 0 && vir[j+1] != pat[i]) {
				if (-1 == f[j]) {
					i -= j;
					j = -1;
					dismatch = -1;
				}
				else {
					j = f[j];
				}
			}

			int exact_match = 0;
			if (can_match(vir[j+1], pat[i], j+1, i, dismatch)) {
				if (vir[j+1] == pat[i]) {
					exact_match = 1;
				}
				else {
					exact_match = 2;
				}
				j++;
			}
			//			if (vir[j+1] == pat[i]) j++;

			if (j == len_v-1)
			{
				out[ret ++] = i - len_v + 1;
				i = i - len_v + 1;
				j = -1;
				dismatch = -1;
				exact_match = 0;
			}

			if (2 == exact_match) {
				dismatch = i;
			}
			}
		}

		return ret;
	}

	int main() {
		int t;

#if DEBUG
		FILE * fp = fopen("input.txt", "r");
		fscanf(fp, "%d", &t);
		FILE * fp_out = fopen("output.txt", "w");
#else
		scanf("%d", &t);
#endif

		for (size_t i = 0; i < t; i++) {
#if DEBUG
			fscanf(fp, "%s %s", p[i], v[i]);
#else
			scanf("%s %s", p[i], v[i]);
#endif
			cnt[i] = save_humanity(p[i], v[i], output[i], failure[i]);
		}

		for (size_t i = 0; i < t; i++) {
			if (0 >= cnt[i]) {
				printf("No Match!\n");
			}
			else {
				int j = 0;
				printf("%d", output[i][j++]);
				while (j < cnt[i]) {
					printf(" %d", output[i][j++]);
				}
				printf("\n");
			}
		}

#if DEBUG
		fclose(fp);
		fclose(fp_out);
#endif

		return 0;
	}

