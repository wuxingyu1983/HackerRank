#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG		0

char p[100001];
char v[100001];

int z[200002];
int rz[200002];

char str[200002];
char rstr[200002];

int output[10][100000];
int cnt[10];

#define max(x,y)  (x>y?x:y)
#define min(x,y)  (x<y?x:y)

void z_function(char s[], int z[])
{
	int n = strlen(s);

	memset(z, 0, sizeof(0));
	z[0] = n;

	int x = 0, y = 0;
	for (int i=1; i<n; i++)
	{
		z[i] = max(0, min(z[i-x], y-i+1));
		while (i + z[i] < n && s[z[i]] == s[i + z[i]])
		{
			x = i;
			y = i + z[i];
			z[i]++;
		}
	}
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

	for (size_t i_t = 0; i_t < t; i_t++) {
		memset(p, 0, sizeof(p));
		memset(v, 0, sizeof(v));
#if DEBUG
		fscanf(fp, "%s %s", p, v);
#else
		scanf("%s %s", p, v);
#endif
		memset(str, 0 , sizeof(str));
		memset(rstr, 0 , sizeof(rstr));
		memset(z, 0 , sizeof(z));
		memset(rz, 0 , sizeof(rz));

		int plen = strlen(p);
		int vlen = strlen(v);
		int index = 0;

		for (int i = 0; i < vlen; i ++) {
			str[i] = v[i];
			rstr[vlen - 1 - i] = v[i];
		}

		str[vlen] = '$';
		rstr[vlen] = '$';

		for (int i = 0; i < plen; i ++) {
			str[vlen + 1 + i] = p[i];
			rstr[vlen + plen - i] = p[i];
		}

		z_function(str, z);
		z_function(rstr, rz);

		for (int i = 0; i < plen; i ++) {
			if (plen + vlen - i - vlen + 1 > vlen && z[i + vlen + 1] + rz[plen + vlen - i - vlen + 1] >= vlen - 1) {
				output[i_t][cnt[i_t]++] = i;
			}
		}
	}

	for (size_t i = 0; i < t; i++) {
		if (0 >= cnt[i]) {
#if DEBUG
			fprintf(fp_out, "No Match!\n");
#else
			printf("No Match!\n");
#endif
		}
		else {
			int j = 0;
#if DEBUG
			fprintf(fp_out, "%d", output[i][j++]);
#else
			printf("%d", output[i][j++]);
#endif
			while (j < cnt[i]) {
#if DEBUG
				fprintf(fp_out, " %d", output[i][j++]);
#else
				printf(" %d", output[i][j++]);
#endif
			}
#if DEBUG
			fprintf(fp_out, "\n");
#else
			printf("\n");
#endif
		}
	}

#if DEBUG
	fclose(fp);
	fclose(fp_out);
#endif

	return 0;
}
