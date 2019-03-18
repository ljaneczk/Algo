/*
Author - Łukasz Janeczko AGH Kraków
Only for private and educational use.
Documentation: http://www.cplusplus.com/reference/set/set/
Input:
    n - number of integers
    a1, a2, ... , an - n integers
    q - number of queries
    b1, b2, ... , bq - n integers
Working:
   Program inserts numbers a1, a2, ... , an into set<int> S
   Then prints S size
   Then prints numbers from S in
        - increasing order
        - decreasing order
   Then prints minimum and maximum value in S
   Then for each number bi in {b1, b2, ... , bq} prints
        - "YES", if bi is in S, "NO" otherwise
        - result of count of equal elements in S
        - lower_bound of bi in S
        - upper_bound of bi in S
   Then performs some other described operations
*/

#include <iostream>
#include <set>
#include <vector>

using namespace std;        // Just for typing cin, cout, set instead of std::cin, std::cout, std::set

int main()
{
    size_t n, q;
    cin >> n;
    vector <int> A(n);
    for (int i = 0; i < n; i++)
        cin >> A[i];
    cin >> q;
    vector <int> B(q);
    for (int i = 0; i < q; i++)
        cin >> B[i];

    cout <<endl;

    set <int> S;            // Set of ints

    for (int a : A)
        S.insert(a);        // Inserts a into S

    cout << "Size of set <int> S: " << S.size() <<endl;
    cout <<endl;

    cout << "Set <int> S in increasing order: " <<endl;
    for (auto v : S)
        cout << v << " ";
    cout <<endl <<endl;

    cout << "Set <int> S in increasing order with iterators: " <<endl;
    for (set<int>::iterator it = S.begin(); it != S.end(); it++)
        cout << *(it) << " ";                                       // * on iterator returns value pointed by iterator
    cout <<endl <<endl;

    /* IT IS INCORRECT - BE CAREFUL! ;)
    cout << "Set <int> S in decreasing order with iterators: " <<endl;
    for (set<int>::iterator it = S.end(); it != S.begin(); it--)
        cout << *(it) << " ";
    cout <<endl;
    */

    cout << "Set <int> S in decreasing order with reverse iterators: " <<endl;
    for (set<int>::reverse_iterator it = S.rbegin(); it != S.rend(); it++)
        cout << *(it) << " ";                                       // * on reverse_iterator returns value pointed by iterator
    cout <<endl <<endl;

    cout << "Set <int> S minimum and maximum with iterators: " <<endl;
    cout << "Minimum in S: " << *(S.begin()) << ", maximum in S: " << *(S.rbegin()) <<endl <<endl;

    for (int b : B) {
        set<int>::iterator s_find_b_it = S.find(b);     // Returns iterator to b in S, if b is in set, end of set otherwise
        bool is_in_set = (s_find_b_it != S.end());
        cout << "Number b = " << b << ((is_in_set) ? " is " : " is not ") << "in set S" <<endl;
        cout << "Result of S.count(" << b << "): " << S.count(b) <<endl;
        cout << "Value of lower_bound of number b = " << b << " is equal to " << *(S.lower_bound(b)) <<endl;
        cout << "Value of upper_bound of number b = " << b << " is equal to " << *(S.upper_bound(b)) <<endl;
        /* NOTE - IT IS NOT POSSIBLE TO COUNT NUMBER OF LESS VALUES BY SUBTRACTING ITERATORS
        cout << S.lower_bound(b) - S.begin() <<endl;
        */
        cout <<endl;
    }

    set <int> S_copy = S;                               // Copy constructor - copies all elements from S and inserts them to
    cout << "Set <int> S: " <<endl;
    for (auto v : S)
        cout << v << " ";
    cout <<endl;
    cout << "Set <int> S_copy: " <<endl;
    for (auto v : S_copy)
        cout << v << " ";
    cout <<endl;
    cout << "Are S and S_copy equal? " << (S == S_copy) <<endl;
    cout << "Are S and S_copy different? " << (S != S_copy) <<endl;
    cout <<endl;

    cout << "Size of S before clear: " << S.size() <<endl;
    cout << "Is S empty before clear? " << S.empty() <<endl;
    S.clear();                                          // Removes all elements from set
    cout << "Size of S after clear: " << S.size() <<endl;
    cout << "Is S empty after clear? " << S.empty() <<endl;
    cout << "Are S and S_copy equal? " << (S == S_copy) <<endl;
    cout << "Are S and S_copy different? " << (S != S_copy) <<endl;
    cout <<endl;

    size_t index_1 = 4 % n, index_2 = (index_1 + 1) % n;     // Random indices from range [0,n)
    if (A[index_1] > A[index_2])
        swap(index_1, index_2);

    S = S_copy;
    cout << "S before S.erase(val), where val = " << A[index_1] << ": " <<endl;
    for (auto v : S)
        cout << v << " ";
    cout <<endl;
    S.erase(A[index_1]);                                // Removes all elements from set having key equal to val
    cout << "S after S.erase(val), where val = " << A[index_1] << ": " <<endl;
    for (auto v : S)
        cout << v << " ";
    cout <<endl <<endl;

    S = S_copy;
    cout << "S before S.erase(it), where it = S.begin(): " <<endl;
    for (auto v : S)
        cout << v << " ";
    cout <<endl;
    S.erase(S.begin());                                 // Removes first element in set
    cout << "S after S.erase(it), where it = S.begin(): " <<endl;
    for (auto v : S)
        cout << v << " ";
    cout <<endl <<endl;

    S = S_copy;
    cout << "S before S.erase(it), where it = lower_bound of " << A[index_1] << ": " <<endl;
    for (auto v : S)
        cout << v << " ";
    cout <<endl;
    S.erase(S.lower_bound(A[index_1]));                 // Removes element from set pointed by iterator it
    cout << "S after S.erase(it), where it = lower_bound of " << A[index_1] << ": " <<endl;
    for (auto v : S)
        cout << v << " ";
    cout <<endl <<endl;

    S = S_copy;
    cout << "S before S.erase(it1, it2), where it1 = lower_bound of " << A[index_1] << " and it2 = lower_bound of " << A[index_2] << ": " <<endl;
    for (auto v : S)
        cout << v << " ";
    cout <<endl;
    S.erase(S.lower_bound(A[index_1]), S.lower_bound(A[index_2]));          // Removes elements in range [*it1, *it2)
    cout << "S after S.erase(it1, it2), where it1 = lower_bound of " << A[index_1] << " and it2 = lower_bound of " << A[index_2] << ": " <<endl;
    for (auto v : S)
        cout << v << " ";
    cout <<endl <<endl;
    return 0;
}
