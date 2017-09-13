#include <queue>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>

using namespace std;

#define DEBUG       0

#define MAX_T       100
#define MAX_2       801
#define MAX_S       100001

int cnt[MAX_T];

// Max number of states in the matching machine.
// Should be equal to the sum of the length of all keywords.
//const int MAXS = 2000000;
int maxs;

vector<string> str_two(MAX_2);

// Maximum number of characters in input alphabet
const int MAXC = 10;

const int MAXM = 512;
const int ONE_MB = 1000000;

struct output {
    int value;
    struct output * next;
};

// OUTPUT FUNCTION IS IMPLEMENTED USING out[]
// Bit i in this mask is one if the word with index i
// appears when the machine enters this state.
//vector<int> out[MAXS];
struct output * * out;
struct output * * last;
struct output * mem[MAXM];

// FAILURE FUNCTION IS IMPLEMENTED USING f[]
int * f;

// GOTO FUNCTION (OR TRIE) IS IMPLEMENTED USING g[][]
//int g[MAXS][MAXC];
int * * g;

int index_in_mem = 0;
int index_in_1mb = 0;

struct output * getOneOutput() {
    struct output * ret = NULL;

    if (ONE_MB == index_in_1mb) {
        index_in_mem ++;
    }

    if (MAXM > index_in_mem)  {
        if (NULL == mem[index_in_mem]) {
            mem[index_in_mem] = (struct output *)malloc(ONE_MB * sizeof(struct output));
            index_in_1mb = 0;
        }

        ret = &mem[index_in_mem][index_in_1mb];
        ret->value = 0;
        ret->next = 0;
        index_in_1mb ++;
    }

    return ret;
}

//void addToOutput(struct output * * l, int value) {
void addToOutput(int index, int value) {
	struct output * tmp = getOneOutput();
	tmp->value = value;
	if (NULL == out[index]) {
		out[index] = tmp;
	}
	else {
		last[index]->next = tmp;
	}
	last[index] = tmp;
}

void mergeOutput(struct output * * l_a, struct output * * l_b) {
    if (*l_b) {
        struct output * p_a = * l_a;
        struct output * pp_a = NULL;
        struct output * p_b = * l_b;

        if (NULL == (*l_a)) {
            *l_a = getOneOutput();
            (*l_a)->value = p_b->value;

            p_a = *l_a;
            p_b = p_b->next;
        }

        while (p_a && p_b) {
            if (p_b->value == p_a->value) {
                p_a = p_a->next;
                p_b = p_b->next;
                if (pp_a) {
                    pp_a = pp_a->next;
                }
                else {
                    pp_a = *l_a;
                }
            }
            else if (p_b->value < p_a->value) {
                struct output * tmp = getOneOutput();
                tmp->value = p_b->value;
                tmp->next = p_a;

                if (pp_a) {
                    pp_a->next = tmp;
                }
                else {
                    * l_a = tmp;
                }
                pp_a = tmp;
                p_b = p_b->next;
            }
            else {
                p_a = p_a->next;
                if (pp_a) {
                    pp_a = pp_a->next;
                }
                else {
                    pp_a = *l_a;
                }

            }
        }

        while (p_b){
            struct output * tmp = getOneOutput();
            tmp->value = p_b->value;

            pp_a->next = tmp;
            pp_a = tmp;

            p_b = p_b->next;
        }
    }
}

