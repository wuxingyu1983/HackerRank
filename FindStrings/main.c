#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG		0

#define MAX_LEN		100051

int n;
char first_char;
char com_str[MAX_LEN];
int remain[MAX_LEN];
int k[500];
char * output[50];
int old_pos[500];

void insert_sort(int s[], int len) {
	int pos = 0;
	while (pos < len) {
		if (0 == pos) {
			k[pos] = s[pos];
			old_pos[pos] = pos;
		}
		else {
			int i;
			for (i = 0; i < pos; i ++) {
				if (k[i] > s[pos]) {
					break;
				}
			}

			if (i < pos) {
				for (int j = pos - 1; j >= i; j --) {
					k[j + 1] = k[j];
					old_pos[j + 1] = old_pos[j];
				}
			}

			k[i] = s[pos];
			old_pos[i] = pos;
		}
		pos ++;
	}
}

struct myTuple {
    int originalIndex;   // stores original index of suffix
    int firstHalf;       // store rank for first half of suffix
    int secondHalf;      // store rank for second half of suffix
    struct myTuple * next;
    struct myTuple * last;
};

struct myTuple round1[MAX_LEN];
struct myTuple round2[MAX_LEN];

void radix_sort(struct myTuple s[], int len) {
	struct myTuple * negative = NULL;
	int buckket_size = len < (26 + n) ? (26 + n) : len;
	struct myTuple * * buckets = (struct myTuple * *)malloc(sizeof(struct myTuple * ) * buckket_size);
	memset(buckets, 0, sizeof(struct myTuple * ) * buckket_size);

	for (size_t i = 0; i < len; i++) {
		if (-1 == s[i].secondHalf) {
			if (NULL == negative) {
				negative = &round1[i];
				negative->firstHalf = s[i].firstHalf;
				negative->secondHalf = s[i].secondHalf;
				negative->originalIndex = s[i].originalIndex;
				negative->next = NULL;
				negative->last = negative;
			}
			else {
				negative->last->next = &round1[i];
				negative->last->next->firstHalf = s[i].firstHalf;
				negative->last->next->secondHalf = s[i].secondHalf;
				negative->last->next->originalIndex = s[i].originalIndex;
				negative->last->next->next = NULL;
				negative->last = negative->last->next;
			}
		}
		else {
			if (NULL == buckets[s[i].secondHalf]) {
				buckets[s[i].secondHalf] = &round1[i];
				buckets[s[i].secondHalf]->firstHalf = s[i].firstHalf;
				buckets[s[i].secondHalf]->secondHalf = s[i].secondHalf;
				buckets[s[i].secondHalf]->originalIndex = s[i].originalIndex;
				buckets[s[i].secondHalf]->next = NULL;
				buckets[s[i].secondHalf]->last = buckets[s[i].secondHalf];
			}
			else {
				buckets[s[i].secondHalf]->last->next = &round1[i];
				buckets[s[i].secondHalf]->last->next->firstHalf = s[i].firstHalf;
				buckets[s[i].secondHalf]->last->next->secondHalf = s[i].secondHalf;
				buckets[s[i].secondHalf]->last->next->originalIndex = s[i].originalIndex;
				buckets[s[i].secondHalf]->last->next->next = NULL;
				buckets[s[i].secondHalf]->last = buckets[s[i].secondHalf]->last->next;
			}
		}
	}

	int index = 0;
	struct myTuple * p = negative;
	struct myTuple * next;
	while (p) {
		s[index ++] = *p;
		next = p->next;
		p = next;
	}
	negative = NULL;

	for (size_t i = 0; i < buckket_size; i++) {
		if (buckets[i]) {
			p = buckets[i];

			while (p) {
				s[index ++] = *p;
				next = p->next;
				p = next;
			}

			buckets[i] = NULL;
		}
	}

	for (size_t i = 0; i < len; i++) {
		if (NULL == buckets[s[i].firstHalf]) {
			buckets[s[i].firstHalf] = &round2[i];
			buckets[s[i].firstHalf]->firstHalf = s[i].firstHalf;
			buckets[s[i].firstHalf]->secondHalf = s[i].secondHalf;
			buckets[s[i].firstHalf]->originalIndex = s[i].originalIndex;
			buckets[s[i].firstHalf]->next = NULL;
			buckets[s[i].firstHalf]->last = buckets[s[i].firstHalf];
		}
		else {
			buckets[s[i].firstHalf]->last->next = &round2[i];
			buckets[s[i].firstHalf]->last->next->firstHalf = s[i].firstHalf;
			buckets[s[i].firstHalf]->last->next->secondHalf = s[i].secondHalf;
			buckets[s[i].firstHalf]->last->next->originalIndex = s[i].originalIndex;
			buckets[s[i].firstHalf]->last->next->next = NULL;
			buckets[s[i].firstHalf]->last = buckets[s[i].firstHalf]->last->next;
		}
	}

	index = 0;
	for (size_t i = 0; i < buckket_size; i++) {
		if (buckets[i]) {
			p = buckets[i];

			while (p) {
				s[index ++] = *p;
				next = p->next;
				p = next;
			}

			buckets[i] = NULL;
		}
	}
}

struct myTuple LS[18][MAX_LEN];
struct myTuple L[MAX_LEN];

