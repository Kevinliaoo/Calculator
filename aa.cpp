#include <iostream>
#include <sstream>
#include <string>
#include <map>
using namespace std;

void printFrequency(string st)
{
    // Each word it mapped to
    // it's frequency
    map<string, int> FW;

    // Used for breaking words
    stringstream ss(st);

    // To store individual words
    string Word;

    while (ss >> Word)
        FW[Word]++;

    map<string, int>::iterator m;
    for (m = FW.begin(); m != FW.end(); m++)
        cout << m->first << "-> "
             << m->second << "\n";
}

// Driver code
int main()
{
    string s = "Geeks For Geeks Ide";
    printFrequency(s);
    return 0;
}