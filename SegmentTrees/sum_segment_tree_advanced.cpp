/*
Author - Łukasz Janeczko AGH Kraków
Only for private and educational use, otherwise needed author's permission.
This program reads two integers n, q and n positive integer numbers (array A).
Then program reads q operations in the following format:
U l r v - add v to all numbers in [l,r]
Q l r - print sum of all numbers in [l,r]
Complexity O((n + q) * logn).
*/

#include <bits/stdc++.h>
using namespace std;

struct tree {
	long long val = 0;					//Suma elementów na przedziale, wpisane jest 0, ponieważ a + 0 = a dla każdego a
	long long mod = 0;                  //Modyfikator oznaczający, że wszystkie elementy danego przedziału mają mieć wartość powiększoną o mod
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
		Tree[b+e].val = Tree[b+(b+e)/2].val + Tree[(b+e)/2+e].val;
		Tree[b+e].mod = 0;
	}
}

void update(int l, int r, int b, int e, int m, tree Tree[])
{
	if (r <= b || e <= l)			//Zadany przedział [l,r) i badny [b,e) są rozłączne
		{ }
	else
	if (l <= b && e <= r) {			//Badany przedział [b,e) zawiera się w całości w [l,r)
		Tree[b+e].val += (e-b) * m; //Każdy element jest zwiększony o m, więc suma rośnie o (e-b) * m
		Tree[b+e].mod += m;

    }
	else {							//Przedziały zadany [l,r) i badany [b,e) przecinają się
        if (Tree[b+e].mod != 0) {   //"Spychamy" modyfikator do dzieci
            Tree[b+(b+e)/2].val += (e-b)/2 * Tree[b+e].mod;
            Tree[b+(b+e)/2].mod += Tree[b+e].mod;
            Tree[(b+e)/2+e].val += (e-b)/2 * Tree[b+e].mod;
            Tree[(b+e)/2+e].mod += Tree[b+e].mod;
            Tree[b+e].mod = 0;
        }
		update(l, r, b, (b+e)/2, m, Tree);
		update(l, r, (b+e)/2, e, m, Tree);
		Tree[b+e].val = Tree[b+(b+e)/2].val + Tree[(b+e)/2+e].val;
	}
}

int query(int l, int r, int b, int e, tree Tree[])
{
	if (r <= b || e <= l)			//Zadany przedział [l,r) i badny [b,e) są rozłączne
		return 0;
	else
	if (l <= b && e <= r)			//Badany przedział [b,e) zawiera się w całości w [l,r)
		return Tree[b+e].val;
	else {							//Przedziały zadany [l,r) i badany [b,e) przecinają się
		if (Tree[b+e].mod != 0) {   //"Spychamy" modyfikator do dzieci
            Tree[b+(b+e)/2].val += (e-b)/2 * Tree[b+e].mod;
            Tree[b+(b+e)/2].mod += Tree[b+e].mod;
            Tree[(b+e)/2+e].val += (e-b)/2 * Tree[b+e].mod;
            Tree[(b+e)/2+e].mod += Tree[b+e].mod;
            Tree[b+e].mod = 0;
        }
		return query(l, r, b, (b+e)/2, Tree) + query(l, r, (b+e)/2, e, Tree);
    }
}

int main()
{
	ios_base::sync_with_stdio(false);
	int n, q, s = 1;				//s - rozmiar drzewa, n - rozmiar tablicy A, q - liczba zapytań / operacji
	cin >> n >> q;
	while (s < 2 * n)
		s *= 2;
	int A[n]; tree Tree[s];

	for (int i = 0; i < n; i++) {
		cin >> A[i];				//Do A wczytujemy liczby z wejścia zadania, liczby są dodatnie
		Tree[2*i+1].val = A[i];		//Przedział [i, i+1) zapisany jest w komórce drzewa pod indeksem 2*i+1
	}

	init(0, s/2, Tree);				//Inicjalizacja drzewa po wpisaniu wartości na najniższym poziomie

    char c; int l, r, v;
	for (int h = 0; h < q; h++) {
        cin >> c;
        if (c == 'U') {             //U l r v - zwiększenie każdej wartości na przedziale [l,r] o wartość v
            cin >> l >> r >> v;
            update(l, r + 1, 0, s/2, v, Tree);
        }
        else
        if (c == 'Q') {             //Wypisanie na ekranie sumy liczb na przedziale [l,r]
            cin >> l >> r;
            cout << query(l, r + 1, 0, s/2, Tree) <<endl;
        }
        else {
            cout << "ERROR" <<endl;
        }
	}

	return 0;
}
