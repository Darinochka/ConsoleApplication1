#include <iostream>
#include <set>
#include <map>

using namespace std;
  

int main() {
    int n;
    string command, word1, word2;
    set <set<string>> words;
    map <string, int> count_syn;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> command;

        if (command == "ADD") {
            cin >> word1 >> word2;
            if (words.find({word1, word2}) == words.end()) {
                words.insert({word1, word2});
                ++count_syn[word1];
                ++count_syn[word2];
            }
        }
        if (command == "COUNT") {
            cin >> word1;
            cout << count_syn[word1] << endl;
        }
        if (command == "CHECK") {
            cin >> word1 >> word2;
            if (words.find({word1, word2}) == words.end()) {
                cout << "NO" << endl;
            } else {
                cout << "YES" << endl;
            }
        }

    }
    return 0;
}