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
   Program inserts numbers a1, a2, ... , an into set<int> MS
   Then prints MS size
   Then prints numbers from MS in
        - increasing order
        - decreasing order
   Then prints minimum and maximum value in MS
   Then for each number bi in {b1, b2, ... , bq} prints
        - "YES", if bi is in MS, "NO" otherwise
        - lower_bound of bi in MS
        - upper_bound of bi in MS
*/

#include <iostream>
#include <set>
#include <vector>

using namespace std;        // Just for typing cin, cout, set instead of std::cin, std::cout, std::set

int main()
{
    uint32_t n, q;
    cin >> n;
    vector <int> A(n);
    for (int i = 0; i < n; i++)
        cin >> A[i];
    cin >> q;
    vector <int> B(q);
    for (int i = 0; i < q; i++)
        cin >> B[i];

    cout <<endl;

    multiset <int> MS;            // Multiset of ints

    for (int a : A)
        MS.insert(a);        // Inserts a into MS

    cout << "Size of set <int> MS: " << MS.size() <<endl;
    cout <<endl;

    cout << "Multiset <int> MS in increasing order: " <<endl;
    for (auto v : MS)
        cout << v << " ";
    cout <<endl <<endl;

    cout << "Multiset <int> MS in increasing order with iterators: " <<endl;
    for (set<int>::iterator it = MS.begin(); it != MS.end(); it++)
        cout << *(it) << " ";                                       // * on iterator returns value pointed by iterator
    cout <<endl <<endl;

    /* IT IS INCORRECT - BE CAREFUL! ;)
    cout << "Multiset <int> MS in decreasing order with iterators: " <<endl;
    for (set<int>::iterator it = MS.end(); it != MS.begin(); it--)
        cout << *(it) << " ";
    cout <<endl;
    */

    cout << "Multiset <int> MS in decreasing order with reverse iterators: " <<endl;
    for (set<int>::reverse_iterator it = MS.rbegin(); it != MS.rend(); it++)
        cout << *(it) << " ";                                       // * on reverse_iterator returns value pointed by iterator
    cout <<endl <<endl;

    cout << "Multiset <int> MS minimum and maximum with iterators: " <<endl;
    cout << "Minimum in MS: " << *(MS.begin()) << ", maximum in MS: " << *(MS.rbegin()) <<endl <<endl;

    for (int b : B) {
        set<int>::iterator s_find_b_it = MS.find(b);     // Returns iterator to b in MS, if b is in set, end of set otherwise
        bool is_in_set = (s_find_b_it != MS.end());
        cout << "Number b = " << b << ((is_in_set) ? " is " : " is not ") << "in set MS" <<endl;
        cout << "Result of MS.count(" << b << "): " << MS.count(b) <<endl;
        cout << "Value of lower_bound of number b = " << b << " is equal to " << *(MS.lower_bound(b)) <<endl;
        cout << "Value of upper_bound of number b = " << b << " is equal to " << *(MS.upper_bound(b)) <<endl;
        /* NOTE - IT IS NOT POSSIBLE TO COUNT NUMBER OF LESS VALUES BY MSUBTRACTING ITERATORS
        cout << MS.lower_bound(b) - MS.begin() <<endl;
        */
        cout <<endl;
    }

    multiset <int> MS_copy = MS;                               // Copy constructor - copies all elements from MS and inserts them to
    cout << "Multiset <int> MS: " <<endl;
    for (auto v : MS)
        cout << v << " ";
    cout <<endl;
    cout << "Multiset <int> MS_copy: " <<endl;
    for (auto v : MS_copy)
        cout << v << " ";
    cout <<endl;
    cout << "Are MS and MS_copy equal? " << (MS == MS_copy) <<endl;
    cout << "Are MS and MS_copy different? " << (MS != MS_copy) <<endl;
    cout <<endl;

    cout << "Size of MS before clear: " << MS.size() <<endl;
    cout << "Is MS empty before clear? " << MS.empty() <<endl;
    MS.clear();                                          // Removes all elements from set
    cout << "Size of MS after clear: " << MS.size() <<endl;
    cout << "Is MS empty after clear? " << MS.empty() <<endl;
    cout << "Are MS and MS_copy equal? " << (MS == MS_copy) <<endl;
    cout << "Are MS and MS_copy different? " << (MS != MS_copy) <<endl;
    cout <<endl;

    size_t index_1 = 4 % n, index_2 = (index_1 + 1) % n;     // Random indices from range [0,n)
    if (A[index_1] > A[index_2])
        swap(index_1, index_2);

    MS = MS_copy;
    cout << "S before MS.erase(val), where val = " << A[index_1] << ": " <<endl;
    for (auto v : MS)
        cout << v << " ";
    cout <<endl;
    MS.erase(A[index_1]);                                // Removes all elements from set having key equal to val
    cout << "S after MS.erase(val), where val = " << A[index_1] << ": " <<endl;
    for (auto v : MS)
        cout << v << " ";
    cout <<endl <<endl;

    MS = MS_copy;
    cout << "S before MS.erase(it), where it = MS.begin(): " <<endl;
    for (auto v : MS)
        cout << v << " ";
    cout <<endl;
    MS.erase(MS.begin());                                 // Removes first element in set
    cout << "S after MS.erase(it), where it = MS.begin(): " <<endl;
    for (auto v : MS)
        cout << v << " ";
    cout <<endl <<endl;

    MS = MS_copy;
    cout << "S before MS.erase(it), where it = lower_bound of " << A[index_1] << ": " <<endl;
    for (auto v : MS)
        cout << v << " ";
    cout <<endl;
    MS.erase(MS.lower_bound(A[index_1]));                 // Removes element from set pointed by iterator it
    cout << "S after MS.erase(it), where it = lower_bound of " << A[index_1] << ": " <<endl;
    for (auto v : MS)
        cout << v << " ";
    cout <<endl <<endl;

    MS = MS_copy;
    cout << "S before MS.erase(it1, it2), where it1 = lower_bound of " << A[index_1] << " and it2 = lower_bound of " << A[index_2] << ": " <<endl;
    for (auto v : MS)
        cout << v << " ";
    cout <<endl;
    MS.erase(MS.lower_bound(A[index_1]), MS.lower_bound(A[index_2]));          // Removes elements in range [*it1, *it2)
    cout << "S after MS.erase(it1, it2), where it1 = lower_bound of " << A[index_1] << " and it2 = lower_bound of " << A[index_2] << ": " <<endl;
    for (auto v : MS)
        cout << v << " ";
    cout <<endl <<endl;
    return 0;
}
