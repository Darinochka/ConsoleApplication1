#include <iostream>
#include <map>
using namespace std;

map <char, int> BuildCharCounters (string word) {
	map <char, int> result;
	for (auto i: word) {
		++result[i];
	}
	return result;
}
int main() {
	int n;
	string word1, word2;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> word1 >> word2;
		if (BuildCharCounters(word1) == BuildCharCounters(word2)) {
			cout << "YES";
		}
		else {
			cout << "NO";
		}
	}
	return 0;

}