// Builds the string matching machine.
// arr -   array of words. The index of each keyword is important:
//         "out[state] & (1 << i)" is > 0 if we just found word[i]
//         in the text.
// Returns the number of states that the built machine has.
// States are numbered 0 up to the return value - 1, inclusive.
int buildMatchingMachine(vector<string>& arr, int k)
{
    // Initialize all values in output function as 0.
    //    memset(out, 0, sizeof out);

    // Initially, we just have the 0 state
    int states = 1;

    // Construct values for goto function, i.e., fill g[][]
    // This is same as building a Trie for arr[]
    for (int i = 0; i < k; ++i)
    {
        const string &word = arr[i];
        int currentState = 0;

        // Insert all characters of current word in arr[]
        for (int j = 0; j < word.size(); ++j)
        {
            int ch = word[j] - '0';

            // Allocate a new node (create a new state) if a
            // node for ch doesn't exist.
            if (g[currentState][ch] == -1)
            g[currentState][ch] = states++;

            currentState = g[currentState][ch];
        }

        // Add current word in output function
        //        out[currentState] |= (1 << i);
//        addToOutput(&out[currentState], i);
        addToOutput(currentState, i);
    }

    // For all characters which don't have an edge from
    // root (or state 0) in Trie, add a goto edge to state
    // 0 itself
    for (int ch = 0; ch < MAXC; ++ch)
    if (g[0][ch] == -1)
    g[0][ch] = 0;

    // Now, let's build the failure function

    // Failure function is computed in breadth first order
    // using a queue
    queue<int> q;

    // Iterate over every possible input
    for (int ch = 0; ch < MAXC; ++ch)
    {
        // All nodes of depth 1 have failure function value
        // as 0. For example, in above diagram we move to 0
        // from states 1 and 3.
        if (g[0][ch] != 0)
        {
            f[g[0][ch]] = 0;
            q.push(g[0][ch]);
        }
    }

    // Now queue has states 1 and 3
    while (q.size())
    {
        // Remove the front state from queue
        int state = q.front();
        q.pop();

        // For the removed state, find failure function for
        // all those characters for which goto function is
        // not defined.
        for (int ch = 0; ch < MAXC; ++ch)
        {
            // If goto function is defined for character 'ch'
            // and 'state'
            if (g[state][ch] != -1)
            {
                // Find failure state of removed state
                int failure = f[state];

                // Find the deepest node labeled by proper
                // suffix of string from root to current
                // state.
                while (g[failure][ch] == -1)
                failure = f[failure];

                failure = g[failure][ch];
                f[g[state][ch]] = failure;

                // Merge output values
                mergeOutput(&out[g[state][ch]], &out[failure]);
                //                out[g[state][ch]] |= out[failure];

                // Insert the next level node (of Trie) in Queue
                q.push(g[state][ch]);
            }
        }
    }

    return states;
}

// Returns the next state the machine will transition to using goto
// and failure functions.
// currentState - The current state of the machine. Must be between
//                0 and the Nnumber of states - 1, inclusive.
// nextInput - The next character that enters into the machine.
int findNextState(int currentState, char nextInput)
{
    int answer = currentState;
    int ch = nextInput - '0';

    // If goto is not defined, use failure function
    while (g[answer][ch] == -1)
    answer = f[answer];

    return g[answer][ch];
}


void init() {
    for (size_t i = 0; i < MAX_2; i++) {
        if (0 == i) {
            str_two[i] = '1';
        }
        else {
            int carry = 0;
            int val = 0;
            for (size_t j = 0; j < str_two[i - 1].length(); j++) {
                val = (str_two[i - 1][j] - '0') * 2 + carry;
                if (9 < val) {
                    str_two[i] += '0' + val - 10;
                    carry = 1;
                }
                else {
                    str_two[i] += '0' + val;
                    carry = 0;
                }
            }

            if (0 < carry) {
                str_two[i] += '1';
            }
        }
        maxs += str_two[i].length();
    }

    // buildMatchingMachine
    f = (int *)malloc(maxs * sizeof(int));
    memset(f, -1, sizeof(maxs * sizeof(int)));

    g = (int * *)malloc(maxs * sizeof(int *));
    for (size_t i = 0; i < maxs; i++) {
        g[i] = (int *)malloc(MAXC * sizeof(int));
        memset(g[i], -1, MAXC * sizeof(int));
    }

    out = (struct output * *)malloc(maxs * sizeof(struct output *));
    memset(out, 0 , maxs * sizeof(struct output *));

    last = (struct output * *)malloc(maxs * sizeof(struct output *));
    memset(last, 0 , maxs * sizeof(struct output *));

    buildMatchingMachine(str_two, MAX_2);
}

int two_two(string& s) {
    int ret = 0;

    // reverse
    reverse(s.begin(), s.end());

    // Initialize current state
    int currentState = 0;

    // Traverse the text through the nuilt machine to find
    // all occurrences of words in arr[]
    for (int i = 0; i < s.size(); ++i)
	{
		currentState = findNextState(currentState, s[i]);

		// Match found, print all matching words of arr[]
		// using output function.
		struct output * p = out[currentState];

		while (p) {
			ret ++;
			p = p->next;
		}
	}

    return ret;
}

int main() {
    int t;

#if DEBUG
    ifstream fin("input.txt");
    if (!fin.is_open()) {
        printf("open file error!\n");
        return -1;
    }
    fin >> t;
#else
    cin >> t;
#endif

    init();

    string s;
    for (size_t i = 0; i < t; i++) {
#if DEBUG
        fin >> s;
#else
        cin >> s;
#endif
        cnt[i] = two_two(s);
    }

    for (size_t i = 0; i < t; i++) {
        cout << cnt[i] << "\n";
    }

    return 0;
}
