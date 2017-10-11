#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct node
{
	int parent;
	int treeSize;
	int depth;
};

void init(node *U, int n)
{
	for (int i = 0; i < n; i++)
	{
		U[i].parent = i;
		U[i].treeSize = 1;
		U[i].depth = 0;
	}
}

void merge(node &a, node &b)
{
	if (a.depth == b.depth)
	{
		a.depth++;
		b.parent = a.parent;
		a.treeSize += b.treeSize;
	}
	else if (a.depth < b.depth)
	{
		a.parent = b.parent;
		b.treeSize += a.treeSize;
	}
	else
	{
		b.parent = a.parent;
		a.treeSize += b.treeSize;
	}
}

int find(node *U, int i)
{
	int j = i;
	while(j != U[j].parent)
		j = U[j].parent;
	return j;
}

int nextLagFib(vector<int> &past, long long k)
{
	int out;
	if (k <= 55)
		out = (100003 - 200003 * k + 300007 * k * k * k) % 1000000;
	else
		out = (past[k - 55] + past[k - 24]) % 1000000;
	past.push_back(out);
	return out;
}

int main()
{
    string prime_minister;
    int p, pm = 0;

    cin >> prime_minister >> p;

    for (size_t i = 0; i < prime_minister.length(); i++) {
        pm = pm * 10 + (prime_minister[i] - '0');
    }

	int size = 1000 * 1000;

	node *U = new node[size];

	init(U, size);

	vector<int> gen;
	gen.reserve(100000000);
	gen.push_back(0);
	int ctr = 1;

	int a;
	int b;

	int calls = 0;

	while (U[find(U, pm)].treeSize < 10000 * p)
	{
		a = nextLagFib(gen, ctr++);
		b = nextLagFib(gen, ctr++);

		if (a != b)
		{
			calls++;
			a = find(U, a);
			b = find(U, b);
			if (a != b)
				merge(U[a], U[b]);
		}
	}

	cout << calls << endl;

	delete [] U;
}
