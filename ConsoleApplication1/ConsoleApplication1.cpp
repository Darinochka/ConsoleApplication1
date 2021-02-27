#include <iostream>
#include <vector>
#include <map>
using namespace std;

template <typename First, typename Second>
  pair<First, Second> operator*(const pair<First, Second>& p1, const pair<First, Second>& p2);

template <typename Key, typename Value>
  map<Key, Value> operator*(const map<Key, Value>& lhs, const map<Key, Value>& rhs);

template <typename T>
  vector<T> operator*(const vector<T>& lhs, const vector<T>& rhs);

template <typename T> T Sqr(T x);

template <typename First, typename Second>
  pair<First, Second> operator*(const pair<First, Second>& p1, const pair<First, Second>& p2) {
    First resultFirst = p1.first * p2.first;
    Second resultSecond = p1.second * p2.second;

    return {resultFirst, resultSecond};
  }

template <typename Key, typename Value>
  map<Key, Value> operator*(const map<Key, Value>& lhs, const map<Key, Value>& rhs) {
    map<Key, Value> new_m;
    for (auto [key, value] : lhs) {
      new_m[key] = value * rhs.at(key);
    }

    return new_m;
  }

template <typename T>
  vector<T> operator*(const vector<T>& lhs, const vector<T>& rhs) {
    vector<T> new_v;
    for (int i = 0; i < lhs.size(); i++) {
      new_v.push_back(lhs[i]*rhs[i]);
    }

    return new_v;
  }

template <typename T>
  T Sqr(T x) {
    return x * x;
  }

int main() {
  vector<int> v = {1, 2, 3};
  cout << "vector:";
  for (int x : Sqr(v)) {
    cout << ' ' << x;
  }
  cout << endl;

  map<int, pair<int, int>> map_of_pairs = {
    {4, {2, 2}},
    {7, {4, 3}}
  };
  cout << "map of pairs:" << endl;
  for (const auto& x : Sqr(map_of_pairs)) {
    cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
  }
}