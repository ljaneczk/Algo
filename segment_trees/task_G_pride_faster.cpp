/*
Author - Łukasz Janeczko AGH Kraków
Only for private and educational use, otherwise needed author's permission.
This program reads n and n positive integer numbers (array A)
and prints minimal number of steps to change array A into array consisting of n ones.
During one step two adjacent numbers from A (i.e. A[i], A[i+1]) can be chosen and exactly of them can be changed into gcd(A[i], A[i+1]).
Complexity O(n * logn * log(MAX)), where MAX = max(A[i], i <- (0,n-1))
*/

#include <bits/stdc++.h>
using namespace std;

struct tree {
	int val = 0;					//Wpisane jest 0, ponieważ gcd(a, 0) = 0 dla każdego a
};

int gcd(int a, int b)
{
	return (b == 0) ? a : gcd(b, a % b);
}

void init(int b, int e, tree Tree[])
{
	if (e - b > 1) {				//Gdy przedział nie jest jednoelementowy
		init(b, (b+e)/2, Tree);
		init((b+e)/2, e, Tree);
		Tree[b+e].val = gcd(Tree[b+(b+e)/2].val, Tree[(b+e)/2+e].val);
	}
}

void update(int l, int r, int b, int e, int m, tree Tree[])
{
	if (r <= b || e <= l)			//Zadany przedział [l,r) i badny [b,e) są rozłączne
		{ }
	else
	if (l <= b && e <= r)			//Badany przedział [b,e) zawiera się w całości w [l,r)
		Tree[b+e].val = m;
	else {							//Przedziały zadany [l,r) i badany [b,e) przecinają się
		update(l, r, b, (b+e)/2, m, Tree);
		update(l, r, (b+e)/2, e, m, Tree);
		Tree[b+e].val = gcd(Tree[b+(b+e)/2].val, Tree[(b+e)/2+e].val);
	}
}

int query(int l, int r, int b, int e, tree Tree[])
{
	if (r <= b || e <= l)			//Zadany przedział [l,r) i badny [b,e) są rozłączne
		return 0;
	else
	if (l <= b && e <= r)			//Badany przedział [b,e) zawiera się w całości w [l,r)
		return Tree[b+e].val;
	else 							//Przedziały zadany [l,r) i badany [b,e) przecinają się
		return gcd(query(l, r, b, (b+e)/2, Tree), query(l, r, (b+e)/2, e, Tree));
}

int main()
{
	ios_base::sync_with_stdio(false);
	int n, s = 1, number_of_ones = 0;	//s - rozmiar drzewa, n - rozmiar tablicy A
	cin >> n;
	while (s < 2 * n)
		s *= 2;
	int A[n]; tree Tree[s];

	for (int i = 0; i < n; i++) {
		cin >> A[i];				//Do A wczytujemy liczby z wejścia zadania, liczby są dodatnie
		Tree[2*i+1].val = A[i];		//Przedział [i, i+1) zapisany jest w komórce drzewa pod indeksem 2*i+1
		if (A[i] == 1)
			number_of_ones++;
	}

	init(0, s/2, Tree);				//Inicjalizacja drzewa po wpisaniu wartości na najniższym poziomie
	if (query(0, s/2, 0, s/2, Tree) != 1) {
		cout << "-1\n";
		return 0;
	}
	if (number_of_ones > 0) {
		cout << n - number_of_ones << "\n";
		return 0;
	}

	int min_steps_to_one = n, current_end = 0, current_gcd;
	for (int i = 0; i < n; i++) {
		if (current_end < i)
			current_end++;
		current_gcd = query(i, current_end+1, 0, s/2, Tree);
		while (current_gcd > 1 && current_end < n) {
			current_end++;
			current_gcd = gcd(current_gcd, A[current_end]);
		}
		if (current_gcd == 1)
			min_steps_to_one = min(min_steps_to_one, current_end - i);
	}

	cout << min_steps_to_one + n - 1 << "\n";
	return 0;
}