int getLcp(int prev, int curr, int stp, int len) {
    int ret = 0;
    int size = pow(2.0, (double)stp);

    if (0 == stp) {
        if (LS[stp][prev].firstHalf == LS[stp][curr].firstHalf) {
            ret += size;
        }
    }
    else {
        if (LS[stp][prev].firstHalf == LS[stp][curr].firstHalf) {
            ret += size;
            if (-1 != LS[stp][prev].secondHalf && -1 != LS[stp][curr].secondHalf) {
                ret += getLcp(prev + size, curr + size, stp - 1, len);
            }
        }
        else {
            ret = getLcp(prev, curr, stp - 1, len);
        }
    }

    return ret;
}

int suffixRank[18][MAX_LEN];
int lcp[MAX_LEN];

void findStrings(char a[], int q) {
    clock_t start,finish;
    double TheTimes;

    int len = strlen(a);

    for(int i = 0; i < len; ++i) {
        suffixRank[0][i] = a[i] - first_char;
    }

    for(int i = 0; i < len; ++i) {
        LS[0][i].firstHalf = suffixRank[0][i];
        LS[0][i].secondHalf = i + 1 < len ? suffixRank[0][i + 1] : -1;
        LS[0][i].originalIndex = i;

        L[i].firstHalf = LS[0][i].firstHalf;
        L[i].secondHalf = LS[0][i].secondHalf;
        L[i].originalIndex = i;
    }

    int cnt, stp;
    for(cnt = 1, stp = 1; cnt < len; cnt *= 2, ++stp) {
        start = clock();
        radix_sort(L, len);
        finish = clock();
        TheTimes = (double)(finish-start)/CLOCKS_PER_SEC;
#if DEBUG
//        printf("radix_sort consume : %fs\n", TheTimes);
#endif

        if (len <= cnt * 2) {
            break;
        }
        else {
            // len > cnt * 2
            suffixRank[stp][L[0].originalIndex] = 0;

            for(int i = 1, currRank = 0; i < len; ++i) {
                if(L[i - 1].firstHalf != L[i].firstHalf || L[i - 1].secondHalf != L[i].secondHalf)
                ++currRank;

                suffixRank[stp][L[i].originalIndex] = currRank;
            }

            for(int i = 0; i < len; ++i) {
                L[i].firstHalf = suffixRank[stp][i];
                L[i].secondHalf = i + (cnt * 2) < len ? suffixRank[stp][i + (cnt * 2)] : -1;
                L[i].originalIndex = i;

                LS[stp][i].firstHalf = L[i].firstHalf;
                LS[stp][i].secondHalf = L[i].secondHalf;
                LS[stp][i].originalIndex = i;
            }
        }
    }

    stp --;
    lcp[0] = 0;
    for (int i = 1; i < len; i++){
        lcp[i] = getLcp(L[i - 1].originalIndex, L[i].originalIndex, stp, len);
    }

	long long sum = 0;
	int index_in_l = n;
	int index_in_k = 0;

	while (index_in_l < len && index_in_k < q) {
		int remn = remain[L[index_in_l].originalIndex];
		int rept = lcp[index_in_l];

		if (remn > rept) {
			while (sum + remn - rept >= k[index_in_k]) {
				int size = k[index_in_k] - sum + rept;
				output[old_pos[index_in_k]] = (char *)malloc(size + 1);
				memset(output[old_pos[index_in_k]], 0 , size + 1);
				memcpy(output[old_pos[index_in_k]], &com_str[L[index_in_l].originalIndex], size);
				index_in_k ++;
				if (q == index_in_k) {
					break;
				}
			}

			sum += remn - rept;
		}

		index_in_l ++;
	}

	while (index_in_k < q) {
		output[old_pos[index_in_k]] = (char *)malloc(8);
		memset(output[old_pos[index_in_k]], 0 , 8);
		memcpy(output[old_pos[index_in_k]], "INVALID", 7);
		index_in_k ++;
	}

	return;
}

int main() {
#if DEBUG
    FILE * fp = fopen("input.txt", "r");
    fscanf(fp, "%d", &n);
	FILE * fp_out = fopen("output.txt", "w");
#else
    scanf("%d", &n);
#endif

	first_char = 'a';
	int index_in_str = 0;
	char w[2001];
	for (int i = 0; i < n; i ++) {
		memset(w, 0, 2001);
#if DEBUG
		fscanf(fp, "%s", w);
#else
		scanf("%s", w);
#endif
		int len = strlen(w);
		for (int j = 0; j < len; j ++) {
			com_str[index_in_str] = w[j];
			remain[index_in_str] = len - j;
			index_in_str ++;
		}

		com_str[index_in_str] = --first_char;
		remain[index_in_str] = 0;
		index_in_str ++;
	}

	int q;
#if DEBUG
    fscanf(fp, "%d", &q);
#else
    scanf("%d", &q);
#endif

	int old_k[500];
	for (int i = 0; i < q; i ++) {
#if DEBUG
		fscanf(fp, "%d", &old_k[i]);
#else
		scanf("%d", &old_k[i]);
#endif
	}

	insert_sort(old_k, q);

	findStrings(com_str, q);

	for (int i = 0; i < q; i ++) {
#if DEBUG
		fputs(output[i], fp_out);
		fputs("\n", fp_out);
#else
		printf("%s\n", output[i]);
#endif
	}

#if DEBUG
    fclose(fp);
    fclose(fp_out);
#endif

    return 0;
}
