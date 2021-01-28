#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <ctype.h> 
#include <stdio.h>

using namespace std;

string lowercase(const string& in) {
  string out;
  transform(in.begin(), in.end(), back_inserter(out), ::tolower );
  return out;
}

int main() {
    int n, i = 0;
    string str;
    char c; 
    cin >> n;
    vector <string> strings(n);
    for (string& str : strings) {
        cin >> str;
    }
    sort(strings.begin(), strings.end(), [](string a, string b) {return lowercase(a) < lowercase(b);});
    for (string str : strings) {
        cout << str << " ";
    }
    return 0;   
}