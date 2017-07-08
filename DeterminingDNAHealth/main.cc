// C++ program for implementation of Aho Corasick algorithm
// for string matching
#include <queue>
#include <vector>
#include <list>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <time.h>
//#include <malloc.h>

#define DEBUG       1

using namespace std;

// Max number of states in the matching machine.
// Should be equal to the sum of the length of all keywords.
//const int MAXS = 2000000;
int maxs;

// Maximum number of characters in input alphabet
const int MAXC = 26;

// OUTPUT FUNCTION IS IMPLEMENTED USING out[]
// Bit i in this mask is one if the word with index i
// appears when the machine enters this state.
//vector<int> out[MAXS];
list<int> * out;

// FAILURE FUNCTION IS IMPLEMENTED USING f[]
int * f;

// GOTO FUNCTION (OR TRIE) IS IMPLEMENTED USING g[][]
//int g[MAXS][MAXC];
int * * g;

int cnt_add = 0, cnt_merge = 0;

void addToVector(list<int> &vec, int value) {
/*
    if (0 < vec.size()) {
        list<int>::iterator it = vec.begin();

        while (it != vec.end()) {
            if (*it == value) {
                return;
            }
            else {
                if (*it > value) {
                    vec.insert(it, value);
                    return;
                }
            }
            it ++;
        }
    }
*/    
    if (0 == vec.size()) {
        vec.push_back(value);
    }
}

void mergeVector(list<int> &vec_a, list<int> &vec_b) {
    if (0 < vec_b.size()) {
        list<int>::iterator it_b = vec_b.begin();
        if (0 < vec_a.size()) {
            list<int>::iterator it_a = vec_a.begin();

            while (it_a != vec_a.end() && it_b != vec_b.end()) {
                if (*it_a == *it_b) {
                    it_a ++;
                    it_b ++;
                }
                else {
                    if (*it_a < *it_b) {
                        it_a ++;
                    }
                    else {
                        // *it_a > *it_b
                        it_a = vec_a.insert(it_a, *it_b);
                        it_b ++;
                    }
                }
            }
        }
        if (it_b != vec_b.end()) {
            while (it_b != vec_b.end()) {
                vec_a.push_back(*it_b);
                it_b ++;
            }
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
            int ch = word[j] - 'a';

            // Allocate a new node (create a new state) if a
            // node for ch doesn't exist.
            if (g[currentState][ch] == -1)
                g[currentState][ch] = states++;

            currentState = g[currentState][ch];
        }

        // Add current word in output function
        //        out[currentState] |= (1 << i);
        addToVector(out[currentState], i);
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
                mergeVector(out[g[state][ch]], out[failure]);
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
    int ch = nextInput - 'a';

    // If goto is not defined, use failure function
    while (g[answer][ch] == -1)
        answer = f[answer];

    return g[answer][ch];
}

// This function finds all occurrences of all array words
// in text.
unsigned long long searchWords(string text, int start, int end, vector<int>& health)
{
    unsigned long long ret = 0;
    // Preprocess patterns.
    // Build machine with goto, failure and output functions

    // Initialize current state
    int currentState = 0;

    // Traverse the text through the nuilt machine to find
    // all occurrences of words in arr[]
    for (int i = 0; i < text.size(); ++i)
    {
        currentState = findNextState(currentState, text[i]);

        // Match found, print all matching words of arr[]
        // using output function.
        if (0 < out[currentState].size()) {
            int index = 0;
            list<int>::iterator it = out[currentState].begin();

            while (it != out[currentState].end()) {
                if (start > *it) {
                }
                else if (*it <= end) {
                    ret += health[*it];
                }
                else {
                    break;
                }
                index ++;
                it ++;
            }
        }
    }

    return ret;
}

// Driver program to test above
int main()
{
    long long min = -1;
    long long max = 0;

    int n;

#if DEBUG
    ifstream fin("input.txt");
    if (!fin.is_open()) {
        printf("open file error!\n");
        return -1;
    }
    fin >> n;
#else
    cin >> n;
#endif

    maxs = 0;
    vector<string> genes(n);
    for(int genes_i = 0; genes_i < n; genes_i++){
#if DEBUG
        fin >> genes[genes_i];
#else
        cin >> genes[genes_i];
#endif
    maxs += genes[genes_i].length();
    }

    f = (int *)malloc(maxs * sizeof(int));
    memset(f, -1, sizeof(maxs * sizeof(int)));

    g = (int * *)malloc(maxs * sizeof(int *));
    for (size_t i = 0; i < maxs; i++) {
        g[i] = (int *)malloc(MAXC * sizeof(int));
        memset(g[i], -1, MAXC * sizeof(int));
    }

    out = new list<int>[maxs];

    vector<int> health(n);
    for(int health_i = 0; health_i < n; health_i++){
#if DEBUG
        fin >> health[health_i];
#else
        cin >> health[health_i];
#endif
    }

    clock_t start,finish;
    double TheTimes;
#if DEBUG
    start=clock();
#endif
    buildMatchingMachine(genes, n);
#if DEBUG
    finish=clock();
    TheTimes=(double)(finish-start)/CLOCKS_PER_SEC;
    printf("buildMatchingMachine consume %fs\n",TheTimes);
#endif

    int s;

#if DEBUG
    fin >> s;
#else
    cin >> s;
#endif

    for(int a0 = 0; a0 < s; a0++){
        int first;
        int last;
        string d;

#if DEBUG
        fin >> first >> last >> d;
#else
        cin >> first >> last >> d;
#endif
        // your code goes here

#if DEBUG
        start=clock();
#endif
        unsigned long long ret = searchWords(d, first, last, health);
#if DEBUG
        finish=clock();
        TheTimes=(double)(finish-start)/CLOCKS_PER_SEC;
//        printf("%d : searchWords consume %fs\n", a0, TheTimes);
#endif
        if (ret > max) {
            max = ret;
        }

        if (0 > min || ret < min) {
            min = ret;
        }
    }

    printf("%lld %lld\n", min, max);

    return 0;
}
