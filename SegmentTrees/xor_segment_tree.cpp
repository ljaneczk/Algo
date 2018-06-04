/*
Author - Łukasz Janeczko AGH Kraków
Only for private and educational use, otherwise needed author's permission.
This program reads one integer n and n positive integer numbers (array A).
Then program reads one integer q and q operations in the following format:
  1 l r x - change all numbers in [l,r] by xor with x (for each ai in segment [l,r]: ai -> ai xor x) (More about xor https://en.wikipedia.org/wiki/Exclusive_or)
  2 l r - print sum of all numbers in [l,r]
All numbers x and numbers in array A should not exceed MAX_VALUE, then s1 is number of bits in MAX_VALUE (excluding leading zeros)
Sollution uses the fact that each bit can be proceeded indepedently.
For one bit it is enough to implement segment tree (storing numbers equal to either 0 or 1) with operations:
  U l r - change all numbers in [l,r]: ones into zeros and zeros into ones
  Q l r - sum of numbers in [l,r]
Then operations from input are procceded as follows:
  1 l r x:
    for each bit bi in x: if bi == 1 then do U l r on i-th tree, otherwise do nothing
  2 l r:
    ans = 0; for i = 0 to s1-1: ans += (Q l r) on i-th tree * Two_to_power[i]; print ans
Complexity O(s1 * (n + q) * logn).
Original problem - http://codeforces.com/problemset/problem/242/E
*/
#include <bits/stdc++.h>
#define MAX_VALUE 1000000
using namespace std;

struct tree {
    int val = 0, all = 0;		//val - number of ones, all - length of segment
	bool mod = false;			//mod = true / false - ones and zeros are swapped / not swapped
};

void init(int b, int e, vector <tree> &Tree)
{
    if(e-b > 1) {
        init(b, (b+e)/2, Tree);
        init((b+e)/2, e, Tree);
        Tree[b+e].all = Tree[b+(b+e)/2].all + Tree[(b+e)/2+e].all;
        Tree[b+e].val = Tree[b+(b+e)/2].val + Tree[(b+e)/2+e].val;
    }
}

void update(int l, int r, int b, int e, vector <tree> &Tree)		//Change zeros into ones and ones into zeros in [l,r)
{
    if(e <= l || r <= b)
        { }
    else
    if(l <= b && e <= r) {
        Tree[b+e].val = Tree[b+e].all - Tree[b+e].val;
        Tree[b+e].mod = !Tree[b+e].mod;
    }
    else {
        if(Tree[b+e].mod) {
            Tree[b+(b+e)/2].val = Tree[b+(b+e)/2].all - Tree[b+(b+e)/2].val;
            Tree[b+(b+e)/2].mod = ! Tree[b+(b+e)/2].mod;
            Tree[(b+e)/2+e].val = Tree[(b+e)/2+e].all - Tree[(b+e)/2+e].val;
            Tree[(b+e)/2+e].mod = ! Tree[(b+e)/2+e].mod;
            Tree[b+e].mod = false;
        }
        update(l, r, b, (b+e)/2, Tree);
        update(l, r, (b+e)/2, e, Tree);
		Tree[b+e].val = Tree[b+(b+e)/2].val + Tree[(b+e)/2+e].val;
        }
}

int query(int l, int r, int b, int e, vector <tree> &Tree)		//Sum of ones in [l,r)
{
    if(e <= l || r <= b)
        return 0;
    else
    if(l <= b && e <= r)
        return Tree[b+e].val;
    else {
		if(Tree[b+e].mod) {
            Tree[b+(b+e)/2].val = Tree[b+(b+e)/2].all - Tree[b+(b+e)/2].val;
            Tree[b+(b+e)/2].mod = ! Tree[b+(b+e)/2].mod;
            Tree[(b+e)/2+e].val = Tree[(b+e)/2+e].all - Tree[(b+e)/2+e].val;
            Tree[(b+e)/2+e].mod = ! Tree[(b+e)/2+e].mod;
            Tree[b+e].mod = false;
        }
		return query(l, r, b, (b+e)/2, Tree) + query(l, r, (b+e)/2, e, Tree);
	}
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n, q, s = 1, s1 = 1;
    cin >> n;
    while (((1ll)<<s1) <= MAX_VALUE)				//Minimum numbers of bits for numbers
		s1++;
    while(s <= 2 * n)
        s *= 2;
    vector <int> A(n), Two(s1); vector < vector <tree> > Tree(s1, vector <tree> (s));		// s1 segments trees, i-th tree is responsible for proceeding i-th bit in numbers
    for (int i = 0; i < n; i++)
        cin >> A[i];
    for (int j = 0; j < s1; j++) 
		Two[j] = (1 << j);
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < s1; j++) {
            Tree[j][2*i+1].val = (A[i] & Two[j]) ? 1 : 0;
            Tree[j][2*i+1].all = 1;
        }
    }
    for (int j = 0; j < s1; j++) 
		init(0, s/2, Tree[j]);
		
	int t, l, r, x; long long answer;
    cin >> q;
    for(int i = 0; i < q; i++) {
        cin >> t;
        if(t == 1) {
			cin >> l >> r;
			answer = 0;
			for (int j = 0; j < s1; j++)
				answer += (1ll * query(l-1, r, 0, s/2, Tree[j]) * Two[j]);
			cout << answer <<endl;
		}
        else
        if (t == 2) {
			cin >> l >> r >> x;
			for (int j = 0; j < s1; j++)
				if (x & Two[j])
					update(l-1, r, 0, s/2, Tree[j]);
		}
		else {
			cout << "ERROR" <<endl;
		}
    }
    return 0;
}
