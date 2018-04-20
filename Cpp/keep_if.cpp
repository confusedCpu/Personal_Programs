#include <algorithm>
#include <deque>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

template <typename F, typename T>
//vector<T> keep_if( F func, const vector<T>& org )
T keep_if( F func, const T& org )
{
    T keeping;
    for( auto i : org )
    {
        if( func( i ))
        {
            keeping.emplace_back( i );
        }    
    }
    return keeping;
}

bool is_even(int x)
{
    return x % 2 == 0;
}

bool is_odd(int x)
{
    return x % 2 != 0;
}

void show( auto struc )
{
    for( auto i : struc )
        cout << i << " ";
    cout << endl;
}

int main()
{
    vector<int> org{ 1,2,3,4,5,6,7,8,9,0 };

    auto even = keep_if( is_even, org );
    auto odd = keep_if( is_odd, org );

    cout << "Original: ";
    show( org );

    cout << "Even: ";
    show( even );

    cout << "Odd: ";
    show( odd );

    cout << "\nLists now" << endl;

    list<int> org2{ 0,9,8,7,6,5,4,3,2,1 };
    
    auto even2 = keep_if( is_even, org2 );
    auto odd2 = keep_if( is_odd, org2 );
    
    cout << "Org2: "; 
    show( org2 );

    cout << "Eorg2: ";
    show( even2 );

    cout << "Oorg2: "; 
    show( odd2 );


    deque<int> dq  = { 12, 21, 13, 25, 89, 90, 15 };

    cout << "Deque\ndq: ";
    show( dq );

    auto even3 = keep_if( is_even, dq );
    auto odd3 = keep_if( is_odd, dq );

    cout << "even3: ";
    show( even3 );

    
    cout << "odd3: ";
    show( odd3 );

    
}
