#include <bits/stdc++.h>
using namespace std;

const int N = 1e6;

int n;
char s[N + 1];
int z[N];

void zArray()
{
	z[0] = n;
	for (int i = 1, l = 0, r = 1; i < n; i++)
	{
		if (i < r)
			z[i] = min(z[i - l], r - i);
		while (i + z[i] < n && s[z[i]] == s[i + z[i]])
			z[i]++;
		if (i + z[i] > r)
			l = i, r = i + z[i];
	}
}

int main()
{
	scanf("%d", &n);
	scanf("%s", s);

	zArray();

	long long p = 0;
	stack<int> s;
	s.push(0);
	for (int k = 1; k <= n; k++)
	{
		s.push(k - 1);
		while (z[s.top()] + s.top() < k)
			s.pop();
		p += s.top();
	}
	printf("%lld\n", p);
}
