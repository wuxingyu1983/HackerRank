#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG       0
#define MAX_LEN     100005

char output[10][2 * MAX_LEN];
int rl[2 * MAX_LEN];
int pallen[2 * MAX_LEN];

struct myTuple {
    int originalIndex;   // stores original index of suffix
    int firstHalf;       // store rank for first half of suffix
    int secondHalf;      // store rank for second half of suffix
    struct myTuple * next;
    struct myTuple * last;
};

struct myTuple round1[2 * MAX_LEN];
struct myTuple round2[2 * MAX_LEN];

void radix_sort(struct myTuple s[], int len) {
    struct myTuple * negative = NULL;
    int buckket_size = len < 27 ? 27 : len;
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

struct myTuple LS[18][2 * MAX_LEN];
struct myTuple L[2 * MAX_LEN];

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

void manacher(char *str, int * out) {
    // # - pre process
    char * tmp = (char *)malloc(2 * strlen(str) + 2);
    memset(tmp, 0, 2 * strlen(str) + 2);

    size_t j = 0;
    for (size_t i = 0; i < strlen(str); i++) {
        tmp[j++] = '#';
        tmp[j++] = str[i];
    }
    tmp[j] = '#';

    memset(rl, 0, sizeof(rl));

    int max_right = 0, pos = 0;
    int len_tmp = strlen(tmp);
    for (int i = 0; i < len_tmp; i++) {
        if (i < max_right) {
            rl[i] = rl[2 * pos - 1] > (max_right - 1) ? (max_right - 1) : rl[2 * pos - 1];
        }
        else {
            rl[i] = 1;
        }

        while (i - rl[i] >= 0 && i + rl[i] < len_tmp && tmp[i - rl[i]] == tmp[i + rl[i]]) {
            rl[i] ++;
        }

        if (i + rl[i] - 1 > max_right) {
            max_right = i + rl[i] - 1;
            pos = i;
        }
    }
/*
	for (size_t i = 0; i < strlen(str); i++) {
		out[i] = 1;
	}
*/
    for (size_t i = 0; i < len_tmp; i ++) {
        pallen[i] = 1;
    }

    for (size_t i = 0; i < len_tmp; i ++) {
        int left = i - rl[i] + 1;   // must # position
        int len = rl[i] * 2 - 1;

        if (1 < len) {
            if (len > pallen[left]) {
                pallen[left] = len;
            }

			int index = left + 1;
			len = (len - 1) / 2;
			while (index < i) {
				if (len > pallen[index]) {
					pallen[index] = len;
				}

				len -= 2;
				index += 2;
			}
        }
    }

    for (size_t i = 1, j = 0; i < len_tmp; i = i + 2, j ++) {
        out[j] = pallen[i];
    }

	free(tmp);
}

// p_a[i] : from a[i] max length palindrome lengths
int p_a[MAX_LEN], p_b[MAX_LEN];

char tmp_out[2 * MAX_LEN];

void build_priv(char * com_str, int len_a, int len_b, char *out) {
	// get lcp for com_str
	int len = strlen(com_str);
	int * suffixRank[18];
	for (int i = 0; i < 18; i ++) {
		suffixRank[i] = (int *)malloc(len * sizeof(int));
	}

	for(int i = 0; i < len; ++i) {
		suffixRank[0][i] = com_str[i] - 'a';
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
		radix_sort(L, len);
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

	// L 数组就是排序后的
	stp --;
	int * lcp = (int *)malloc(len * sizeof(int));
	lcp[0] = 0;
	for (int i = 1; i < len; i++){
		lcp[i] = getLcp(L[i - 1].originalIndex, L[i].originalIndex, stp, len);
	}

	// get pos
	int * pos = (int *)malloc(len * sizeof(int));
	for (int i = 0; i < len; i ++) {
		pos[L[i].originalIndex] = i;
	}

	for (int i = 0; i < len_a; i ++) {
		int after_i = i + p_a[i];
		if (after_i < len_a) {
			int pos_in_lcp = pos[after_i];
			int tmp = lcp[pos_in_lcp];
			int pos_in_b = -1;
			int min = 0;
			while (0 < lcp[pos_in_lcp]) {
				// go left
				if (L[pos_in_lcp - 1].originalIndex > len_a) {
					min = tmp;
					pos_in_b = L[pos_in_lcp - 1].originalIndex;
					break;
				}
				else {
					if (tmp > lcp[pos_in_lcp - 1]) {
						tmp = lcp[pos_in_lcp - 1];
					}
				}

				pos_in_lcp --;
			}

			if (0 <= pos_in_b) {
				int j = 0;
				for (int com_i = 0; com_i < min; com_i ++) {
					tmp_out[j ++] = com_str[pos_in_b + min - 1 - com_i];
				}

				for (int com_i = 0; com_i < p_a[i]; com_i ++) {
					tmp_out[j ++] = com_str[i + com_i];
				}

				for (int com_i = 0; com_i < min; com_i ++) {
					tmp_out[j ++] = com_str[pos_in_b + com_i];
				}

				tmp_out[j] = 0;

				if (0 == strlen(out) || strlen(tmp_out) > strlen(out) || (strlen(tmp_out) == strlen(out) && 0 > strcmp(tmp_out, out))) {
					out[0] = 0;
					strcpy(out, tmp_out);
				}
			}

			pos_in_lcp = pos[after_i];
			pos_in_lcp ++;
			tmp = MAX_LEN;
			min = 0;
			pos_in_b = -1;
			while(0 < lcp[pos_in_lcp]) {
				if (L[pos_in_lcp].originalIndex > len_a) {
					min = tmp > lcp[pos_in_lcp] ? lcp[pos_in_lcp] : tmp;
					pos_in_b = L[pos_in_lcp].originalIndex;
					break;
				}
				else {
					if (tmp > lcp[pos_in_lcp]) {
						tmp = lcp[pos_in_lcp];
					}
				}

				pos_in_lcp ++;
			}

			if (0 <= pos_in_b) {
				int j = 0;
				for (int com_i = 0; com_i < min; com_i ++) {
					tmp_out[j ++] = com_str[pos_in_b + min - 1 - com_i];
				}

				for (int com_i = 0; com_i < p_a[i]; com_i ++) {
					tmp_out[j ++] = com_str[i + com_i];
				}

				for (int com_i = 0; com_i < min; com_i ++) {
					tmp_out[j ++] = com_str[pos_in_b + com_i];
				}

				tmp_out[j] = 0;

				if (0 == strlen(out) || strlen(tmp_out) > strlen(out) || (strlen(tmp_out) == strlen(out) && 0 > strcmp(tmp_out, out))) {
					out[0] = 0;
					strcpy(out, tmp_out);
				}
			}
		}
	}
}

void build(char *a, char *b, char *out) {
    char * rev_a = (char *)malloc(strlen(a) + 1);
    char * rev_b = (char *)malloc(strlen(b) + 1);

    // reverse a[]
    int len_a = strlen(a);
    for (size_t i = 0; i < len_a; i++) {
        rev_a[i] = a[len_a - 1 - i];
    }
    rev_a[len_a] = 0;

    // reverse b[]
    int len_b = strlen(b);
    for (size_t i = 0; i < len_b; i++) {
        rev_b[i] = b[len_b - 1 - i];
    }
    rev_b[len_b] = 0;

    // step 1 : get reversed a palindrome array, get reversed a + b lcp
    {
        memset(p_a, 0, sizeof(p_a));
        manacher(rev_a, p_a);

        char * com_str = (char *)malloc(len_a + len_b + 1 + 1);
        for (size_t i = 0; i < len_a; i++) {
            com_str[i] = rev_a[i];
        }
		com_str[len_a] = '{';

        for (size_t i = 0; i < len_b; i++) {
            com_str[len_a + 1 + i] = b[i];
        }
        com_str[len_a + len_b + 1] = 0;

        build_priv(com_str, len_a, len_b, out);

        free(com_str);
    }

	{
		memset(p_a, 0, sizeof(p_a));
		manacher(b, p_a);

		char * com_str = (char *)malloc(len_a + len_b + 1 + 1);
        for (size_t i = 0; i < len_b; i++) {
            com_str[i] = b[i];
        }
		com_str[len_b] = '{';

        for (size_t i = 0; i < len_a; i++) {
            com_str[len_b + 1 + i] = rev_a[i];
        }
        com_str[len_a + len_b + 1] = 0;

        build_priv(com_str, len_b, len_a, out);

        free(com_str);
	}

    free(rev_a);
    free(rev_b);
}

int main() {
    int q;

#if DEBUG
    FILE * fp = fopen("input.txt", "r");
    FILE * fp_out = fopen("output.txt", "w");
    fscanf(fp,"%d",&q);
#else
    scanf("%d",&q);
#endif

    char a[MAX_LEN];
    char b[MAX_LEN];
    for (size_t i = 0; i < q; i++) {
        memset(a, 0, MAX_LEN);
        memset(b, 0, MAX_LEN);

#if DEBUG
        fscanf(fp,"%s",a);
        fscanf(fp,"%s",b);
#else
        scanf("%s",a);
        scanf("%s",b);
#endif

        build(a, b, output[i]);
    }

    for (size_t i = 0; i < q; i++) {
        if (0 == strlen(output[i])) {
#if DEBUG
            fprintf(fp_out, "-1\n");
#else
            printf("-1\n");
#endif
        }
        else {
#if DEBUG
            fprintf(fp_out, "%s\n", output[i]);
#else
            printf("%s\n", output[i]);
#endif
        }
    }

#if DEBUG
    fclose(fp);
    fclose(fp_out);
#endif

	system("pause");

    return 0;
}
