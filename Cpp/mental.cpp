/**
 * mental.cpp
 * This program prints a random quote that promotes mental health or that I 
 * just like in general. It is intended to be added a shells .*rc file so that 
 * it can run whenever a new shell is opened. The quotes are retrieved from a 
 * text file in your home directory called ".quotes" and the format of the 
 * quotes is seen bellow.
 *
 * Syntax: Name - "Quote"
 */

#include <fstream>
#include <iostream>
#include <random>
#include <string>

using namespace std;

int main()
{
    const string path = ".quotes";
    ifstream file;
    file.open( path );
    vector<string> qVec;
    string quote;

    if( !file )
    {
        cout << "There was an issue opening the '.quotes' file. Verify its "
             << "validity/prescence" << endl;
        return -1;
    }

    while( getline( file, quote  ) )
        qVec.push_back( quote );

    file.close();

    srand( time( NULL ) );
    int random = ( rand() % qVec.size() );

    cout << "\n" << qVec.at( random ) << "\n" << endl;
}
