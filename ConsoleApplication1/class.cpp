#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

template <typename Key, typename Value>
  Value& GetRefStrict(map<Key, Value>& m, Key find_key) {
    if (m.count(find_key) > 0) {
      return m[find_key];
    }
    throw runtime_error("");
  }

int main() {
  map<int, string> m = {{0, "value"}, {2, "value"}, {5, "value"}, {7, "value"}};
  string& item = GetRefStrict(m, 2);
  item = "newvalue";
  cout << m[2] << endl; // выведет newvalue
  return 0;
}